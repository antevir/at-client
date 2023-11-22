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
#ifndef _U_CX_SECURITY_H_
#define _U_CX_SECURITY_H_

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

/* ------------------------------------------------------------
 * PUBLIC FUNCTIONS
 * ---------------------------------------------------------- */

/**
 * Remove X.509 certificates and private keys.
 * 
 * Output AT command:
 * > AT+USECR=<cert_type>,<name>
 *
 * @param[in]  puCxHandle: uCX API handle
 * @param      cert_type:  
 * @param      name:       
 */
int32_t uCxSecurityCertificateRemove(uCxHandle_t * puCxHandle, uCertType_t cert_type, const char * name);

/**
 * Remove X.509 certificates and private keys.
 * 
 * Output AT command:
 * > AT+USECR=<remove_all>
 *
 * @param[in]  puCxHandle: uCX API handle
 * @param      remove_all: 
 */
int32_t uCxSecurityCertificateRemoveAll(uCxHandle_t * puCxHandle, uRemoveAll_t remove_all);

/**
 * Turn Server Name Indication TLS extension on and off on a system level
 * 
 * Output AT command:
 * > AT+USETE0=<enabled>
 *
 * @param[in]  puCxHandle: uCX API handle
 * @param      enabled:    
 */
int32_t uCxSecuritySetTlsServerNameIndication(uCxHandle_t * puCxHandle, uEnabled_t enabled);

/**
 * Read Server Name Indication setting
 * 
 * Output AT command:
 * > AT+USETE0?
 *
 * @param[in]  puCxHandle: uCX API handle
 * @param[out] pEnabled:   
 */
int32_t uCxBeginSecurityGetTlsServerNameIndication(uCxHandle_t * puCxHandle, uEnabled_t * pEnabled);

/**
 * Turn Handshake Fragmentation TLS extension on and off on a system level
 * 
 * Output AT command:
 * > AT+USETE1=<enabled>
 *
 * @param[in]  puCxHandle: uCX API handle
 * @param      enabled:    
 */
int32_t uCxSecuritySetTlsHandshakeFrag(uCxHandle_t * puCxHandle, uEnabled_t enabled);

/**
 * Read Handshake Fragmentation setting
 * 
 * Output AT command:
 * > AT+USETE1?
 *
 * @param[in]  puCxHandle: uCX API handle
 * @param[out] pEnabled:   
 */
int32_t uCxBeginSecurityGetTlsHandshakeFrag(uCxHandle_t * puCxHandle, uEnabled_t * pEnabled);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _U_CX_SECURITY_H_ */