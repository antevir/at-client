/** @file
 * @brief Short description of the purpose of the file
 */

#ifndef U_AT_CLIENT_H
#define U_AT_CLIENT_H

#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>

#include "u_at_util.h"

/* ----------------------------------------------------------------
 * COMPILE-TIME MACROS
 * -------------------------------------------------------------- */

typedef struct {
    char *pRxBuffer;
    size_t rxBufferLen;
    size_t rxBufferPos;
    bool executingCmd;
    const char *pExpectedRsp;
    size_t pExpectedRspLen;
    char *pRspParams;
    int status;
    void (*urcCallback)(char *pLine);
} uAtClient_t;

/* ----------------------------------------------------------------
 * TYPES
 * -------------------------------------------------------------- */

/* ----------------------------------------------------------------
 * VARIABLES
 * -------------------------------------------------------------- */

/* ----------------------------------------------------------------
 * PUBLIC FUNCTIONS
 * -------------------------------------------------------------- */

void uAtClientInit(void *pRxBuffer, size_t rxBufferLen, uAtClient_t *pClient);

void uAtClientSendCmdVaList(uAtClient_t *pClient, const char *pCmd, const char *pParamFmt, va_list args);

int uAtClientExecSimpleCmdF(uAtClient_t *pClient, const char *pCmd, const char *pParamFmt, ...);
int uAtClientExecSimpleCmd(uAtClient_t *pClient, const char *pCmd);

void uAtClientCmdBeginF(uAtClient_t *pClient, const char *pCmd, const char *pParamFmt, ...);

char *uAtClientCmdGetRspParamLine(uAtClient_t *pClient, const char *pExpectedRsp);

int uAtClientCmdGetRspParamsF(uAtClient_t *pClient, const char *pExpectedRsp, const char *pParamFmt, ...);

int uAtClientCmdEnd(uAtClient_t *pClient);

#endif // U_AT_CLIENT_H
