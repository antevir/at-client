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
#include "u_cx_sps.h"

int32_t uCxSpsConnect1(uCxHandle_t * puCxHandle, int32_t conn_handle)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+USPSC=", "d", conn_handle, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxSpsConnect2(uCxHandle_t * puCxHandle, int32_t conn_handle, int32_t flow_control)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+USPSC=", "dd", conn_handle, flow_control, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxSpsSetServiceEnable(uCxHandle_t * puCxHandle, uSpsServiceOption_t sps_service_option)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+USPS=", "d", sps_service_option, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxSpsGetServiceEnable(uCxHandle_t * puCxHandle, uSpsServiceOption_t * pSpsServiceOption)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    int32_t ret;
    uCxAtClientCmdBeginF(pAtClient, "AT+USPS?", "", U_CX_AT_UTIL_PARAM_LAST);
    ret = uCxAtClientCmdGetRspParamsF(pAtClient, "+USPS:", "d", pSpsServiceOption, U_CX_AT_UTIL_PARAM_LAST);
    if (ret >= 0) {
        ret = uCxAtClientCmdEnd(pAtClient);
    }
    return ret;
}

int32_t uCxSpsWriteString(uCxHandle_t * puCxHandle, int32_t conn_handle, const char * string_data, uCxSpsWriteString_t * pSpsWriteStringRsp)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    int32_t ret;
    uCxAtClientCmdBeginF(pAtClient, "AT+USPSWS=", "ds", conn_handle, string_data, U_CX_AT_UTIL_PARAM_LAST);
    ret = uCxAtClientCmdGetRspParamsF(pAtClient, "+USPSWS:", "dd", &pSpsWriteStringRsp->conn_handle, &pSpsWriteStringRsp->written_length, U_CX_AT_UTIL_PARAM_LAST);
    if (ret >= 0) {
        ret = uCxAtClientCmdEnd(pAtClient);
    }
    return ret;
}

int32_t uCxSpsSetDataMode(uCxHandle_t * puCxHandle, uReadMode_t read_mode)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+USPSRM=", "d", read_mode, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxSpsGetDataMode(uCxHandle_t * puCxHandle, uReadMode_t * pReadMode)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    int32_t ret;
    uCxAtClientCmdBeginF(pAtClient, "AT+USPSRM?", "", U_CX_AT_UTIL_PARAM_LAST);
    ret = uCxAtClientCmdGetRspParamsF(pAtClient, "+USPSRM:", "d", pReadMode, U_CX_AT_UTIL_PARAM_LAST);
    if (ret >= 0) {
        ret = uCxAtClientCmdEnd(pAtClient);
    }
    return ret;
}

int32_t uCxBeginSpsReadString(uCxHandle_t * puCxHandle, int32_t conn_handle, int32_t length, uCxSpsReadString_t * pSpsReadStringRsp)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    int32_t ret;
    uCxAtClientCmdBeginF(pAtClient, "AT+USPSRS=", "dd", conn_handle, length, U_CX_AT_UTIL_PARAM_LAST);
    ret = uCxAtClientCmdGetRspParamsF(pAtClient, "+USPSRS:", "dds", &pSpsReadStringRsp->conn_handle, &pSpsReadStringRsp->length, &pSpsReadStringRsp->string_data, U_CX_AT_UTIL_PARAM_LAST);
    return ret;
}
