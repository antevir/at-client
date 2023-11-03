/** @file
 * @brief 2nd gen uConnectXpress AT client
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

struct uCxAtClient;

typedef void (*uUrcCallback_t)(struct uCxAtClient *pClient, void *pTag, char *pLine, size_t lineLength);

typedef struct uCxAtClient {
    const struct uCxAtClientConfig *pConfig;
    size_t rxBufferPos;
    size_t urcBufferPos;
    bool executingCmd;
    const char *pExpectedRsp;
    size_t pExpectedRspLen;
    char *pRspParams;
    int32_t status;
    uUrcCallback_t urcCallback;
    void *pUrcCallbackTag;
} uCxAtClient_t;

typedef struct uCxAtClientConfig {
    void *pRxBuffer;        /**< Pointer to a buffer that the client will use as RX buffer */
    size_t rxBufferLen;     /**< Size of the RX buffer. */
    void *pUrcBuffer;       /**< Pointer to a separate URC buffer */
    size_t urcBufferLen;    /**< Size of the URC buffer. */
    void *pStreamHandle;    /**< User pointer associated with the AT interface.
                                 This pointer will be passed to write and read functions below
                                 and can be used to talk to a certain COM port etc.*/

    /* Callback for writing to the AT interface (typically a UART)
     * The function should return the number of actual bytes written or negative number on error.
     */
    int32_t (*write)(uCxAtClient_t *pClient, void *pStreamHandle, const void *pData, size_t length);

    /* Callback for reading from the AT interface (typically a UART)
     * The function should return the number of actual bytes read or negative number on error.
     */
    int32_t (*read)(uCxAtClient_t *pClient, void *pStreamHandle, void *pData, size_t length);
} uCxAtClientConfig_t;

/* ----------------------------------------------------------------
 * TYPES
 * -------------------------------------------------------------- */

/* ----------------------------------------------------------------
 * VARIABLES
 * -------------------------------------------------------------- */

/* ----------------------------------------------------------------
 * PUBLIC FUNCTIONS
 * -------------------------------------------------------------- */

/**
  * @brief  AT client init
  *
  * This function must be called before any other uCxAtClientXxx function is called.
  *
  * @param[in]  pConfig:  the AT client configuration (see \ref uCxAtClientConfig_t)
  * @param[out] pClient:  a pointer to an AT client struct that will be initialized.
  */
void uCxAtClientInit(const uCxAtClientConfig_t *pConfig, uCxAtClient_t *pClient);

/**
  * @brief  Set URC callback
  *
  * @param[in]  pClient:      the AT client from uCxAtClientInit().
  * @param[in]  urcCallback:  the callback to be called when a URC line is received.
  *                           Can be set to NULL for disabling the callback.
  * @param[in]  pTag          a user pointer that will be passed to the callback when called.
  */
void uCxAtClientSetUrcCallback(uCxAtClient_t *pClient, uUrcCallback_t urcCallback, void *pTag);

/**
  * @brief  Execute an AT command without any response
  *
  * @param[in]  pClient:  the AT client from uCxAtClientInit().
  * @param[in]  pCmd:     the AT command to execute.
  * @retval               0 on status OK, -1 on status ERROR, negative value on error.
  */
int32_t uCxAtClientExecSimpleCmd(uCxAtClient_t *pClient, const char *pCmd);


/**
  * @brief  Execute an AT command with params but without any response
  *
  * This function uses a param format string (somewhat similar to printf).
  * Defined format characters are:
  *
  * Char   Type          Desc
  * ---------------------------------------------
  * 'd'    int32_t       Integer
  * 's'    const char *  Null terminated string
  *
  * Each AT parameter is then added as an variadic argument to this function.
  * NOTE: The variadic parameters must always be terminated with U_CX_AT_UTIL_PARAM_LAST
  *
  * Example:
  * uCxAtClientExecSimpleCmdF(pClient,"AT+FOO=","ds",123,"MyString",U_CX_AT_UTIL_PARAM_LAST)
  * Result:
  * "AT+FOO=123,MyString\r"
  *
  * @param[in]  pClient:   the AT client from uCxAtClientInit().
  * @param[in]  pCmd:      the AT command to execute.
  * @param[in]  pParamFmt: format string - see function description.
  * @param      ...:       the AT params. Last param is always U_CX_AT_UTIL_PARAM_LAST!
  * @retval                0 on status OK, -1 on status ERROR, negative value on error.
  */
int32_t uCxAtClientExecSimpleCmdF(uCxAtClient_t *pClient, const char *pCmd, const char *pParamFmt,
                                  ...);

/**
  * @brief  Execute an AT command with params but without any response
  *
  * Same as uCxAtClientExecSimpleCmdF() but using a va_list for AT params instead of variadic arguments.
  *
  * @param[in]  pClient:   the AT client from uCxAtClientInit().
  * @param[in]  pCmd:      the AT command to execute.
  * @param[in]  pParamFmt: format string - see uCxAtClientExecSimpleCmdF().
  * @param      args:      the AT params. Last param is always U_CX_AT_UTIL_PARAM_LAST!
  * @retval                0 on status OK, -1 on status ERROR, negative value on error.
  */
void uCxAtClientSendCmdVaList(uCxAtClient_t *pClient, const char *pCmd, const char *pParamFmt,
                              va_list args);

/**
  * @brief  Begin an AT command with response
  *
  * The sequence of executing an AT command with response are:
  * 1. Call uCxAtClientCmdBeginF() - this will send the AT command
  * 2. Call either uCxAtClientCmdGetRspParamLine() or uCxAtClientCmdGetRspParamsF() for each response
  *    (you may call these functions several times if there are more than one response line)
  * 3. Call uCxAtClientCmdEnd() to wait for the AT status and end the AT command sequence.
  *
  * I.e. each call to uCxAtClientCmdBeginF() must always be terminated with a call to uCxAtClientCmdEnd().
  *
  * @param[in]  pClient:   the AT client from uCxAtClientInit().
  * @param[in]  pCmd:      the AT command to execute.
  * @param[in]  pParamFmt: format string - see uCxAtClientExecSimpleCmdF().
  * @param      args:      the AT params. Last param is always U_CX_AT_UTIL_PARAM_LAST!
  */
void uCxAtClientCmdBeginF(uCxAtClient_t *pClient, const char *pCmd, const char *pParamFmt, ...);

/**
  * @brief  Get AT response parameter line for AT command started with uCxAtClientCmdBeginF()
  *
  * @param[in]  pClient:      the AT client from uCxAtClientInit().
  * @param[in]  pExpectedRsp: the expected AT response suffix. Typically an AT command AT+FOO will respond
  *                           with something like '+FOO:123,"foo"'. In this case you set pExpectedRsp to '+FOO:'.
  *                           For some AT commands (such as AT+GMM) there are no suffix. In this case you can
  *                           set pExpectedRsp to either "" or NULL.
  * @retval                   a null terminated AT parameter line on success, otherwise NULL.
  *                           NOTE: The pExpectedRsp part will not be included in this string.
  */
char *uCxAtClientCmdGetRspParamLine(uCxAtClient_t *pClient, const char *pExpectedRsp);

/**
  * @brief  Get parsed AT response parameters for AT command started with uCxAtClientCmdBeginF()
  *
  * This function will read a response line like uCxAtClientCmdGetRspParamLine(), but will also try to
  * parse each AT parameter.
  *
  * @param[in]  pClient:      the AT client from uCxAtClientInit().
  * @param[in]  pExpectedRsp: the expected AT response suffix. Typically an AT command AT+FOO will respond
  *                           with something like '+FOO:123,"foo"'. In this case you set pExpectedRsp to '+FOO:'.
  *                           For some AT commands (such as AT+GMM) there are no suffix. In this case you can
  *                           set pExpectedRsp to either "" or NULL.
  * @param[in]  pParamFmt:    format string - see uCxAtClientExecSimpleCmdF().
  * @param      ...:          the AT params. Last param is always U_CX_AT_UTIL_PARAM_LAST!
  * @retval                   the number of parsed parameters on success otherwise negative value.
  */
int32_t uCxAtClientCmdGetRspParamsF(uCxAtClient_t *pClient, const char *pExpectedRsp,
                                    const char *pParamFmt, ...);

/**
  * @brief  End AT command started with uCxAtClientCmdBeginF() and get AT status
  *
  * Each call to uCxAtClientCmdBeginF() must be terminated with a call to this function.
  * The function will wait for the AT status ("OK" or "ERROR").
  *
  * @param[in]  pClient:   the AT client from uCxAtClientInit().
  * @retval                0 on status OK, -1 on status ERROR, negative value on error.
  */
int32_t uCxAtClientCmdEnd(uCxAtClient_t *pClient);

/**
  * @brief  Handle AT RX data
  *
  * Call this function when data has been received by the AT interface (UART) while no
  * AT command is being executed.
  *
  * This is needed for handling URCs that can be sent by the AT server at any time.
  * If this function is called when AT client is currently handling an AT command it
  * will do nothing.
  *
  * @param[in]  pClient:   the AT client from uCxAtClientInit().
  */
void uCxAtClientHandleRx(uCxAtClient_t *pClient);

#endif // U_CX_AT_CLIENT_H
