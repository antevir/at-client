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
#ifndef _U_CX_TYPES_H_
#define _U_CX_TYPES_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdint.h>
#include <stdbool.h>

/* ------------------------------------------------------------
 * ENUMS
 * ---------------------------------------------------------- */

typedef enum
{
    U_INTERFACE_ID_BLUETOOTH,         /**< Bluetooth */
    U_INTERFACE_ID_WI_FI_STATION = 1, /**< Wifi station */
    U_INTERFACE_ID_WIFI_AP = 2        /**< Wifi Accesspoint */
} uInterfaceId_t;

typedef enum
{
    U_BOOTLOADER_MODE_XMODEM,          /**< Enter xmodem mode for u-connect software update using serial port. */
    U_BOOTLOADER_MODE_COMMAND_LINE = 1 /**< Enter the bootloader command line mode using serial port. */
} uBootloaderMode_t;

typedef enum
{
    U_ECHO_ON_OFF,   /**< Module does not echo the characters */
    U_ECHO_ON_ON = 1 /**< (Factory default) Module echoes the characters */
} uEchoOn_t;

typedef enum
{
    U_WPA_THRESHOLD_WPA2,    /**< Only connect to access points that support WPA2 or up */
    U_WPA_THRESHOLD_WPA3 = 1 /**< Only connect to access points that support WPA3 */
} uWpaThreshold_t;

typedef enum
{
    U_STATUS_ID_IPV4,         /**< The current IPv4 address. */
    U_STATUS_ID_SUBNET = 1,   /**< The current subnet mask */
    U_STATUS_ID_GATE_WAY = 2, /**< The current gateway */
    U_STATUS_ID_PRIM_DNS = 3, /**< The current primary DNS server */
    U_STATUS_ID_SEC_DNS = 4,  /**< The current secondary DNS server */
    U_STATUS_ID_IPV6 = 5      /**< The current IPv6 link local address */
} uStatusId_t;

typedef enum
{
    U_CHANNEL1 = 1,   /**< 1 */
    U_CHANNEL2 = 2,   /**< 2 */
    U_CHANNEL3 = 3,   /**< 3 */
    U_CHANNEL4 = 4,   /**< 4 */
    U_CHANNEL5 = 5,   /**< 5 */
    U_CHANNEL6 = 6,   /**< 6 */
    U_CHANNEL7 = 7,   /**< 7 */
    U_CHANNEL8 = 8,   /**< 8 */
    U_CHANNEL9 = 9,   /**< 9 */
    U_CHANNEL10 = 10, /**< 10 */
    U_CHANNEL11 = 11, /**< 11 */
    U_CHANNEL36 = 36, /**< 36 */
    U_CHANNEL40 = 40, /**< 40 */
    U_CHANNEL44 = 44, /**< 44 */
    U_CHANNEL48 = 48  /**< 48 */
} uChannel_t;

typedef enum
{
    U_WPA_VERSION_WPA2 /**< WPA 2 */
} uWpaVersion_t;

typedef enum
{
    U_PROTOCOL_TCP = 6, /**< TCP */
    U_PROTOCOL_UDP = 17 /**< UDP */
} uProtocol_t;

typedef enum
{
    U_PREFERRED_PROTOCOL_TYPE_IP_V4,    /**< IPv4 address. */
    U_PREFERRED_PROTOCOL_TYPE_IP_V6 = 1 /**< IPv6 address. */
} uPreferredProtocolType_t;

typedef enum
{
    U_READ_MODE_BUFFERED,          /**< Buffered mode */
    U_READ_MODE_DIRECT_STRING = 1, /**< Direct String mode */
    U_READ_MODE_DIRECT_BINARY = 2  /**< Direct Binary Mode */
} uReadMode_t;

typedef enum
{
    U_SOCKET_STATUS_NOT_CONNECTED, /**< Not Connected */
    U_SOCKET_STATUS_LISTENING = 1, /**< Listening */
    U_SOCKET_STATUS_CONNECTED = 2  /**< Connected */
} uSocketStatus_t;

typedef enum
{
    U_OPTION_NO_DELAY,       /**< Turn on/off No delay feature for TCP sockets.
                                  Integer flag: 0 = off (i.e. Nagle algorithm enabled), 1 = on  (i.e. Nagle algorithm
                                  disabled)
                                  Default: to 1
                                  Note: This will make no difference if applied to UDP sockets. */
    U_OPTION_BLOCK = 1,      /**< Set socket to be blocking or non blocking.
                                  Integer flag: 0 = off, 1 = on.
                                  Sockets are non-blocking by default (Note that read/write will always be non-blocking).
                                  Can only be set while the socket is in a non connected state.
                                  Note: Only valid for TCP sockets, will have no effect on UDP sockets */
    U_OPTION_KEEP_ALIVE = 2, /**< Keep connections alive by sending keepalive probes.
                                  Integer flag: 0 = off, 1 = on.
                                  To calculate the keepalive time us this formula KeepIdle + (KeepIntvl * KeepCnt).
                                  Defaults to 1.
                                  Note: Only valid for TCP sockets. */
    U_OPTION_KEEP_IDLE = 3,  /**< Set Keep Idle value for the socket.
                                  This specifies the amount of time (in sec) that the connection must be idle before sending
                                  keepalive probes (if keepalive is enabled).
                                  Defaults to 3.
                                  Note: Only valid for TCP sockets. */
    U_OPTION_KEEP_INTVL = 4, /**< Set keep alive interval value for the socket. This is the time in seconds between two
                                  successive keepalive retransmissions.
                                  Defaults to 3.
                                  Note: Only valid for TCP sockets. */
    U_OPTION_KEEP_CNT = 5    /**< Set keep alive counter value for the socket.
                                  The number of unanswered probes required to force closure of the socket.
                                  Defaults to 3.
                                  Note: Only valid for TCP sockets. */
} uOption_t;

typedef enum
{
    U_OPTIONS_WRITE_WITH_OUT_RESPONSE, /**< Write without Response performed */
    U_OPTIONS_WRITE_WITH_RESPONSE = 1, /**< Write with Response performed */
    U_OPTIONS_WRITE_LONG = 2           /**< Write long performed */
} uOptions_t;

typedef enum
{
    U_PING_RESPONSE_FALSE,   /**< Ping failed. */
    U_PING_RESPONSE_TRUE = 1 /**< Ping succeeded. */
} uPingResponse_t;

/* ------------------------------------------------------------
 * CALLBACK TYPES
 * ---------------------------------------------------------- */

struct uCxHandle;
typedef void (*uUEBTDC_t)(struct uCxHandle *puCxHandle, int32_t conn_handle);
typedef void (*uUEBTPHYU_t)(struct uCxHandle *puCxHandle, int32_t conn_handle, int32_t phy_status, int32_t tx_phy, int32_t rx_phy);
typedef void (*uUEBTGCN_t)(struct uCxHandle *puCxHandle, int32_t conn_handle, int32_t value_handle, const char * hex_data);
typedef void (*uUEBTGCI_t)(struct uCxHandle *puCxHandle, int32_t conn_handle, int32_t value_handle, const char * hex_data);
typedef void (*uUEBTGCW_t)(struct uCxHandle *puCxHandle, int32_t conn_handle, int32_t value_handle, const char * value, uOptions_t options);
typedef void (*uUEBTGRR_t)(struct uCxHandle *puCxHandle, int32_t conn_handle, int32_t value_handle);
typedef void (*uUEBTGIC_t)(struct uCxHandle *puCxHandle, int32_t conn_handle, int32_t char_handle);
typedef void (*uUESPSC_t)(struct uCxHandle *puCxHandle, int32_t conn_handle);
typedef void (*uUESPSDC_t)(struct uCxHandle *puCxHandle, int32_t conn_handle);
typedef void (*uUESPSDS_t)(struct uCxHandle *puCxHandle, int32_t conn_handle, const char * string_data);
typedef void (*uUESPSDB_t)(struct uCxHandle *puCxHandle, int32_t conn_handle);
typedef void (*uUESPSDA_t)(struct uCxHandle *puCxHandle, int32_t conn_handle, int32_t number_bytes);
typedef void (*uUEWLU_t)(struct uCxHandle *puCxHandle, int32_t wlan_handle, uMacAddress_t * bssid, int32_t channel);
typedef void (*uUEWLD_t)(struct uCxHandle *puCxHandle, int32_t wlan_handle, int32_t reason);
typedef void (*uUEWSNU_t)(struct uCxHandle *puCxHandle);
typedef void (*uUEWSND_t)(struct uCxHandle *puCxHandle);
typedef void (*uUEWAPNU_t)(struct uCxHandle *puCxHandle);
typedef void (*uUEWAPND_t)(struct uCxHandle *puCxHandle);
typedef void (*uUEWAPU_t)(struct uCxHandle *puCxHandle);
typedef void (*uUEWAPD_t)(struct uCxHandle *puCxHandle);
typedef void (*uUEWAPSA_t)(struct uCxHandle *puCxHandle, uMacAddress_t * mac);
typedef void (*uUEWAPSDA_t)(struct uCxHandle *puCxHandle, uMacAddress_t * mac);
typedef void (*uUESOC_t)(struct uCxHandle *puCxHandle, int32_t socket_handle);
typedef void (*uUESODA_t)(struct uCxHandle *puCxHandle, int32_t socket_handle, int32_t number_bytes);
typedef void (*uUESODS_t)(struct uCxHandle *puCxHandle, int32_t socket_handle, const char * string_data);
typedef void (*uUESODSF_t)(struct uCxHandle *puCxHandle, int32_t socket_handle, uSockIpAddress_t * remote_ip, int32_t remote_port, const char * string_data);
typedef void (*uUESODB_t)(struct uCxHandle *puCxHandle, int32_t socket_handle);
typedef void (*uUESODBF_t)(struct uCxHandle *puCxHandle, int32_t socket_handle, uSockIpAddress_t * remote_ip, int32_t remote_port);
typedef void (*uUESOCL_t)(struct uCxHandle *puCxHandle, int32_t socket_handle);
typedef void (*uUESOIC_t)(struct uCxHandle *puCxHandle, int32_t socket_handle, uSockIpAddress_t * remote_ip, int32_t listening_socket_handle);
typedef void (*uUEMQC_t)(struct uCxHandle *puCxHandle, int32_t mqtt_id);
typedef void (*uUEMQDC_t)(struct uCxHandle *puCxHandle, int32_t mqtt_id, int32_t disconnect_reason);
typedef void (*uUEMQDA_t)(struct uCxHandle *puCxHandle, int32_t mqtt_id, int32_t message_len);
typedef void (*uUEDGPC_t)(struct uCxHandle *puCxHandle, int32_t transmitted_packets, int32_t received_packets, int32_t packet_loss_rate, int32_t avg_response_time);
typedef void (*uUEDGP_t)(struct uCxHandle *puCxHandle, uPingResponse_t ping_response, int32_t response_time);

/* ------------------------------------------------------------
 * INTERNAL CALLBACK STRUCT
 * ---------------------------------------------------------- */

typedef struct
{
    uUEBTDC_t UEBTDC;
    uUEBTPHYU_t UEBTPHYU;
    uUEBTGCN_t UEBTGCN;
    uUEBTGCI_t UEBTGCI;
    uUEBTGCW_t UEBTGCW;
    uUEBTGRR_t UEBTGRR;
    uUEBTGIC_t UEBTGIC;
    uUESPSC_t UESPSC;
    uUESPSDC_t UESPSDC;
    uUESPSDS_t UESPSDS;
    uUESPSDB_t UESPSDB;
    uUESPSDA_t UESPSDA;
    uUEWLU_t UEWLU;
    uUEWLD_t UEWLD;
    uUEWSNU_t UEWSNU;
    uUEWSND_t UEWSND;
    uUEWAPNU_t UEWAPNU;
    uUEWAPND_t UEWAPND;
    uUEWAPU_t UEWAPU;
    uUEWAPD_t UEWAPD;
    uUEWAPSA_t UEWAPSA;
    uUEWAPSDA_t UEWAPSDA;
    uUESOC_t UESOC;
    uUESODA_t UESODA;
    uUESODS_t UESODS;
    uUESODSF_t UESODSF;
    uUESODB_t UESODB;
    uUESODBF_t UESODBF;
    uUESOCL_t UESOCL;
    uUESOIC_t UESOIC;
    uUEMQC_t UEMQC;
    uUEMQDC_t UEMQDC;
    uUEMQDA_t UEMQDA;
    uUEDGPC_t UEDGPC;
    uUEDGP_t UEDGP;
} uUrcCallbacks;
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _U_CX_TYPES_H_ */