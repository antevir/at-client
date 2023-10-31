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
#include "u_cx_general.h"

int32_t uCxGeneralAttention(uCxAtClient_t * pAtClient)
{
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT", "", U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxBeginGeneralGetManufacturerIdentification(uCxAtClient_t * pAtClient, const char * * pManufacturer)
{
    uCxAtClientCmdBeginF(pAtClient, "AT+GMI", "", U_CX_AT_UTIL_PARAM_LAST);
    return uCxAtClientCmdGetRspParamsF(pAtClient, "", "s", pManufacturer);
}

int32_t uCxBeginGeneralGetDeviceModelIdentification(uCxAtClient_t * pAtClient, const char * * pDeviceModel)
{
    uCxAtClientCmdBeginF(pAtClient, "AT+GMM", "", U_CX_AT_UTIL_PARAM_LAST);
    return uCxAtClientCmdGetRspParamsF(pAtClient, "", "s", pDeviceModel);
}

int32_t uCxBeginGeneralGetSoftwareVersion(uCxAtClient_t * pAtClient, const char * * pVersion)
{
    uCxAtClientCmdBeginF(pAtClient, "AT+GMR", "", U_CX_AT_UTIL_PARAM_LAST);
    return uCxAtClientCmdGetRspParamsF(pAtClient, "", "s", pVersion);
}

int32_t uCxBeginGeneralGetSerialNumber(uCxAtClient_t * pAtClient, const char * * pSerialNumber)
{
    uCxAtClientCmdBeginF(pAtClient, "AT+GSN", "", U_CX_AT_UTIL_PARAM_LAST);
    return uCxAtClientCmdGetRspParamsF(pAtClient, "", "s", pSerialNumber);
}
