/** @file
 * @brief 2nd gen uConnectXpress AT client
 */

#include "limits.h"  // For INT_MAX
#include "stddef.h"  // NULL, size_t etc.
#include "stdint.h"  // int32_t etc.
#include "stdbool.h"
#include "string.h"  // memcpy(), strcmp(), strcspn(), strspm()
#include "stdio.h"   // snprintf()
#include "ctype.h"   // isprint()

#include "u_cx_at_config.h"

#include "u_cx_log.h"
#include "u_cx_at_util.h"
#include "u_cx_at_client.h"

/* ----------------------------------------------------------------
 * COMPILE-TIME MACROS
 * -------------------------------------------------------------- */

#define NO_STATUS   (INT_MAX)

/* ----------------------------------------------------------------
 * TYPES
 * -------------------------------------------------------------- */

enum uCxAtParserCode {
    AT_PARSER_NOP = 0,
    AT_PARSER_GOT_STATUS,
    AT_PARSER_GOT_RSP,
    AT_PARSER_ERROR
};

/* ----------------------------------------------------------------
 * STATIC PROTOTYPES
 * -------------------------------------------------------------- */

/* ----------------------------------------------------------------
 * STATIC VARIABLES
 * -------------------------------------------------------------- */

/* ----------------------------------------------------------------
 * STATIC FUNCTIONS
 * -------------------------------------------------------------- */

static int32_t parseLine(uCxAtClient_t *pClient, char *pLine, size_t lineLength)
{
    const struct uCxAtClientConfig *pConfig = pClient->pConfig;
    int32_t ret = AT_PARSER_NOP;

    char *pPtr = pLine;
    bool emptyLine = true;
    while (pPtr < &pLine[lineLength]) {
        if ((*pPtr != '\n') && (*pPtr != '\r')) {
            emptyLine = false;
            break;
        }
        pPtr++;
    }
    if (emptyLine) {
        return AT_PARSER_NOP;
    }

    U_CX_LOG_LINE(U_CX_LOG_CHANNEL_RX, "%s", pLine);

    if (pClient->executingCmd) {
        if ((pClient->pExpectedRsp != NULL) &&
            (*pClient->pExpectedRsp != 0) &&
            (strncmp(pLine, pClient->pExpectedRsp, pClient->pExpectedRspLen) == 0)) {
            pClient->pRspParams = &pLine[pClient->pExpectedRspLen];
            ret = AT_PARSER_GOT_RSP;
        } else if (strcmp(pLine, "OK") == 0) {
            pClient->status = 0;
            ret = AT_PARSER_GOT_STATUS;
        } else if (strcmp(pLine, "ERROR") == 0) {
            pClient->status = -1;
            ret = AT_PARSER_GOT_STATUS;
        } else if ((pLine[0] != '+') && (pLine[0] != '*')) {
            pClient->pRspParams = &pLine[0];
            ret = AT_PARSER_GOT_RSP;
        }
    }

    if (ret == AT_PARSER_NOP) {
        // Check if this is URC data
        if ((pLine[0] == '+') || (pLine[0] == '*')) {
            if (!pClient->executingCmd) {
                // If there are no command is currently executing we can just
                // execute the URC handler right away
                if (pClient->urcCallback) {
                    pClient->urcCallback(pClient, pClient->pUrcCallbackTag, pLine, lineLength);
                }
            } else {
                // AT client is busy handling AT command
                // Defer callback until command is done

                // We only support deferring one URC at the moment
                U_CX_AT_PORT_ASSERT(pClient->urcBufferPos == 0);

                if (lineLength <= pConfig->urcBufferLen) {
                    memcpy(pConfig->pUrcBuffer, pLine, lineLength);
                    pClient->urcBufferPos = lineLength;
                } else {
                    // URC buffer too small. Fail assert for now.
                    U_CX_AT_PORT_ASSERT(false);
                }
            }
        } else {
            // Received unexpected data
            // TODO: Handle
        }
    }

    return ret;
}

static int32_t parseIncomingChar(uCxAtClient_t *pClient, char ch)
{
    int32_t ret = AT_PARSER_NOP;
    char *pRxBuffer = (char *)pClient->pConfig->pRxBuffer;

    if ((ch == '\r') || (ch == '\n')) {
        pRxBuffer[pClient->rxBufferPos] = 0;
        ret = parseLine(pClient, pRxBuffer, pClient->rxBufferPos);
        pClient->rxBufferPos = 0;
    } else if (isprint(ch)) {
        pRxBuffer[pClient->rxBufferPos++] = ch;
        if (pClient->rxBufferPos == pClient->pConfig->rxBufferLen) {
            // Overflow - discard everything and start over
            pClient->rxBufferPos = 0;
        }
    }

    return ret;
}

static int32_t handleRxData(uCxAtClient_t *pClient)
{
    int32_t ret = AT_PARSER_NOP;
    int32_t readStatus;
    char ch;

    while ((readStatus = pClient->pConfig->read(pClient, pClient->pConfig->pStreamHandle, &ch, 1,
                                                pClient->pConfig->timeoutMs)) == 1) {
        ret = parseIncomingChar(pClient, ch);
        if (ret != AT_PARSER_NOP) {
            break;
        }
    }
    return ret;
}

static void handleDeferredUrc(uCxAtClient_t *pClient)
{
    if (pClient->urcBufferPos > 0) {
        if (pClient->urcCallback) {
            const struct uCxAtClientConfig *pConfig = pClient->pConfig;
            pClient->urcCallback(pClient, pClient->pUrcCallbackTag,
                                 (char *)pConfig->pUrcBuffer, pClient->urcBufferPos);
        }
        pClient->urcBufferPos = 0;
    }
}

static void cmdBeginF(uCxAtClient_t *pClient, const char *pCmd, const char *pParamFmt, va_list args)
{
    U_CX_MUTEX_LOCK(pClient->cmdMutex);

    // Check that previous command has completed
    // If this assert fails you have probably forgotten to call uCxAtClientCmdEnd()
    U_CX_AT_PORT_ASSERT(!pClient->executingCmd);

    pClient->pRspParams = NULL;
    pClient->executingCmd = true;
    pClient->status = NO_STATUS;
    pClient->cmdStartTime = U_CX_PORT_GET_TIME_MS();
    pClient->cmdTimeout = 10000; // Hard coded for now. TODO: Should be function argument
    uCxAtClientSendCmdVaList(pClient, pCmd, pParamFmt, args);
}

static int32_t cmdEnd(uCxAtClient_t *pClient)
{
    while (pClient->status == NO_STATUS) {
        handleRxData(pClient);

        int32_t now = U_CX_PORT_GET_TIME_MS();
        if ((now - pClient->cmdStartTime) > pClient->cmdTimeout) {
            pClient->status = -1;
            break;
        }
    }

    // cmdEnd() must be preceeded by a cmdBeginF()
    U_CX_AT_PORT_ASSERT(pClient->executingCmd);

    pClient->executingCmd = false;

    U_CX_MUTEX_UNLOCK(pClient->cmdMutex);

    // We may have received URCs during command execution
    handleDeferredUrc(pClient);

    return pClient->status;
}

static inline int32_t writeAndLog(uCxAtClient_t *pClient, const void *pData, size_t dataLen)
{
    const struct uCxAtClientConfig *pConfig = pClient->pConfig;
    U_CX_LOG(U_CX_LOG_CHANNEL_TX, "%s", (char *)pData);
    return pConfig->write(pClient, pConfig->pStreamHandle, pData, dataLen);
}

/* ----------------------------------------------------------------
 * PUBLIC FUNCTIONS
 * -------------------------------------------------------------- */

void uCxAtClientInit(const uCxAtClientConfig_t *pConfig, uCxAtClient_t *pClient)
{
    memset(pClient, 0, sizeof(uCxAtClient_t));
    pClient->pConfig = pConfig;
    U_CX_MUTEX_CREATE(pClient->cmdMutex);
}

void uCxAtClientSetUrcCallback(uCxAtClient_t *pClient, uUrcCallback_t urcCallback, void *pTag)
{
    pClient->urcCallback = urcCallback;
    pClient->pUrcCallbackTag = pTag;
}

void uCxAtClientSendCmdVaList(uCxAtClient_t *pClient, const char *pCmd, const char *pParamFmt,
                              va_list args)
{
    char buf[16];
    const struct uCxAtClientConfig *pConfig = pClient->pConfig;

    U_CX_LOG_BEGIN(U_CX_LOG_CHANNEL_TX);

    writeAndLog(pClient, pCmd, strlen(pCmd));
    const char *pCh = pParamFmt;
    while (*pCh != 0) {
        if (pCh != pParamFmt) {
            writeAndLog(pClient, ",", 1);
        }

        memset(&buf, 0, sizeof(buf));
        switch (*pCh) {
            case 'd': {
                int32_t i = va_arg(args, int32_t);
                int32_t len = snprintf(buf, sizeof(buf), "%d", i);
                writeAndLog(pClient, buf, len);
            }
            break;
            case 'h': {
                int32_t i = va_arg(args, int32_t);
                int32_t len = snprintf(buf, sizeof(buf), "%x", i);
                writeAndLog(pClient, buf, len);
            }
            break;
            case 's': {
                char *pStr = va_arg(args, char *);
                writeAndLog(pClient, pStr, strlen(pStr));
            }
            break;
            case 'b': {
                int32_t len = va_arg(args, int32_t);
                uint8_t *pData = va_arg(args, uint8_t *);
                for (int32_t i = 0; i < len; i++) {
                    uCxAtUtilByteToHex(pData[i], buf);
                    writeAndLog(pClient, buf, 2);
                }
            }
            break;
        }
        pCh++;
    }

    pConfig->write(pClient, pConfig->pStreamHandle, "\r", 1);
    U_CX_LOG_END(U_CX_LOG_CHANNEL_TX);
}

int32_t uCxAtClientExecSimpleCmdF(uCxAtClient_t *pClient, const char *pCmd, const char *pParamFmt,
                                  ...)
{
    va_list args;

    va_start(args, pParamFmt);
    cmdBeginF(pClient, pCmd, pParamFmt, args);
    va_end(args);

    return cmdEnd(pClient);
}

int32_t uCxAtClientExecSimpleCmd(uCxAtClient_t *pClient, const char *pCmd)
{
    cmdBeginF(pClient, pCmd, "", NULL);

    return cmdEnd(pClient);
}

void uCxAtClientCmdBeginF(uCxAtClient_t *pClient, const char *pCmd, const char *pParamFmt, ...)
{
    va_list args;

    va_start(args, pParamFmt);
    cmdBeginF(pClient, pCmd, pParamFmt, args);
    va_end(args);
}

char *uCxAtClientCmdGetRspParamLine(uCxAtClient_t *pClient, const char *pExpectedRsp)
{
    char *pRet = NULL;
    pClient->pRspParams = NULL;
    pClient->pExpectedRsp = pExpectedRsp;
    if (pExpectedRsp) {
        pClient->pExpectedRspLen = strlen(pExpectedRsp);
    } else {
        pClient->pExpectedRspLen = 0;
    }

    while (pClient->status == NO_STATUS) {
        if (handleRxData(pClient) == AT_PARSER_GOT_RSP) {
            pRet = pClient->pRspParams;
            break;
        }
        // Check for timeout
        int32_t now = U_CX_PORT_GET_TIME_MS();
        if ((now - pClient->cmdStartTime) > pClient->cmdTimeout) {
            return NULL;
        }
    }

    return pRet;
}

int32_t uCxAtClientCmdGetRspParamsF(uCxAtClient_t *pClient, const char *pExpectedRsp,
                                    const char *pParamFmt, ...)
{
    va_list args;
    char *pRspParams = uCxAtClientCmdGetRspParamLine(pClient, pExpectedRsp);
    if (pRspParams == NULL) {
        return -1;
    }
    va_start(args, pParamFmt);
    int32_t ret = uCxAtUtilParseParamsVaList(pRspParams, pParamFmt, args);
    va_end(args);

    return ret;
}

int32_t uCxAtClientCmdEnd(uCxAtClient_t *pClient)
{
    return cmdEnd(pClient);
}

void uCxAtClientHandleRx(uCxAtClient_t *pClient)
{
    U_CX_MUTEX_LOCK(pClient->cmdMutex);

    if (!pClient->executingCmd) {
        handleRxData(pClient);
    }

    U_CX_MUTEX_UNLOCK(pClient->cmdMutex);
}
