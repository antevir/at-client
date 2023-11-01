/** @file
 * @brief AT string utilities
 */

#ifndef U_CX_AT_UTIL_H
#define U_CX_AT_UTIL_H

#include <stdarg.h>
#include <stdint.h>

#include "u_cx_at_config.h"

/* ----------------------------------------------------------------
 * COMPILE-TIME MACROS
 * -------------------------------------------------------------- */

#define U_CX_AT_UTIL_PARAM_LAST  NULL

/* ----------------------------------------------------------------
 * TYPES
 * -------------------------------------------------------------- */

/* ----------------------------------------------------------------
 * VARIABLES
 * -------------------------------------------------------------- */

/* ----------------------------------------------------------------
 * PUBLIC FUNCTIONS
 * -------------------------------------------------------------- */

void uCxAtUtilByteToHex(uint8_t byte, char *pOutPtr);
int uCxAtUtilHexToByte(char *pHex, uint8_t *pOutByte);
char *uCxAtUtilFindParamEnd(char *pStr);
int uCxAtUtilParseParamsVaList(char *pParams, const char *pParamFmt, va_list args);
int uCxAtUtilParseParamsF(char *pParams, const char *pParamFmt, ...);

#endif // U_CX_AT_UTIL_H