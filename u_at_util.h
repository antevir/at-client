/** @file
 * @brief Short description of the purpose of the file
 */

#ifndef U_AT_UTIL_H
#define U_AT_UTIL_H

#include <stdarg.h>
#include <stdint.h>

/* ----------------------------------------------------------------
 * COMPILE-TIME MACROS
 * -------------------------------------------------------------- */

#ifndef ASSERT
# include <assert.h>
# define ASSERT assert
#endif

#define U_AT_UTIL_PARAM_LAST  NULL

/* ----------------------------------------------------------------
 * TYPES
 * -------------------------------------------------------------- */

/* ----------------------------------------------------------------
 * VARIABLES
 * -------------------------------------------------------------- */

/* ----------------------------------------------------------------
 * PUBLIC FUNCTIONS
 * -------------------------------------------------------------- */

void uAtUtilByteToHex(uint8_t byte, char *pOutPtr);
int uAtUtilHexToByte(char *pHex, uint8_t *pOutByte);
char *uAtUtilFindParamEnd(char *pStr);
int uAtUtilParseParamsVaList(char *pParams, const char *pParamFmt, va_list args);
int uAtUtilParseParamsF(char *pParams, const char *pParamFmt, ...);

#endif // U_AT_UTIL_H