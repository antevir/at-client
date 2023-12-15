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

int32_t uCxSocketCreate1(uCxHandle_t * puCxHandle, uProtocol_t protocol, int32_t * pSocketHandle)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    int32_t ret;
    uCxAtClientCmdBeginF(pAtClient, "AT+USOCR=", "d", protocol, U_CX_AT_UTIL_PARAM_LAST);
    ret = uCxAtClientCmdGetRspParamsF(pAtClient, "+USOCR:", "d", pSocketHandle, U_CX_AT_UTIL_PARAM_LAST);
    if (ret >= 0) {
        ret = uCxAtClientCmdEnd(pAtClient);
    }
    return ret;
}

int32_t uCxSocketCreate2(uCxHandle_t * puCxHandle, uProtocol_t protocol, uPreferredProtocolType_t preferred_protocol_type, int32_t * pSocketHandle)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    int32_t ret;
    uCxAtClientCmdBeginF(pAtClient, "AT+USOCR=", "dd", protocol, preferred_protocol_type, U_CX_AT_UTIL_PARAM_LAST);
    ret = uCxAtClientCmdGetRspParamsF(pAtClient, "+USOCR:", "d", pSocketHandle, U_CX_AT_UTIL_PARAM_LAST);
    if (ret >= 0) {
        ret = uCxAtClientCmdEnd(pAtClient);
    }
    return ret;
}

int32_t uCxSocketSetTLS2(uCxHandle_t * puCxHandle, int32_t socket_handle, uTlsVersion_t tls_version)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+USOTLS=", "dd", socket_handle, tls_version, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxSocketSetTLS3(uCxHandle_t * puCxHandle, int32_t socket_handle, uTlsVersion_t tls_version, const char * ca_name)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+USOTLS=", "dds", socket_handle, tls_version, ca_name, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxSocketSetTLS5(uCxHandle_t * puCxHandle, int32_t socket_handle, uTlsVersion_t tls_version, const char * ca_name, const char * client_cert_name, const char * client_key_name)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+USOTLS=", "ddsss", socket_handle, tls_version, ca_name, client_cert_name, client_key_name, U_CX_AT_UTIL_PARAM_LAST);
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

int32_t uCxSocketGetReadMode(uCxHandle_t * puCxHandle, uReadMode_t * pReadMode)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    int32_t ret;
    uCxAtClientCmdBeginF(pAtClient, "AT+USORM?", "", U_CX_AT_UTIL_PARAM_LAST);
    ret = uCxAtClientCmdGetRspParamsF(pAtClient, "+USORM:", "d", pReadMode, U_CX_AT_UTIL_PARAM_LAST);
    if (ret >= 0) {
        ret = uCxAtClientCmdEnd(pAtClient);
    }
    return ret;
}

int32_t uCxSocketWriteString(uCxHandle_t * puCxHandle, int32_t socket_handle, const char * string_data, uCxSocketWriteString_t * pSocketWriteStringRsp)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    int32_t ret;
    uCxAtClientCmdBeginF(pAtClient, "AT+USOWS=", "ds", socket_handle, string_data, U_CX_AT_UTIL_PARAM_LAST);
    ret = uCxAtClientCmdGetRspParamsF(pAtClient, "+USOWS:", "dd", &pSocketWriteStringRsp->socket_handle, &pSocketWriteStringRsp->written_length, U_CX_AT_UTIL_PARAM_LAST);
    if (ret >= 0) {
        ret = uCxAtClientCmdEnd(pAtClient);
    }
    return ret;
}

int32_t uCxSocketClose(uCxHandle_t * puCxHandle, int32_t socket_handle)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+USOCL=", "d", socket_handle, U_CX_AT_UTIL_PARAM_LAST);
}

bool uCxBeginSocketReadString(uCxHandle_t * puCxHandle, int32_t socket_handle, int32_t length, uCxSocketReadString_t * pSocketReadStringRsp)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    int32_t ret;
    uCxAtClientCmdBeginF(pAtClient, "AT+USORS=", "dd", socket_handle, length, U_CX_AT_UTIL_PARAM_LAST);
    ret = uCxAtClientCmdGetRspParamsF(pAtClient, "+USORS:", "dds", &pSocketReadStringRsp->socket_handle, &pSocketReadStringRsp->length, &pSocketReadStringRsp->string_data, U_CX_AT_UTIL_PARAM_LAST);
    return ret > 0;
}

int32_t uCxSocketListen(uCxHandle_t * puCxHandle, int32_t socket_handle, int32_t port)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+USOL=", "dd", socket_handle, port, U_CX_AT_UTIL_PARAM_LAST);
}

bool uCxBeginSocketReceiveFrom(uCxHandle_t * puCxHandle, int32_t socket_handle, int32_t length, uCxSocketReceiveFrom_t * pSocketReceiveFromRsp)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    int32_t ret;
    uCxAtClientCmdBeginF(pAtClient, "AT+USORF=", "dd", socket_handle, length, U_CX_AT_UTIL_PARAM_LAST);
    ret = uCxAtClientCmdGetRspParamsF(pAtClient, "+USORF:", "didds", &pSocketReceiveFromRsp->socket_handle, &pSocketReceiveFromRsp->remote_ip, &pSocketReceiveFromRsp->remote_port, &pSocketReceiveFromRsp->length, &pSocketReceiveFromRsp->string_data, U_CX_AT_UTIL_PARAM_LAST);
    return ret > 0;
}

void uCxBeginSocketListStatus(uCxHandle_t * puCxHandle)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    uCxAtClientCmdBeginF(pAtClient, "AT+USOST?", "", U_CX_AT_UTIL_PARAM_LAST);
}

bool uCxSocketListStatusGetResponse(uCxHandle_t * puCxHandle, uCxSocketListStatus_t * pSocketListStatusRsp)
{
    int32_t ret;
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    ret = uCxAtClientCmdGetRspParamsF(pAtClient, "+USOST:", "ddd", &pSocketListStatusRsp->socket_handle, &pSocketListStatusRsp->protocol, &pSocketListStatusRsp->socket_status, U_CX_AT_UTIL_PARAM_LAST);
    return ret >= 0;
}

int32_t uCxSocketGetStatus(uCxHandle_t * puCxHandle, int32_t socket_handle, uCxSocketGetStatus_t * pSocketGetStatusRsp)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    int32_t ret;
    uCxAtClientCmdBeginF(pAtClient, "AT+USOST=", "d", socket_handle, U_CX_AT_UTIL_PARAM_LAST);
    ret = uCxAtClientCmdGetRspParamsF(pAtClient, "+USOST:", "ddd", &pSocketGetStatusRsp->socket_handle, &pSocketGetStatusRsp->protocol, &pSocketGetStatusRsp->socket_status, U_CX_AT_UTIL_PARAM_LAST);
    if (ret >= 0) {
        ret = uCxAtClientCmdEnd(pAtClient);
    }
    return ret;
}

int32_t uCxSocketSetOption(uCxHandle_t * puCxHandle, int32_t socket_handle, uOption_t option, int32_t value)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+USOO=", "ddd", socket_handle, option, value, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxSocketGetOption(uCxHandle_t * puCxHandle, int32_t socket_handle, uOption_t option, uCxSocketGetOption_t * pSocketGetOptionRsp)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    int32_t ret;
    uCxAtClientCmdBeginF(pAtClient, "AT+USOO=", "dd", socket_handle, option, U_CX_AT_UTIL_PARAM_LAST);
    ret = uCxAtClientCmdGetRspParamsF(pAtClient, "+USOO:", "ddd", &pSocketGetOptionRsp->socket_handle, &pSocketGetOptionRsp->option, &pSocketGetOptionRsp->value, U_CX_AT_UTIL_PARAM_LAST);
    if (ret >= 0) {
        ret = uCxAtClientCmdEnd(pAtClient);
    }
    return ret;
}

int32_t uCxSocketGetHostByName(uCxHandle_t * puCxHandle, const char * host_name, uSockIpAddress_t * pHostIp)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    int32_t ret;
    uCxAtClientCmdBeginF(pAtClient, "AT+USOH=", "s", host_name, U_CX_AT_UTIL_PARAM_LAST);
    ret = uCxAtClientCmdGetRspParamsF(pAtClient, "+USOH:", "i", pHostIp, U_CX_AT_UTIL_PARAM_LAST);
    if (ret >= 0) {
        ret = uCxAtClientCmdEnd(pAtClient);
    }
    return ret;
}
