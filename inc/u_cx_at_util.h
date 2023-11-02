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

/**
  * @brief Convert a single byte from uint8_t to a null terminated hex string
  *
  * Example:
  * With byte=0x00, pOutPtr will be set to "00" (plus null terminator)
  * With byte=0x3f, pOutPtr will be set to "3F" (plus null terminator)
  *
  * @param      byte:     byte to convert to hex.
  * @param[out] pOutPtr:  the output pointer to receive the hex string (must be a buffer of 3 bytes or more).
  */
void uCxAtUtilByteToHex(uint8_t byte, char *pOutPtr);

/**
  * @brief Convert a single byte from a null terminated hex string to uint8_t
  *
  * The function will read 2 hex characters from pHex and try to convert these to a uint8_t
  * Any character after these 2 characters will not be read or validated.
  *
  * Example:
  * With pHex="00", pOutPtr will be set to 0x00
  * With pHex="3F", pOutPtr will be set to 0x3f
  * With pHex="3F00", pOutPtr will be set to 0x3f
  *
  * @param[in]  pHex:      the input hex string.
  * @param[out] pOutByte:  the output byte.
  * @retval                0 on success otherwise negative value.
  */
int uCxAtUtilHexToByte(char *pHex, uint8_t *pOutByte);

/**
  * @brief Find end of a parameter in an AT parameter string
  *
  * This function is used as a tokenizer for an AT parameter string.
  * It will handle escaped characters ('\') and disregards commas
  * inside strings.
  *
  * NOTE: The comma after at the end of the parameter will be modified
  *       to a null terminator.
  *
  * Example:
  * With pStr="abc,123" return value will be: "123" and pStr modified to "abc"
  *
  * @param[in]  pHex:      the input hex string.
  * @param[out] pOutByte:  the output byte.
  * @retval                the number of parsed params on success otherwise negative value.
  */
char *uCxAtUtilFindParamEnd(char *pStr);

/**
  * @brief  Parse an AT parameter string
  *
  * This function uses a param format string (somewhat similar to scanf).
  * Defined format characters are:
  *
  * Char   Type           Desc
  * ---------------------------------------------
  * 'd'    int32_t *      Integer
  * 's'    const char **  Null terminated string
  *
  * Each AT parameter pointer is then added as an variadic argument to this function.
  * NOTE: The variadic parameters must always be terminated with U_CX_AT_UTIL_PARAM_LAST
  *
  * Example:
  *   const char *pStr
  *   int32_t digit;
  *   uCxAtUtilParseParamsF(pClient,"123,Foo","ds",&digit,&pStr,U_CX_AT_UTIL_PARAM_LAST)
  * Result:
  *   digit: 123
  *   pStr: "Foo"
  *
  * @param[in]  pParams:   the AT parameter string to parse.
  * @param[in]  pParamFmt: format string - see function description.
  * @param[out] ...:       the output AT param pointers. Last param is always U_CX_AT_UTIL_PARAM_LAST!
  * @retval                the number of parsed params on success otherwise negative value.
  */
int uCxAtUtilParseParamsF(char *pParams, const char *pParamFmt, ...);

/**
  * @brief  Parse an AT parameter string
  *
  * Same as uCxAtUtilParseParamsF() but using a va_list for AT params instead of variadic arguments.
  *
  * @param[in]  pParams:   the AT parameter string to parse.
  * @param[in]  pParamFmt: format string - see function description.
  * @param[out] args:      the output AT param pointers. Last param is always U_CX_AT_UTIL_PARAM_LAST!
  * @retval                the number of parsed params on success otherwise negative value.
  */
int uCxAtUtilParseParamsVaList(char *pParams, const char *pParamFmt, va_list args);

#endif // U_CX_AT_UTIL_H