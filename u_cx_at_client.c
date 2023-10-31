/** @file
 * @brief Short description of the purpose of the file
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

static int parseLine(uCxAtClient_t *pClient, char *pLine)
{
    int ret = AT_PARSER_NOP;

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

static int parseIncomingChar(uCxAtClient_t *pClient, char ch)
{
    int ret = AT_PARSER_NOP;

    if ((ch == '\r') || (ch == '\n')) {
        pClient->pRxBuffer[pClient->rxBufferPos] = 0;
        ret = parseLine(pClient, pClient->pRxBuffer);
        pClient->rxBufferPos = 0;
    } else if (isprint(ch)) {
        pClient->pRxBuffer[pClient->rxBufferPos++] = ch;
        if (pClient->rxBufferPos == pClient->rxBufferLen) {
            // Overflow - discard everything and start over
            pClient->rxBufferPos = 0;
        }
    }

    return ret;
}

static int handleRxData(uCxAtClient_t *pClient)
{
    int ret = AT_PARSER_NOP;
    char ch;

    while (U_CX_AT_PORT_READ(pClient, &ch, 1) > 0) {
        ret = parseIncomingChar(pClient, ch);
        if (ret != AT_PARSER_NOP) {
            break;
        }
    }

    return ret;
}


static void cmdBeginF(uCxAtClient_t *pClient, const char *pCmd, const char *pParamFmt, va_list args)
{
    //handleRxData(pClient);

    pClient->pRspParams = NULL;
    pClient->executingCmd = true;
    pClient->status = NO_STATUS;
    uCxAtClientSendCmdVaList(pClient, pCmd, pParamFmt, args);
}

static int cmdEnd(uCxAtClient_t *pClient)
{
    while (pClient->status == NO_STATUS) {
        handleRxData(pClient);
    }

    pClient->executingCmd = false;

    return pClient->status;
}

/* ----------------------------------------------------------------
 * PUBLIC FUNCTIONS
 * -------------------------------------------------------------- */

void uCxAtClientInit(void *streamHandle, void *pRxBuffer, size_t rxBufferLen,
                     uCxAtClient_t *pClient)
{
    memset(pClient, 0, sizeof(uCxAtClient_t));
    pClient->streamHandle = streamHandle;
    pClient->pRxBuffer = pRxBuffer;
    pClient->rxBufferLen = rxBufferLen;
}

void uCxAtClientSendCmdVaList(uCxAtClient_t *pClient, const char *pCmd, const char *pParamFmt,
                              va_list args)
{
    char buf[16];

    U_CX_AT_PORT_WRITE(pClient, pCmd, strlen(pCmd));
    const char *pCh = pParamFmt;
    while (*pCh != 0) {
        if (pCh != pParamFmt) {
            U_CX_AT_PORT_WRITE(pClient, ",", 1);
        }

        switch (*pCh) {
            case 'd': {
                int i = va_arg(args, int);
                int len = snprintf(buf, sizeof(buf), "%d", i);
                U_CX_AT_PORT_WRITE(pClient, buf, len);
            }
            break;
            case 'h': {
                int i = va_arg(args, int);
                int len = snprintf(buf, sizeof(buf), "%x", i);
                U_CX_AT_PORT_WRITE(pClient, buf, len);
            }
            break;
            case 's': {
                char *pStr = va_arg(args, char *);
                U_CX_AT_PORT_WRITE(pClient, pStr, strlen(pStr));
            }
            break;
            case 'b': {
                int len = va_arg(args, int);
                uint8_t *pData = va_arg(args, uint8_t *);
                for (int i = 0; i < len; i++) {
                    uCxAtUtilByteToHex(pData[i], buf);
                    U_CX_AT_PORT_WRITE(pClient, buf, 2);
                }
            }
            break;
        }
        pCh++;
    }

    U_CX_AT_PORT_WRITE(pClient, "\r", 1);
}

int uCxAtClientExecSimpleCmdF(uCxAtClient_t *pClient, const char *pCmd, const char *pParamFmt, ...)
{
    va_list args;

    va_start(args, pParamFmt);
    cmdBeginF(pClient, pCmd, pParamFmt, args);
    va_end(args);

    return cmdEnd(pClient);
}

int uCxAtClientExecSimpleCmd(uCxAtClient_t *pClient, const char *pCmd)
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

int uCxAtClientCmdGetRspParamsF(uCxAtClient_t *pClient, const char *pExpectedRsp,
                                const char *pParamFmt, ...)
{
    va_list args;
    char *pRspParams = uCxAtClientCmdGetRspParamLine(pClient, pExpectedRsp);

    va_start(args, pParamFmt);
    int ret = uCxAtUtilParseParamsVaList(pRspParams, pParamFmt, args);
    va_end(args);

    return ret;
}

int uCxAtClientCmdEnd(uCxAtClient_t *pClient)
{
    return cmdEnd(pClient);
}
