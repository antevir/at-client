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
#include "u_cx_wifi.h"

int32_t uCxWifiSetHostname(uCxHandle_t * puCxHandle, const char * host_name)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+UWHN=", "s", host_name, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxBeginWifiGetHostname(uCxHandle_t * puCxHandle, const char ** ppHostName)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    uCxAtClientCmdBeginF(pAtClient, "AT+UWHN?", "", U_CX_AT_UTIL_PARAM_LAST);
    return uCxAtClientCmdGetRspParamsF(pAtClient, "+UWHN:", "s", ppHostName);
}

int32_t uCxWifiStationSetSecurityEnterprise(uCxHandle_t * puCxHandle, int32_t wlan_handle, const char * ca_name, const char * client_cert_name, const char * client_key_name)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+UWSSE=", "dsss", wlan_handle, ca_name, client_cert_name, client_key_name, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxWifiStationSetSecurityPeap3(uCxHandle_t * puCxHandle, int32_t wlan_handle, const char * peap_user, const char * peap_password)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+UWSSP=", "dss", wlan_handle, peap_user, peap_password, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxWifiStationSetSecurityPeap4(uCxHandle_t * puCxHandle, int32_t wlan_handle, const char * peap_user, const char * peap_password, const char * ca_name)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+UWSSP=", "dsss", wlan_handle, peap_user, peap_password, ca_name, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxWifiStationSetSecurityWpa(uCxHandle_t * puCxHandle, int32_t wlan_handle, const char * passphrase, uWpaThreshold_t wpa_threshold)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+UWSSW=", "dsd", wlan_handle, passphrase, wpa_threshold, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxWifiStationSetSecurityOpen(uCxHandle_t * puCxHandle, int32_t wlan_handle)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+UWSSO=", "d", wlan_handle, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxWifiStationSetConnectionParams(uCxHandle_t * puCxHandle, int32_t wlan_handle, const char * ssid)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+UWSCP=", "ds", wlan_handle, ssid, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxBeginWifiStationGetConnectionParams(uCxHandle_t * puCxHandle, int32_t wlan_handle, uCxWifiStationGetConnectionParams_t * pWifiStationGetConnectionParamsRsp)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    uCxAtClientCmdBeginF(pAtClient, "AT+UWSCP=", "d", wlan_handle, U_CX_AT_UTIL_PARAM_LAST);
    return uCxAtClientCmdGetRspParamsF(pAtClient, "+UWSCP=", "ds", &pWifiStationGetConnectionParamsRsp->wlan_handle, &pWifiStationGetConnectionParamsRsp->ssid);
}

int32_t uCxWifiStationSetIpConfigStatic4(uCxHandle_t * puCxHandle, int32_t wlan_handle, uSockIpAddress_t * ip_addr, uSockIpAddress_t * subnet_mask, uSockIpAddress_t * gateway)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+UWSIPS=", "diii", wlan_handle, ip_addr, subnet_mask, gateway, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxWifiStationSetIpConfigStatic5(uCxHandle_t * puCxHandle, int32_t wlan_handle, uSockIpAddress_t * ip_addr, uSockIpAddress_t * subnet_mask, uSockIpAddress_t * gateway, uSockIpAddress_t * prim_dns)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+UWSIPS=", "diiii", wlan_handle, ip_addr, subnet_mask, gateway, prim_dns, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxWifiStationSetIpConfigStatic6(uCxHandle_t * puCxHandle, int32_t wlan_handle, uSockIpAddress_t * ip_addr, uSockIpAddress_t * subnet_mask, uSockIpAddress_t * gateway, uSockIpAddress_t * prim_dns, uSockIpAddress_t * sec_dns)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+UWSIPS=", "diiiii", wlan_handle, ip_addr, subnet_mask, gateway, prim_dns, sec_dns, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxWifiStationSetIpConfigDhcp(uCxHandle_t * puCxHandle, int32_t wlan_handle)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+UWSIPD=", "d", wlan_handle, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxWifiStationConnect(uCxHandle_t * puCxHandle, int32_t wlan_handle)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+UWSC=", "d", wlan_handle, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxWifiStationDisconnect(uCxHandle_t * puCxHandle)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+UWSDC", "", U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxWifiStationGetNetworkStatus(uCxHandle_t * puCxHandle, uStatusId_t status_id, uCxWifiStationGetNetworkStatus_t * pWifiStationGetNetworkStatusRsp)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    uCxAtClientCmdBeginF(pAtClient, "AT+UWSNST=", "d", status_id, U_CX_AT_UTIL_PARAM_LAST);
    int32_t ret = uCxAtClientCmdGetRspParamsF(pAtClient, "+UWSNST:", "di", &pWifiStationGetNetworkStatusRsp->status_id, &pWifiStationGetNetworkStatusRsp->status_val);
    if (ret >= 0) {
        ret = uCxAtClientCmdEnd(pAtClient);
    }
    return ret;
}

int32_t uCxWifiApActivate(uCxHandle_t * puCxHandle)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+UWAPA", "", U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxWifiApDeactivate(uCxHandle_t * puCxHandle)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+UWAPD", "", U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxWifiApSetConnectionParams1(uCxHandle_t * puCxHandle, const char * ssid)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+UWAPCP=", "s", ssid, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxWifiApSetConnectionParams2(uCxHandle_t * puCxHandle, const char * ssid, uChannel_t channel)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+UWAPCP=", "sd", ssid, channel, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxBeginWifiApGetConnectionParams(uCxHandle_t * puCxHandle, uCxWifiApGetConnectionParams_t * pWifiApGetConnectionParamsRsp)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    uCxAtClientCmdBeginF(pAtClient, "AT+UWAPCP?", "", U_CX_AT_UTIL_PARAM_LAST);
    return uCxAtClientCmdGetRspParamsF(pAtClient, "+UWAPCP:", "sd", &pWifiApGetConnectionParamsRsp->ssid, &pWifiApGetConnectionParamsRsp->channel);
}

int32_t uCxWifiApSetSecurityWpa1(uCxHandle_t * puCxHandle, const char * passphrase)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+UWAPSW=", "s", passphrase, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxWifiApSetSecurityWpa2(uCxHandle_t * puCxHandle, const char * passphrase, uWpaVersion_t wpa_version)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+UWAPSW=", "sd", passphrase, wpa_version, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxWifiApSetSecurityOpen(uCxHandle_t * puCxHandle)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+UWAPSO", "", U_CX_AT_UTIL_PARAM_LAST);
}
