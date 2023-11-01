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

static int32_t parseLine(uCxAtClient_t *pClient, char *pLine)
{
    int32_t ret = AT_PARSER_NOP;

    char *pPtr = pLine;
    bool emptyLine = true;
    while (*pPtr) {
        if ((*pPtr != '\n') && (*pPtr != '\r')) {
            emptyLine = false;
        }
        pPtr++;
    }
    if (emptyLine) {
        return AT_PARSER_NOP;
    }

    if (pClient->executingCmd) {
        if ((pClient->pExpectedRsp != NULL) &&
            (*pClient->pExpectedRsp != 0) &&
            (strncmp(pLine, pClient->pExpectedRsp, pClient->pExpectedRspLen) == 0)) {
            pClient->pRspParams = &pLine[pClient->pExpectedRspLen + 1];
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
        if ((pLine[0] == '+') || (pLine[0] == '*')) {
            if (pClient->urcCallback) {
                pClient->urcCallback(pLine);
            }
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
        ret = parseLine(pClient, pRxBuffer);
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

    while ((readStatus = pClient->pConfig->read(pClient, pClient->pConfig->pStreamHandle, &ch, 1)) == 1) {
        ret = parseIncomingChar(pClient, ch);
        if (ret != AT_PARSER_NOP) {
            break;
        }
    }

    return (readStatus < 0 ? readStatus : ret);
}


static void cmdBeginF(uCxAtClient_t *pClient, const char *pCmd, const char *pParamFmt, va_list args)
{
    // Check that previous command has completed
    // If this assert fails you have probably forgotten to call uCxAtClientCmdEnd()
    U_CX_AT_PORT_ASSERT(!pClient->executingCmd);

    pClient->pRspParams = NULL;
    pClient->executingCmd = true;
    pClient->status = NO_STATUS;
    uCxAtClientSendCmdVaList(pClient, pCmd, pParamFmt, args);
}

static int32_t cmdEnd(uCxAtClient_t *pClient)
{
    while (pClient->status == NO_STATUS) {
        handleRxData(pClient);
    }

    // cmdEnd() must be preceeded by a cmdBeginF()
    U_CX_AT_PORT_ASSERT(pClient->executingCmd);

    pClient->executingCmd = false;

    return pClient->status;
}

/* ----------------------------------------------------------------
 * PUBLIC FUNCTIONS
 * -------------------------------------------------------------- */

void uCxAtClientInit(const uCxAtClientConfig_t *pConfig, uCxAtClient_t *pClient)
{
    memset(pClient, 0, sizeof(uCxAtClient_t));
    pClient->pConfig = pConfig;
}

void uCxAtClientSendCmdVaList(uCxAtClient_t *pClient, const char *pCmd, const char *pParamFmt,
                              va_list args)
{
    char buf[16];
    const struct uCxAtClientConfig *pConfig = pClient->pConfig;

    pConfig->write(pClient, pConfig->pStreamHandle, pCmd, strlen(pCmd));
    const char *pCh = pParamFmt;
    while (*pCh != 0) {
        if (pCh != pParamFmt) {
            pConfig->write(pClient, pConfig->pStreamHandle, ",", 1);
        }

        switch (*pCh) {
            case 'd': {
                int i = va_arg(args, int);
                int len = snprintf(buf, sizeof(buf), "%d", i);
                pConfig->write(pClient, pConfig->pStreamHandle, buf, len);
            }
            break;
            case 'h': {
                int i = va_arg(args, int);
                int len = snprintf(buf, sizeof(buf), "%x", i);
                pConfig->write(pClient, pConfig->pStreamHandle, buf, len);
            }
            break;
            case 's': {
                char *pStr = va_arg(args, char *);
                pConfig->write(pClient, pConfig->pStreamHandle, pStr, strlen(pStr));
            }
            break;
            case 'b': {
                int len = va_arg(args, int);
                uint8_t *pData = va_arg(args, uint8_t *);
                for (int i = 0; i < len; i++) {
                    uCxAtUtilByteToHex(pData[i], buf);
                    pConfig->write(pClient, pConfig->pStreamHandle, buf, 2);
                }
            }
            break;
        }
        pCh++;
    }

    pConfig->write(pClient, pConfig->pStreamHandle, "\r", 1);
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
    }

    return pRet;
}

int32_t uCxAtClientCmdGetRspParamsF(uCxAtClient_t *pClient, const char *pExpectedRsp,
                                    const char *pParamFmt, ...)
{
    va_list args;
    char *pRspParams = uCxAtClientCmdGetRspParamLine(pClient, pExpectedRsp);

    va_start(args, pParamFmt);
    int32_t ret = uCxAtUtilParseParamsVaList(pRspParams, pParamFmt, args);
    va_end(args);

    return ret;
}

int32_t uCxAtClientCmdEnd(uCxAtClient_t *pClient)
{
    return cmdEnd(pClient);
}
