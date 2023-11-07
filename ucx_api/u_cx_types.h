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
    U_PING_RESPONSE_FALSE,   /**< Ping failed. */
    U_PING_RESPONSE_TRUE = 1 /**< Ping succeeded. */
} uPingResponse_t;

/* ------------------------------------------------------------
 * CALLBACK TYPES
 * ---------------------------------------------------------- */

struct uCxHandle;
typedef void (*uUEBTDC_t)(struct uCxHandle *puCxHandle, int32_t conn_handle);
typedef void (*uUEBTPHYU_t)(struct uCxHandle *puCxHandle, int32_t conn_handle, int32_t phy_status, int32_t tx_phy, int32_t rx_phy);
typedef void (*uUEBTGRR_t)(struct uCxHandle *puCxHandle, int32_t conn_handle, int32_t value_handle);
typedef void (*uUEBTGIC_t)(struct uCxHandle *puCxHandle, int32_t conn_handle, int32_t char_handle);
typedef void (*uUESPSC_t)(struct uCxHandle *puCxHandle, int32_t conn_handle);
typedef void (*uUESPSDC_t)(struct uCxHandle *puCxHandle, int32_t conn_handle);
typedef void (*uUESPSDS_t)(struct uCxHandle *puCxHandle, int32_t conn_handle, const char * string_data);
typedef void (*uUESPSDB_t)(struct uCxHandle *puCxHandle, int32_t conn_handle);
typedef void (*uUESPSDA_t)(struct uCxHandle *puCxHandle, int32_t conn_handle, int32_t number_bytes);
typedef void (*uUEWLD_t)(struct uCxHandle *puCxHandle, int32_t wlan_handle, int32_t reason);
typedef void (*uUEWSNU_t)(struct uCxHandle *puCxHandle);
typedef void (*uUEWSND_t)(struct uCxHandle *puCxHandle);
typedef void (*uUEWAPNU_t)(struct uCxHandle *puCxHandle);
typedef void (*uUEWAPND_t)(struct uCxHandle *puCxHandle);
typedef void (*uUEWAPU_t)(struct uCxHandle *puCxHandle);
typedef void (*uUEWAPD_t)(struct uCxHandle *puCxHandle);
typedef void (*uUESOC_t)(struct uCxHandle *puCxHandle, int32_t socket_handle);
typedef void (*uUESODA_t)(struct uCxHandle *puCxHandle, int32_t socket_handle, int32_t number_bytes);
typedef void (*uUESODS_t)(struct uCxHandle *puCxHandle, int32_t socket_handle, const char * string_data);
typedef void (*uUESODB_t)(struct uCxHandle *puCxHandle, int32_t socket_handle);
typedef void (*uUESOCL_t)(struct uCxHandle *puCxHandle, int32_t socket_handle);
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
    uUEBTGRR_t UEBTGRR;
    uUEBTGIC_t UEBTGIC;
    uUESPSC_t UESPSC;
    uUESPSDC_t UESPSDC;
    uUESPSDS_t UESPSDS;
    uUESPSDB_t UESPSDB;
    uUESPSDA_t UESPSDA;
    uUEWLD_t UEWLD;
    uUEWSNU_t UEWSNU;
    uUEWSND_t UEWSND;
    uUEWAPNU_t UEWAPNU;
    uUEWAPND_t UEWAPND;
    uUEWAPU_t UEWAPU;
    uUEWAPD_t UEWAPD;
    uUESOC_t UESOC;
    uUESODA_t UESODA;
    uUESODS_t UESODS;
    uUESODB_t UESODB;
    uUESOCL_t UESOCL;
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