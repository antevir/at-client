/** @file
 * @brief Short description of the purpose of the file
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#include "u_at_util.h"
#include "u_at_client.h"

/* ----------------------------------------------------------------
 * COMPILE-TIME MACROS
 * -------------------------------------------------------------- */

#define NO_STATUS   (INT_MAX)

/* ----------------------------------------------------------------
 * TYPES
 * -------------------------------------------------------------- */

enum uAtParserCode {
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

size_t read(void *pData, size_t length)
{
    return fread(pData, 1, length, stdin);
}

void write(const void *pData, size_t length)
{
    fwrite(pData, 1, length, stdout);
}

static int parseLine(uAtClient_t *pClient, char *pLine)
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

static int parseIncomingChar(uAtClient_t *pClient, char ch)
{
    int ret = AT_PARSER_NOP;

    if ((ch == '\r') || (ch == '\n')) {
        pClient->pRxBuffer[pClient->rxBufferPos] = 0;
        ret = parseLine(pClient, pClient->pRxBuffer);
        pClient->rxBufferPos = 0;
    } else if(isprint(ch)) {
        pClient->pRxBuffer[pClient->rxBufferPos++] = ch;
        if (pClient->rxBufferPos == pClient->rxBufferLen) {
            // Overflow - discard everything and start over
            pClient->rxBufferPos = 0;
        }
    }

    return ret;
}

static int handleRxData(uAtClient_t *pClient)
{
    int ret = AT_PARSER_NOP;
    char ch;

    while (read(&ch, 1) > 0) {
        ret = parseIncomingChar(pClient, ch);
        if (ret != AT_PARSER_NOP) {
            break;
        }
    }

    return ret;
}


static void cmdBeginF(uAtClient_t *pClient, const char *pCmd, const char *pParamFmt, va_list args)
{
    //handleRxData(pClient);

    pClient->pRspParams = NULL;
    pClient->executingCmd = true;
    pClient->status = NO_STATUS;
    uAtClientSendCmdVaList(pClient, pCmd, pParamFmt, args);
}

static int cmdEnd(uAtClient_t *pClient)
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

void uAtClientInit(void *pRxBuffer, size_t rxBufferLen, uAtClient_t *pClient)
{
    memset(pClient, 0, sizeof(uAtClient_t));
    pClient->pRxBuffer = pRxBuffer;
    pClient->rxBufferLen = rxBufferLen;
}

void uAtClientSendCmdVaList(uAtClient_t *pClient, const char *pCmd, const char *pParamFmt, va_list args)
{
    char buf[16];

    write(pCmd, strlen(pCmd));
    const char *pCh = pParamFmt;
    while (*pCh != 0) {
        if (pCh != pParamFmt) {
            write(",", 1);
        }

        switch (*pCh) {
            case 'd':
                {
                    int i = va_arg(args, int);
                    int len = snprintf(buf, sizeof(buf), "%d", i);
                    write(buf, len);
                }
                break;
            case 'h':
                {
                    int i = va_arg(args, int);
                    int len = snprintf(buf, sizeof(buf), "%x", i);
                    write(buf, len);
                }
                break;
            case 's':
                {
                    char *pStr = va_arg(args, char *);
                    write(pStr, strlen(pStr));
                }
                break;
            case 'b':
                {
                    int len = va_arg(args, int);
                    uint8_t *pData = va_arg(args, uint8_t *);
                    for (int i = 0; i < len; i++) {
                        uAtUtilByteToHex(pData[i], buf);
                        write(buf, 2);
                    }
                }
                break;
        }
        pCh++;
    }

    write("\r", 1);
}

int uAtClientExecSimpleCmdF(uAtClient_t *pClient, const char *pCmd, const char *pParamFmt, ...)
{
    va_list args;

    va_start(args, pParamFmt);
    cmdBeginF(pClient, pCmd, pParamFmt, args);
    va_end(args);

    return cmdEnd(pClient);
}

int uAtClientExecSimpleCmd(uAtClient_t *pClient, const char *pCmd)
{
    cmdBeginF(pClient, pCmd, "", NULL);

    return cmdEnd(pClient);
}

void uAtClientCmdBeginF(uAtClient_t *pClient, const char *pCmd, const char *pParamFmt, ...)
{
    va_list args;

    va_start(args, pParamFmt);
    cmdBeginF(pClient, pCmd, pParamFmt, args);
    va_end(args);
}

char *uAtClientCmdGetRspParamLine(uAtClient_t *pClient, const char *pExpectedRsp)
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

int uAtClientCmdGetRspParamsF(uAtClient_t *pClient, const char *pExpectedRsp, const char *pParamFmt, ...)
{
    va_list args;
    char *pRspParams = uAtClientCmdGetRspParamLine(pClient, pExpectedRsp);

    va_start(args, pParamFmt);
    int ret = uAtUtilParseParamsVaList(pRspParams, pParamFmt, args);
    va_end(args);

    return ret;
}

int uAtClientCmdEnd(uAtClient_t *pClient)
{
    return cmdEnd(pClient);
}
