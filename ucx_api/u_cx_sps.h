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
#ifndef _U_CX_SPS_H_
#define _U_CX_SPS_H_

#include <stddef.h>
#include <stdint.h>
#include "u_cx_types.h"
#include "u_cx.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* ------------------------------------------------------------
 * RESPONSES
 * ---------------------------------------------------------- */

typedef struct
{
    int32_t conn_handle;    /**< Connection handle of remote peer which has SPS enabled */
    int32_t written_length; /**< Data length that was written. */
} uCxSpsWriteString_t;

typedef struct
{
    int32_t conn_handle;      /**< Connection handle of remote peer */
    int32_t length;           /**< Data bytes to read. */
    const char * string_data; /**< SPS data in string format */
} uCxSpsReadString_t;


/* ------------------------------------------------------------
 * PUBLIC FUNCTIONS
 * ---------------------------------------------------------- */

/**
 * SPS connect on connected Bluetooth device
 * 
 * Output AT command:
 * > AT+USPSC=<conn_handle>
 *
 * @param[in]  puCxHandle:  uCX API handle
 * @param      conn_handle: Connection handle of remote peer
 */
int32_t uCxSpsConnect1(uCxHandle_t * puCxHandle, int32_t conn_handle);

/**
 * SPS connect on connected Bluetooth device
 * 
 * Output AT command:
 * > AT+USPSC=<conn_handle>,<flow_control>
 *
 * @param[in]  puCxHandle:   uCX API handle
 * @param      conn_handle:  Connection handle of remote peer
 * @param      flow_control: Flow control: 0 - no flow control, 1 - flow control
 */
int32_t uCxSpsConnect2(uCxHandle_t * puCxHandle, int32_t conn_handle, int32_t flow_control);

/**
 * Enables or disable the SPS Service.
 * 
 * Output AT command:
 * > AT+USPS=<sps_service_option>
 *
 * @param[in]  puCxHandle:         uCX API handle
 * @param      sps_service_option: 
 */
int32_t uCxSpsSetServiceEnable(uCxHandle_t * puCxHandle, uSpsServiceOption_t sps_service_option);

/**
 * Read if the SPS service is enabled or disabled.
 * 
 * Output AT command:
 * > AT+USPS?
 *
 * @param[in]  puCxHandle:        uCX API handle
 * @param[out] pSpsServiceOption: 
 */
int32_t uCxSpsGetServiceEnable(uCxHandle_t * puCxHandle, uSpsServiceOption_t * pSpsServiceOption);

/**
 * Write SPS data
 * 
 * Output AT command:
 * > AT+USPSWS=<conn_handle>,<string_data>
 *
 * @param[in]  puCxHandle:         uCX API handle
 * @param      conn_handle:        Connection handle of remote peer which has SPS enabled
 * @param      string_data:        Data encoded as ascii chars.
 * @param[out] pSpsWriteStringRsp: Please see \ref uCxSpsWriteString_t
 */
int32_t uCxSpsWriteString(uCxHandle_t * puCxHandle, int32_t conn_handle, const char * string_data, uCxSpsWriteString_t * pSpsWriteStringRsp);

/**
 * Set the mode in which to receive SPS data in AT mode.
 * 
 * Output AT command:
 * > AT+USPSRM=<read_mode>
 *
 * @param[in]  puCxHandle: uCX API handle
 * @param      read_mode:  Modes to read data in AT
 */
int32_t uCxSpsSetDataMode(uCxHandle_t * puCxHandle, uReadMode_t read_mode);

/**
 * Read mode set.
 * 
 * Output AT command:
 * > AT+USPSRM?
 *
 * @param[in]  puCxHandle: uCX API handle
 * @param[out] pReadMode:  Modes to read data in AT
 */
int32_t uCxSpsGetDataMode(uCxHandle_t * puCxHandle, uReadMode_t * pReadMode);

/**
 * Reads the specified amount of data from given connection handle.
 * Note that the data should include no null terminator characters.
 * 
 * Output AT command:
 * > AT+USPSRS=<conn_handle>,<length>
 *
 * @param[in]  puCxHandle:        uCX API handle
 * @param      conn_handle:       Connection handle of remote peer
 * @param      length:            Data bytes to read.
 * @param[out] pSpsReadStringRsp: Please see \ref uCxSpsReadString_t
 */
int32_t uCxBeginSpsReadString(uCxHandle_t * puCxHandle, int32_t conn_handle, int32_t length, uCxSpsReadString_t * pSpsReadStringRsp);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _U_CX_SPS_H_ */