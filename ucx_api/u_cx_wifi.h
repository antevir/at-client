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
#ifndef _U_CX_WIFI_H_
#define _U_CX_WIFI_H_

#include <stddef.h>
#include <stdint.h>
#include "u_cx_types.h"
#include "u_cx.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* ------------------------------------------------------------
 * RESPONSE STRUCTS
 * ---------------------------------------------------------- */

typedef struct
{
    int32_t wlan_handle; /**< Handle to use for Wi-Fi config and connection */
    const char * ssid;   /**< SSID */
} uCxWifiStationGetConnectionParams_t;

typedef struct
{
    int32_t status_id;
    uSockIpAddress_t status_val; /**< IP address */
} uCxWifiStationGetNetworkStatus_t;

typedef struct
{
    const char * ssid; /**< SSID */
    int32_t channel;   /**< channel */
} uCxWifiApGetConnectionParams_t;

/* ------------------------------------------------------------
 * PUBLIC FUNCTIONS
 * ---------------------------------------------------------- */

/**
 * Set the Host Name
 * 
 * Output AT command:
 * > AT+UWHN=<host_name>
 *
 * @param[in]  puCxHandle: uCX API handle
 * @param      host_name:  
 */
int32_t uCxWifiSetHostname(uCxHandle_t * puCxHandle, const char * host_name);

/**
 * Reads the current hostname
 * 
 * Output AT command:
 * > AT+UWHN?
 *
 * @param[in]  puCxHandle: uCX API handle
 * @param[out] ppHostName: 
 */
int32_t uCxBeginWifiGetHostname(uCxHandle_t * puCxHandle, const char ** ppHostName);

/**
 * Set the EAP-TLS connection parameters to use.
 * 
 * Output AT command:
 * > AT+UWSSE=<wlan_handle>,<ca_name>,<client_cert_name>,<client_key_name>
 *
 * @param[in]  puCxHandle:       uCX API handle
 * @param      wlan_handle:      Handle to use for Wi-Fi config and connection
 * @param      ca_name:          Name of the certificate authority (CA) certificate to use
 * @param      client_cert_name: Name of the client certificate to use
 * @param      client_key_name:  Name of the private key for client certificate
 */
int32_t uCxWifiStationSetSecurityEnterprise(uCxHandle_t * puCxHandle, int32_t wlan_handle, const char * ca_name, const char * client_cert_name, const char * client_key_name);

/**
 * Set the PEAP connection parameters to use.
 * 
 * Output AT command:
 * > AT+UWSSP=<wlan_handle>,<peap_user>,<peap_password>
 *
 * @param[in]  puCxHandle:    uCX API handle
 * @param      wlan_handle:   Handle to use for Wi-Fi config and connection
 * @param      peap_user:     User name for PEAP authentication. Could be either only username or username@domain. Use @
 *                            as separator
 * @param      peap_password: Password for PEAP authentication.
 */
int32_t uCxWifiStationSetSecurityPeap3(uCxHandle_t * puCxHandle, int32_t wlan_handle, const char * peap_user, const char * peap_password);

/**
 * Set the PEAP connection parameters to use.
 * 
 * Output AT command:
 * > AT+UWSSP=<wlan_handle>,<peap_user>,<peap_password>,<ca_name>
 *
 * @param[in]  puCxHandle:    uCX API handle
 * @param      wlan_handle:   Handle to use for Wi-Fi config and connection
 * @param      peap_user:     User name for PEAP authentication. Could be either only username or username@domain. Use @
 *                            as separator
 * @param      peap_password: Password for PEAP authentication.
 * @param      ca_name:       Name of the certificate authority (CA) certificate to use
 */
int32_t uCxWifiStationSetSecurityPeap4(uCxHandle_t * puCxHandle, int32_t wlan_handle, const char * peap_user, const char * peap_password, const char * ca_name);

/**
 * Set WPA connection parameters to use
 * 
 * Output AT command:
 * > AT+UWSSW=<wlan_handle>,<passphrase>,<wpa_threshold>
 *
 * @param[in]  puCxHandle:    uCX API handle
 * @param      wlan_handle:   Handle to use for Wi-Fi config and connection
 * @param      passphrase:    Passphrase to use for WPA connection
 * @param      wpa_threshold: Lowest WPA version to connect to
 */
int32_t uCxWifiStationSetSecurityWpa(uCxHandle_t * puCxHandle, int32_t wlan_handle, const char * passphrase, uWpaThreshold_t wpa_threshold);

/**
 * Sets security to open security
 * 
 * Output AT command:
 * > AT+UWSSO=<wlan_handle>
 *
 * @param[in]  puCxHandle:  uCX API handle
 * @param      wlan_handle: Handle to use for Wi-Fi config and connection
 */
int32_t uCxWifiStationSetSecurityOpen(uCxHandle_t * puCxHandle, int32_t wlan_handle);

/**
 * Sets the connection parameters for the connection.
 * 
 * Output AT command:
 * > AT+UWSCP=<wlan_handle>,<ssid>
 *
 * @param[in]  puCxHandle:  uCX API handle
 * @param      wlan_handle: Handle to use for Wi-Fi config and connection
 * @param      ssid:        SSID
 */
int32_t uCxWifiStationSetConnectionParams(uCxHandle_t * puCxHandle, int32_t wlan_handle, const char * ssid);

/**
 * Reads the connection parameters for the connection.
 * 
 * Output AT command:
 * > AT+UWSCP=<wlan_handle>
 *
 * @param[in]  puCxHandle:                         uCX API handle
 * @param      wlan_handle:                        Handle to use for Wi-Fi config and connection
 * @param[out] pWifiStationGetConnectionParamsRsp: Please see \ref uCxWifiStationGetConnectionParams_t
 */
int32_t uCxBeginWifiStationGetConnectionParams(uCxHandle_t * puCxHandle, int32_t wlan_handle, uCxWifiStationGetConnectionParams_t * pWifiStationGetConnectionParamsRsp);

/**
 * Sets ip configuration to use static ip
 * 
 * Output AT command:
 * > AT+UWSIPS=<wlan_handle>,<ip_addr>,<subnet_mask>,<gateway>
 *
 * @param[in]  puCxHandle:  uCX API handle
 * @param      wlan_handle: Handle to use for Wi-Fi config and connection
 * @param      ip_addr:     Static IPv4 address
 * @param      subnet_mask: Subnet mask
 * @param      gateway:     IPv4 gateway address
 */
int32_t uCxWifiStationSetIpConfigStatic4(uCxHandle_t * puCxHandle, int32_t wlan_handle, uSockIpAddress_t * ip_addr, uSockIpAddress_t * subnet_mask, uSockIpAddress_t * gateway);

/**
 * Sets ip configuration to use static ip
 * 
 * Output AT command:
 * > AT+UWSIPS=<wlan_handle>,<ip_addr>,<subnet_mask>,<gateway>,<prim_dns>
 *
 * @param[in]  puCxHandle:  uCX API handle
 * @param      wlan_handle: Handle to use for Wi-Fi config and connection
 * @param      ip_addr:     Static IPv4 address
 * @param      subnet_mask: Subnet mask
 * @param      gateway:     IPv4 gateway address
 * @param      prim_dns:    IPv4 primary dns address
 */
int32_t uCxWifiStationSetIpConfigStatic5(uCxHandle_t * puCxHandle, int32_t wlan_handle, uSockIpAddress_t * ip_addr, uSockIpAddress_t * subnet_mask, uSockIpAddress_t * gateway, uSockIpAddress_t * prim_dns);

/**
 * Sets ip configuration to use static ip
 * 
 * Output AT command:
 * > AT+UWSIPS=<wlan_handle>,<ip_addr>,<subnet_mask>,<gateway>,<prim_dns>,<sec_dns>
 *
 * @param[in]  puCxHandle:  uCX API handle
 * @param      wlan_handle: Handle to use for Wi-Fi config and connection
 * @param      ip_addr:     Static IPv4 address
 * @param      subnet_mask: Subnet mask
 * @param      gateway:     IPv4 gateway address
 * @param      prim_dns:    IPv4 primary dns address
 * @param      sec_dns:     IPv4 secondary dns address
 */
int32_t uCxWifiStationSetIpConfigStatic6(uCxHandle_t * puCxHandle, int32_t wlan_handle, uSockIpAddress_t * ip_addr, uSockIpAddress_t * subnet_mask, uSockIpAddress_t * gateway, uSockIpAddress_t * prim_dns, uSockIpAddress_t * sec_dns);

/**
 * Sets ip configuration to receive ip address via dhcp
 * 
 * Output AT command:
 * > AT+UWSIPD=<wlan_handle>
 *
 * @param[in]  puCxHandle:  uCX API handle
 * @param      wlan_handle: Handle to use for Wi-Fi config and connection
 */
int32_t uCxWifiStationSetIpConfigDhcp(uCxHandle_t * puCxHandle, int32_t wlan_handle);

/**
 * Initiate connection to Wi-Fi network
 * 
 * Output AT command:
 * > AT+UWSC=<wlan_handle>
 *
 * @param[in]  puCxHandle:  uCX API handle
 * @param      wlan_handle: Handle to use for Wi-Fi config and connection
 */
int32_t uCxWifiStationConnect(uCxHandle_t * puCxHandle, int32_t wlan_handle);

/**
 * Disconnect from Wi-Fi network
 * 
 * Output AT command:
 * > AT+UWSDC
 *
 * @param[in]  puCxHandle: uCX API handle
 */
int32_t uCxWifiStationDisconnect(uCxHandle_t * puCxHandle);

/**
 * Show current status of Wi-Fi station network interface
 * 
 * Output AT command:
 * > AT+UWSNST=<status_id>
 *
 * @param[in]  puCxHandle:                      uCX API handle
 * @param      status_id:                       
 * @param[out] pWifiStationGetNetworkStatusRsp: Please see \ref uCxWifiStationGetNetworkStatus_t
 */
int32_t uCxBeginWifiStationGetNetworkStatus(uCxHandle_t * puCxHandle, uStatusId_t status_id, uCxWifiStationGetNetworkStatus_t * pWifiStationGetNetworkStatusRsp);

/**
 * Start an access point with the current access point configuration.
 * 
 * Output AT command:
 * > AT+UWAPA
 *
 * @param[in]  puCxHandle: uCX API handle
 */
int32_t uCxWifiApActivate(uCxHandle_t * puCxHandle);

/**
 * Brings down Wi-Fi access point and disconnect all connected stations
 * 
 * Output AT command:
 * > AT+UWAPD
 *
 * @param[in]  puCxHandle: uCX API handle
 */
int32_t uCxWifiApDeactivate(uCxHandle_t * puCxHandle);

/**
 * Sets connection parameters for the AP configuration
 * 
 * Output AT command:
 * > AT+UWAPCP=<ssid>
 *
 * @param[in]  puCxHandle: uCX API handle
 * @param      ssid:       SSID
 */
int32_t uCxWifiApSetConnectionParams1(uCxHandle_t * puCxHandle, const char * ssid);

/**
 * Sets connection parameters for the AP configuration
 * 
 * Output AT command:
 * > AT+UWAPCP=<ssid>,<channel>
 *
 * @param[in]  puCxHandle: uCX API handle
 * @param      ssid:       SSID
 * @param      channel:    channel
 */
int32_t uCxWifiApSetConnectionParams2(uCxHandle_t * puCxHandle, const char * ssid, uChannel_t channel);

/**
 * Read the current connection parameters
 * 
 * Output AT command:
 * > AT+UWAPCP?
 *
 * @param[in]  puCxHandle:                    uCX API handle
 * @param[out] pWifiApGetConnectionParamsRsp: Please see \ref uCxWifiApGetConnectionParams_t
 */
int32_t uCxBeginWifiApGetConnectionParams(uCxHandle_t * puCxHandle, uCxWifiApGetConnectionParams_t * pWifiApGetConnectionParamsRsp);

/**
 * Sets WPA parameters for the AP config
 * 
 * Output AT command:
 * > AT+UWAPSW=<passphrase>
 *
 * @param[in]  puCxHandle: uCX API handle
 * @param      passphrase: Passphrase to use
 */
int32_t uCxWifiApSetSecurityWpa1(uCxHandle_t * puCxHandle, const char * passphrase);

/**
 * Sets WPA parameters for the AP config
 * 
 * Output AT command:
 * > AT+UWAPSW=<passphrase>,<wpa_version>
 *
 * @param[in]  puCxHandle:  uCX API handle
 * @param      passphrase:  Passphrase to use
 * @param      wpa_version: 
 */
int32_t uCxWifiApSetSecurityWpa2(uCxHandle_t * puCxHandle, const char * passphrase, uWpaVersion_t wpa_version);

/**
 * Sets security level to open for the AP config
 * 
 * Output AT command:
 * > AT+UWAPSO
 *
 * @param[in]  puCxHandle: uCX API handle
 */
int32_t uCxWifiApSetSecurityOpen(uCxHandle_t * puCxHandle);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _U_CX_WIFI_H_ */