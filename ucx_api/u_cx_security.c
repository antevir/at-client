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
#include "u_cx_security.h"

int32_t uCxSecurityCertificateRemove(uCxHandle_t * puCxHandle, uCertType_t cert_type, const char * name)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+USECR=", "ds", cert_type, name, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxSecurityCertificateRemoveAll(uCxHandle_t * puCxHandle, uRemoveAll_t remove_all)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+USECR=", "d", remove_all, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxSecuritySetTlsServerNameIndication(uCxHandle_t * puCxHandle, uEnabled_t enabled)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+USETE0=", "d", enabled, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxSecurityGetTlsServerNameIndication(uCxHandle_t * puCxHandle, uEnabled_t * pEnabled)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    int32_t ret;
    uCxAtClientCmdBeginF(pAtClient, "AT+USETE0?", "", U_CX_AT_UTIL_PARAM_LAST);
    ret = uCxAtClientCmdGetRspParamsF(pAtClient, "+USETE0:", "d", pEnabled, U_CX_AT_UTIL_PARAM_LAST);
    if (ret >= 0) {
        ret = uCxAtClientCmdEnd(pAtClient);
    }
    return ret;
}

int32_t uCxSecuritySetTlsHandshakeFrag(uCxHandle_t * puCxHandle, uEnabled_t enabled)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+USETE1=", "d", enabled, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxSecurityGetTlsHandshakeFrag(uCxHandle_t * puCxHandle, uEnabled_t * pEnabled)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    int32_t ret;
    uCxAtClientCmdBeginF(pAtClient, "AT+USETE1?", "", U_CX_AT_UTIL_PARAM_LAST);
    ret = uCxAtClientCmdGetRspParamsF(pAtClient, "+USETE1:", "d", pEnabled, U_CX_AT_UTIL_PARAM_LAST);
    if (ret >= 0) {
        ret = uCxAtClientCmdEnd(pAtClient);
    }
    return ret;
}
