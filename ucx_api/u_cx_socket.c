/*
* This file was automatically generated using csnake v0.3.5.
*
* This file should not be edited directly, any changes will be
* overwritten next time the script is run.
*
* Source code for csnake is available at:
* https://gitlab.com/andrejr/csnake
*
* csnake is also available on PyPI, at :
* https://pypi.org/project/csnake
*/
#include "u_cx_at_client.h"
#include "u_cx_socket.h"

int32_t uCxBeginSocketCreate1(uCxHandle_t * puCxHandle, uProtocol_t protocol, int32_t * pSocketHandle)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    uCxAtClientCmdBeginF(pAtClient, "AT+USOCR=", "d", protocol, U_CX_AT_UTIL_PARAM_LAST);
    return uCxAtClientCmdGetRspParamsF(pAtClient, "+USOCR:", "d", pSocketHandle);
}

int32_t uCxBeginSocketCreate2(uCxHandle_t * puCxHandle, uProtocol_t protocol, uPreferredProtocolType_t preferred_protocol_type, int32_t * pSocketHandle)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    uCxAtClientCmdBeginF(pAtClient, "AT+USOCR=", "dd", protocol, preferred_protocol_type, U_CX_AT_UTIL_PARAM_LAST);
    return uCxAtClientCmdGetRspParamsF(pAtClient, "+USOCR:", "d", pSocketHandle);
}

int32_t uCxSocketConnect(uCxHandle_t * puCxHandle, int32_t socket_handle, const char * host_address, int32_t remote_port)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+USOC=", "dsd", socket_handle, host_address, remote_port, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxSocketSetReadMode(uCxHandle_t * puCxHandle, uReadMode_t read_mode)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+USORM=", "d", read_mode, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxBeginSocketGetReadMode(uCxHandle_t * puCxHandle, uReadMode_t * pReadMode)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    uCxAtClientCmdBeginF(pAtClient, "AT+USORM?", "", U_CX_AT_UTIL_PARAM_LAST);
    return uCxAtClientCmdGetRspParamsF(pAtClient, "+USORM:", "d", pReadMode);
}

int32_t uCxBeginSocketWriteString(uCxHandle_t * puCxHandle, int32_t socket_handle, const char * string_data, uCxSocketWriteString_t * pSocketWriteStringRsp)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    uCxAtClientCmdBeginF(pAtClient, "AT+USOWS=", "ds", socket_handle, string_data, U_CX_AT_UTIL_PARAM_LAST);
    return uCxAtClientCmdGetRspParamsF(pAtClient, "+USOWS:", "dd", &pSocketWriteStringRsp->socket_handle, &pSocketWriteStringRsp->written_length);
}

int32_t uCxSocketClose(uCxHandle_t * puCxHandle, int32_t socket_handle)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+USOCL=", "d", socket_handle, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxBeginSocketReadString(uCxHandle_t * puCxHandle, int32_t socket_handle, int32_t length, uCxSocketReadString_t * pSocketReadStringRsp)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    uCxAtClientCmdBeginF(pAtClient, "AT+USORS=", "dd", socket_handle, length, U_CX_AT_UTIL_PARAM_LAST);
    return uCxAtClientCmdGetRspParamsF(pAtClient, "+USORS:", "dds", &pSocketReadStringRsp->socket_handle, &pSocketReadStringRsp->length, &pSocketReadStringRsp->string_data);
}

int32_t uCxSocketListen(uCxHandle_t * puCxHandle, int32_t socket_handle, int32_t port)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+USOL=", "dd", socket_handle, port, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxBeginSocketStatus(uCxHandle_t * puCxHandle, uCxSocketStatus_t * pSocketStatusRsp)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    uCxAtClientCmdBeginF(pAtClient, "AT+USOST?", "", U_CX_AT_UTIL_PARAM_LAST);
    return uCxAtClientCmdGetRspParamsF(pAtClient, "+USOST:", "ddd", &pSocketStatusRsp->socket_handle, &pSocketStatusRsp->protocol, &pSocketStatusRsp->socket_status);
}

int32_t uCxSocketSetOption(uCxHandle_t * puCxHandle, int32_t socket_handle, uOption_t option, int32_t value)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+USOO=", "ddd", socket_handle, option, value, U_CX_AT_UTIL_PARAM_LAST);
}