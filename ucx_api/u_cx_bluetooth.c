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
#include "u_cx_bluetooth.h"

int32_t uCxBluetoothSetMode(uCxHandle_t * puCxHandle, uBtMode_t bt_mode)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+UBTM=", "d", bt_mode, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxBluetoothGetMode(uCxHandle_t * puCxHandle, uBtMode_t * pBtMode)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    uCxAtClientCmdBeginF(pAtClient, "AT+UBTM?", "", U_CX_AT_UTIL_PARAM_LAST);
    int32_t ret = uCxAtClientCmdGetRspParamsF(pAtClient, "+UBTM:", "d", pBtMode);
    if (ret >= 0) {
        ret = uCxAtClientCmdEnd(pAtClient);
    }
    return ret;
}

int32_t uCxBluetoothConnect(uCxHandle_t * puCxHandle, uBtLeAddress_t * bd_addr)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+UBTC=", "b", bd_addr, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxBluetoothDisconnect(uCxHandle_t * puCxHandle, int32_t conn_handle)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+UBTDC=", "d", conn_handle, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxBeginBluetoothGetLocalName(uCxHandle_t * puCxHandle, const char ** ppDeviceName)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    uCxAtClientCmdBeginF(pAtClient, "AT+UBTLN?", "", U_CX_AT_UTIL_PARAM_LAST);
    return uCxAtClientCmdGetRspParamsF(pAtClient, "+UBTLN:", "s", ppDeviceName);
}

int32_t uCxBluetoothSetLocalName(uCxHandle_t * puCxHandle, const char * device_name)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+UBTLN=", "s", device_name, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxBluetoothDiscovery(uCxHandle_t * puCxHandle)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+UBTD", "", U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxBeginBluetoothDiscoveryEx1(uCxHandle_t * puCxHandle, uDiscoveryType_t discovery_type, uCxBluetoothDiscoveryEx_t * pBluetoothDiscoveryExRsp)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    uCxAtClientCmdBeginF(pAtClient, "AT+UBTD=", "d", discovery_type, U_CX_AT_UTIL_PARAM_LAST);
    return uCxAtClientCmdGetRspParamsF(pAtClient, "+UBTD:", "bdsdh", &pBluetoothDiscoveryExRsp->bd_addr, &pBluetoothDiscoveryExRsp->rssi, &pBluetoothDiscoveryExRsp->device_name, &pBluetoothDiscoveryExRsp->data_type, &pBluetoothDiscoveryExRsp->data);
}

int32_t uCxBeginBluetoothDiscoveryEx2(uCxHandle_t * puCxHandle, uDiscoveryType_t discovery_type, uDiscoveryMode_t discovery_mode, uCxBluetoothDiscoveryEx_t * pBluetoothDiscoveryExRsp)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    uCxAtClientCmdBeginF(pAtClient, "AT+UBTD=", "dd", discovery_type, discovery_mode, U_CX_AT_UTIL_PARAM_LAST);
    return uCxAtClientCmdGetRspParamsF(pAtClient, "+UBTD:", "bdsdh", &pBluetoothDiscoveryExRsp->bd_addr, &pBluetoothDiscoveryExRsp->rssi, &pBluetoothDiscoveryExRsp->device_name, &pBluetoothDiscoveryExRsp->data_type, &pBluetoothDiscoveryExRsp->data);
}

int32_t uCxBeginBluetoothDiscoveryEx3(uCxHandle_t * puCxHandle, uDiscoveryType_t discovery_type, uDiscoveryMode_t discovery_mode, int32_t discovery_length, uCxBluetoothDiscoveryEx_t * pBluetoothDiscoveryExRsp)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    uCxAtClientCmdBeginF(pAtClient, "AT+UBTD=", "ddd", discovery_type, discovery_mode, discovery_length, U_CX_AT_UTIL_PARAM_LAST);
    return uCxAtClientCmdGetRspParamsF(pAtClient, "+UBTD:", "bdsdh", &pBluetoothDiscoveryExRsp->bd_addr, &pBluetoothDiscoveryExRsp->rssi, &pBluetoothDiscoveryExRsp->device_name, &pBluetoothDiscoveryExRsp->data_type, &pBluetoothDiscoveryExRsp->data);
}

int32_t uCxBluetoothSetBgDiscovery(uCxHandle_t * puCxHandle, uBackgroundDiscoveryMode_t background_discovery_mode)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+UBTBGD=", "d", background_discovery_mode, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxBluetoothGetBgDiscovery(uCxHandle_t * puCxHandle, uBackgroundDiscoveryMode_t * pBackgroundDiscoveryMode)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    uCxAtClientCmdBeginF(pAtClient, "AT+UBTBGD?", "", U_CX_AT_UTIL_PARAM_LAST);
    int32_t ret = uCxAtClientCmdGetRspParamsF(pAtClient, "+UBTBGD:", "d", pBackgroundDiscoveryMode);
    if (ret >= 0) {
        ret = uCxAtClientCmdEnd(pAtClient);
    }
    return ret;
}

int32_t uCxBluetoothRssi(uCxHandle_t * puCxHandle, int32_t conn_handle, int32_t * pRssi)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    uCxAtClientCmdBeginF(pAtClient, "AT+UBTRSS=", "d", conn_handle, U_CX_AT_UTIL_PARAM_LAST);
    int32_t ret = uCxAtClientCmdGetRspParamsF(pAtClient, "+UBTRSS:", "d", pRssi);
    if (ret >= 0) {
        ret = uCxAtClientCmdEnd(pAtClient);
    }
    return ret;
}

int32_t uCxBluetoothConnectionStatus1(uCxHandle_t * puCxHandle, int32_t conn_handle, uCxBluetoothConnectionStatus_t * pBluetoothConnectionStatusRsp)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    uCxAtClientCmdBeginF(pAtClient, "AT+UBTCST=", "d", conn_handle, U_CX_AT_UTIL_PARAM_LAST);
    int32_t ret = uCxAtClientCmdGetRspParamsF(pAtClient, "+UBTCST:", "dd", &pBluetoothConnectionStatusRsp->property_id, &pBluetoothConnectionStatusRsp->status_val);
    if (ret >= 0) {
        ret = uCxAtClientCmdEnd(pAtClient);
    }
    return ret;
}

int32_t uCxBluetoothConnectionStatus2(uCxHandle_t * puCxHandle, int32_t conn_handle, uPropertyId_t property_id, uCxBluetoothConnectionStatus_t * pBluetoothConnectionStatusRsp)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    uCxAtClientCmdBeginF(pAtClient, "AT+UBTCST=", "dd", conn_handle, property_id, U_CX_AT_UTIL_PARAM_LAST);
    int32_t ret = uCxAtClientCmdGetRspParamsF(pAtClient, "+UBTCST:", "dd", &pBluetoothConnectionStatusRsp->property_id, &pBluetoothConnectionStatusRsp->status_val);
    if (ret >= 0) {
        ret = uCxAtClientCmdEnd(pAtClient);
    }
    return ret;
}

int32_t uCxBluetoothSetAdvertiseData(uCxHandle_t * puCxHandle, const uint8_t * adv_data, int32_t adv_data_len)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+UBTAD=", "h", adv_data, adv_data_len, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxBeginBluetoothGetAdvertiseData(uCxHandle_t * puCxHandle, uByteArray_t * pAdvData)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    uCxAtClientCmdBeginF(pAtClient, "AT+UBTAD?", "", U_CX_AT_UTIL_PARAM_LAST);
    return uCxAtClientCmdGetRspParamsF(pAtClient, "+UBTAD:", "h", pAdvData);
}

int32_t uCxBluetoothSetScanResponseData(uCxHandle_t * puCxHandle, const uint8_t * scan_rsp_data, int32_t scan_rsp_data_len)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+UBTSD=", "h", scan_rsp_data, scan_rsp_data_len, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxBeginBluetoothGetScanResponseData(uCxHandle_t * puCxHandle, uByteArray_t * pScanRspData)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    uCxAtClientCmdBeginF(pAtClient, "AT+UBTSD?", "", U_CX_AT_UTIL_PARAM_LAST);
    return uCxAtClientCmdGetRspParamsF(pAtClient, "+UBTSD:", "h", pScanRspData);
}

int32_t uCxBluetoothSetAdvertisements(uCxHandle_t * puCxHandle, uAdvMode_t adv_mode)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+UBTA=", "d", adv_mode, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxBluetoothGetAdvertisements(uCxHandle_t * puCxHandle, uAdvMode_t * pAdvMode)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    uCxAtClientCmdBeginF(pAtClient, "AT+UBTA?", "", U_CX_AT_UTIL_PARAM_LAST);
    int32_t ret = uCxAtClientCmdGetRspParamsF(pAtClient, "+UBTA:", "d", pAdvMode);
    if (ret >= 0) {
        ret = uCxAtClientCmdEnd(pAtClient);
    }
    return ret;
}

int32_t uCxBluetoothDirectedAdvertisement1(uCxHandle_t * puCxHandle, uBtLeAddress_t * bd_addr)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+UBTDA=", "b", bd_addr, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxBluetoothDirectedAdvertisement2(uCxHandle_t * puCxHandle, uBtLeAddress_t * bd_addr, int32_t timeout)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+UBTDA=", "bd", bd_addr, timeout, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxBluetoothSetIoCapabilities(uCxHandle_t * puCxHandle, uIoCapabilities_t io_capabilities)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+UBTIOC=", "d", io_capabilities, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxBluetoothGetIoCapabilities(uCxHandle_t * puCxHandle, uIoCapabilities_t * pIoCapabilities)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    uCxAtClientCmdBeginF(pAtClient, "AT+UBTIOC?", "", U_CX_AT_UTIL_PARAM_LAST);
    int32_t ret = uCxAtClientCmdGetRspParamsF(pAtClient, "+UBTIOC:", "d", pIoCapabilities);
    if (ret >= 0) {
        ret = uCxAtClientCmdEnd(pAtClient);
    }
    return ret;
}

int32_t uCxBluetoothSetSecurityMode(uCxHandle_t * puCxHandle, uBtSecurityMode_t bt_security_mode)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+UBTBSM=", "d", bt_security_mode, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxBluetoothGetSecurityMode(uCxHandle_t * puCxHandle, uBtSecurityMode_t * pBtSecurityMode)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    uCxAtClientCmdBeginF(pAtClient, "AT+UBTBSM?", "", U_CX_AT_UTIL_PARAM_LAST);
    int32_t ret = uCxAtClientCmdGetRspParamsF(pAtClient, "+UBTBSM:", "d", pBtSecurityMode);
    if (ret >= 0) {
        ret = uCxAtClientCmdEnd(pAtClient);
    }
    return ret;
}

int32_t uCxBluetoothSetPairingMode(uCxHandle_t * puCxHandle, uPairingMode_t pairing_mode)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+UBTPM=", "d", pairing_mode, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxBluetoothGetPairingMode(uCxHandle_t * puCxHandle, uPairingMode_t * pPairingMode)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    uCxAtClientCmdBeginF(pAtClient, "AT+UBTPM?", "", U_CX_AT_UTIL_PARAM_LAST);
    int32_t ret = uCxAtClientCmdGetRspParamsF(pAtClient, "+UBTPM:", "d", pPairingMode);
    if (ret >= 0) {
        ret = uCxAtClientCmdEnd(pAtClient);
    }
    return ret;
}

int32_t uCxBluetoothUserConfirmation(uCxHandle_t * puCxHandle, uBtLeAddress_t * bd_addr, uYesNo_t yes_no)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+UBTUC=", "bd", bd_addr, yes_no, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxBluetoothUserPasskeyEntry2(uCxHandle_t * puCxHandle, uBtLeAddress_t * bd_addr, uYesNo_t yes_no)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+UBTUPE=", "bd", bd_addr, yes_no, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxBluetoothUserPasskeyEntry3(uCxHandle_t * puCxHandle, uBtLeAddress_t * bd_addr, uYesNo_t yes_no, int32_t passkey)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+UBTUPE=", "bdd", bd_addr, yes_no, passkey, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxBluetoothBond(uCxHandle_t * puCxHandle, uBtLeAddress_t * bd_addr)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+UBTB=", "b", bd_addr, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxBluetoothUnbond(uCxHandle_t * puCxHandle, uBtLeAddress_t * bd_addr)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+UBTUB=", "b", bd_addr, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxBluetoothRequestPhy(uCxHandle_t * puCxHandle, int32_t conn_handle, int32_t tx_phy, int32_t rx_phy)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+UBTPHYR=", "ddd", conn_handle, tx_phy, rx_phy, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxBluetoothGetPhy(uCxHandle_t * puCxHandle, int32_t conn_handle, uCxBluetoothGetPhy_t * pBluetoothGetPhyRsp)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    uCxAtClientCmdBeginF(pAtClient, "AT+UBTPHYR=", "d", conn_handle, U_CX_AT_UTIL_PARAM_LAST);
    int32_t ret = uCxAtClientCmdGetRspParamsF(pAtClient, "+UBTPHYR:", "ddd", &pBluetoothGetPhyRsp->conn_handle, &pBluetoothGetPhyRsp->tx_phy, &pBluetoothGetPhyRsp->rx_phy);
    if (ret >= 0) {
        ret = uCxAtClientCmdEnd(pAtClient);
    }
    return ret;
}
