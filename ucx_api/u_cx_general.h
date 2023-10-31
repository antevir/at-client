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
#ifndef _U_CX_GENERAL_H_
#define _U_CX_GENERAL_H_

#include <stddef.h>
#include <stdint.h>
#include "u_cx_at_client.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* ------------------------------------------------------------
 * ENUMERATORS
 * ---------------------------------------------------------- */

/* ------------------------------------------------------------
 * RESPONSE STRUCTS
 * ---------------------------------------------------------- */

/* ------------------------------------------------------------
 * COMMAND HANDLERS
 * ---------------------------------------------------------- */

/**
 * Attention command.
 * 
 * Output AT command:
 * > AT
 *
 * @param[in]  pAtClient: AT client
 */
int32_t uCxGeneralAttention(uCxAtClient_t * pAtClient);

/**
 * Read manufacturer text string.
 * 
 * Output AT command:
 * > AT+GMI
 *
 * @param[in]  pAtClient:     AT client
 * @param[out] pManufacturer: Manufacturer ("u-blox").
 */
int32_t uCxBeginGeneralGetManufacturerIdentification(uCxAtClient_t * pAtClient, const char * * pManufacturer);

/**
 * Read device model.
 * 
 * Output AT command:
 * > AT+GMM
 *
 * @param[in]  pAtClient:    AT client
 * @param[out] pDeviceModel: Device model
 */
int32_t uCxBeginGeneralGetDeviceModelIdentification(uCxAtClient_t * pAtClient, const char * * pDeviceModel);

/**
 * Read software version.
 * 
 * Output AT command:
 * > AT+GMR
 *
 * @param[in]  pAtClient: AT client
 * @param[out] pVersion:  Version.
 */
int32_t uCxBeginGeneralGetSoftwareVersion(uCxAtClient_t * pAtClient, const char * * pVersion);

/**
 * Read serial number.
 * 
 * Output AT command:
 * > AT+GSN
 *
 * @param[in]  pAtClient:     AT client
 * @param[out] pSerialNumber: Serial number.
 */
int32_t uCxBeginGeneralGetSerialNumber(uCxAtClient_t * pAtClient, const char * * pSerialNumber);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _U_CX_GENERAL_H_ */