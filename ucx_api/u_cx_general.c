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
#include "u_cx_general.h"

int32_t uCxGeneralAttention(uCxHandle_t * puCxHandle)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT", "", U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxBeginGeneralGetManufacturerIdentification(uCxHandle_t * puCxHandle, const char * * pManufacturer)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    uCxAtClientCmdBeginF(pAtClient, "AT+GMI", "", U_CX_AT_UTIL_PARAM_LAST);
    return uCxAtClientCmdGetRspParamsF(pAtClient, "", "s", pManufacturer);
}

int32_t uCxBeginGeneralGetDeviceModelIdentification(uCxHandle_t * puCxHandle, const char * * pDeviceModel)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    uCxAtClientCmdBeginF(pAtClient, "AT+GMM", "", U_CX_AT_UTIL_PARAM_LAST);
    return uCxAtClientCmdGetRspParamsF(pAtClient, "", "s", pDeviceModel);
}

int32_t uCxBeginGeneralGetSoftwareVersion(uCxHandle_t * puCxHandle, const char * * pVersion)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    uCxAtClientCmdBeginF(pAtClient, "AT+GMR", "", U_CX_AT_UTIL_PARAM_LAST);
    return uCxAtClientCmdGetRspParamsF(pAtClient, "", "s", pVersion);
}

int32_t uCxBeginGeneralGetSerialNumber(uCxHandle_t * puCxHandle, const char * * pSerialNumber)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    uCxAtClientCmdBeginF(pAtClient, "AT+GSN", "", U_CX_AT_UTIL_PARAM_LAST);
    return uCxAtClientCmdGetRspParamsF(pAtClient, "", "s", pSerialNumber);
}
