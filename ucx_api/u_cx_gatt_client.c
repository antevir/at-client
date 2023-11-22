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
#include "u_cx_gatt_client.h"

int32_t uCxBeginGattClientRead(uCxHandle_t * puCxHandle, int32_t conn_handle, int32_t value_handle, uCxGattClientRead_t * pGattClientReadRsp)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    uCxAtClientCmdBeginF(pAtClient, "AT+UBTGR=", "dd", conn_handle, value_handle, U_CX_AT_UTIL_PARAM_LAST);
    return uCxAtClientCmdGetRspParamsF(pAtClient, "+UBTGR:", "ddh", &pGattClientReadRsp->conn_handle, &pGattClientReadRsp->value_handle, &pGattClientReadRsp->hex_data);
}

int32_t uCxBeginGattClientReadByUuid(uCxHandle_t * puCxHandle, int32_t conn_handle, int32_t start, int32_t end, const uint8_t * uuid, int32_t uuid_len, uCxGattClientReadByUuid_t * pGattClientReadByUuidRsp)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    uCxAtClientCmdBeginF(pAtClient, "AT+UBTGRU=", "dddh", conn_handle, start, end, uuid, uuid_len, U_CX_AT_UTIL_PARAM_LAST);
    return uCxAtClientCmdGetRspParamsF(pAtClient, "+UBTGRU:", "ddh", &pGattClientReadByUuidRsp->conn_handle, &pGattClientReadByUuidRsp->value_handle, &pGattClientReadByUuidRsp->hex_data);
}

int32_t uCxGattClientWrite(uCxHandle_t * puCxHandle, int32_t conn_handle, int32_t value_handle, const uint8_t * hex_data, int32_t hex_data_len)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+UBTGW=", "ddh", conn_handle, value_handle, hex_data, hex_data_len, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxGattClientConfigWrite(uCxHandle_t * puCxHandle, int32_t conn_handle, int32_t desc_handle, uConfig_t config)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+UBTGCCW=", "ddd", conn_handle, desc_handle, config, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxGattClientWriteNoRsp(uCxHandle_t * puCxHandle, int32_t conn_handle, int32_t value_handle, const uint8_t * hex_data, int32_t hex_data_len)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+UBTGWNR=", "ddh", conn_handle, value_handle, hex_data, hex_data_len, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxGattClientWriteLong(uCxHandle_t * puCxHandle, int32_t conn_handle, int32_t value_handle, const char * hex_data, uReliable_t reliable, uFlag_t flag, int32_t offset)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+UBTGWL=", "ddsddd", conn_handle, value_handle, hex_data, reliable, flag, offset, U_CX_AT_UTIL_PARAM_LAST);
}
