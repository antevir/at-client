/** @file
 * @brief Short description of the purpose of the file
 */

#ifndef U_CX_AT_CLIENT_H
#define U_CX_AT_CLIENT_H

#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>

#include "u_cx_at_util.h"

/* ----------------------------------------------------------------
 * COMPILE-TIME MACROS
 * -------------------------------------------------------------- */

typedef struct uCxAtClient {
    void *streamHandle;
    char *pRxBuffer;
    size_t rxBufferLen;
    size_t rxBufferPos;
    bool executingCmd;
    const char *pExpectedRsp;
    size_t pExpectedRspLen;
    char *pRspParams;
    int status;
    void (*urcCallback)(char *pLine);
} uCxAtClient_t;

/* ----------------------------------------------------------------
 * TYPES
 * -------------------------------------------------------------- */

/* ----------------------------------------------------------------
 * VARIABLES
 * -------------------------------------------------------------- */

/* ----------------------------------------------------------------
 * PUBLIC FUNCTIONS
 * -------------------------------------------------------------- */

void uCxAtClientInit(void *streamHandle, void *pRxBuffer, size_t rxBufferLen,
                     uCxAtClient_t *pClient);

void uCxAtClientSendCmdVaList(uCxAtClient_t *pClient, const char *pCmd, const char *pParamFmt,
                              va_list args);

int uCxAtClientExecSimpleCmdF(uCxAtClient_t *pClient, const char *pCmd, const char *pParamFmt, ...);
int uCxAtClientExecSimpleCmd(uCxAtClient_t *pClient, const char *pCmd);

void uCxAtClientCmdBeginF(uCxAtClient_t *pClient, const char *pCmd, const char *pParamFmt, ...);

char *uCxAtClientCmdGetRspParamLine(uCxAtClient_t *pClient, const char *pExpectedRsp);

int uCxAtClientCmdGetRspParamsF(uCxAtClient_t *pClient, const char *pExpectedRsp,
                                const char *pParamFmt, ...);

int uCxAtClientCmdEnd(uCxAtClient_t *pClient);

#endif // U_CX_AT_CLIENT_H
