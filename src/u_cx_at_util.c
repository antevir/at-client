/** @file
 * @brief AT string utilities
 */

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "u_cx_at_util.h"

/* ----------------------------------------------------------------
 * COMPILE-TIME MACROS
 * -------------------------------------------------------------- */

/* ----------------------------------------------------------------
 * TYPES
 * -------------------------------------------------------------- */

/* ----------------------------------------------------------------
 * STATIC PROTOTYPES
 * -------------------------------------------------------------- */

/* ----------------------------------------------------------------
 * STATIC VARIABLES
 * -------------------------------------------------------------- */

/* ----------------------------------------------------------------
 * STATIC FUNCTIONS
 * -------------------------------------------------------------- */

static inline char nibbleToHex(uint8_t nibble)
{
    return (nibble < 10) ? '0' + nibble : 'A' + nibble - 10;
}


static inline int32_t hexToNibble(char hexChar)
{
    if ((hexChar >= '0') && (hexChar <= '9')) {
        return hexChar - '0';
    }
    if ((hexChar >= 'a') && (hexChar <= 'f')) {
        return hexChar - 'a' + 10;
    }
    if ((hexChar >= 'A') && (hexChar <= 'F')) {
        return hexChar - 'A' + 10;
    }
    return -1;
}

/* ----------------------------------------------------------------
 * PUBLIC FUNCTIONS
 * -------------------------------------------------------------- */

void uCxAtUtilByteToHex(uint8_t byte, char *pOutPtr)
{
    pOutPtr[0] = nibbleToHex(byte >> 4);
    pOutPtr[1] = nibbleToHex(byte & 0xF);
    pOutPtr[2] = 0;
}

int32_t uCxAtUtilHexToByte(char *pHex, uint8_t *pOutByte)
{
    int32_t highNibble = hexToNibble(pHex[0]);
    int32_t lowNibble = hexToNibble(pHex[1]);
    if ((highNibble < 0) || (lowNibble < 0)) {
        return -1;
    }
    *pOutByte = (highNibble << 4) | lowNibble;
    return 0;
}

char *uCxAtUtilFindParamEnd(char *pStr)
{
    bool insideString = false;
    bool escape = false;

    char *pIter = pStr;
    while (*pIter != 0) {
        if (escape) {
            escape = false;
        } else if (*pIter == '\\') {
            escape = true;
        } else if (insideString) {
            if (*pIter == '"') {
                insideString = false;
            }
        } else if (*pIter == '"') {
            insideString = true;
        } else if (*pIter == ',') {
            break;
        }
        pIter++;
    }

    if (insideString || escape) {
        return NULL;
    }

    return pIter;
}

int32_t uCxAtUtilParseParamsVaList(char *pParams, const char *pParamFmt, va_list args)
{
    const char *pFmtCh = pParamFmt;
    char *pParam = pParams;
    bool last = false;
    int32_t ret = 0;

    while (*pFmtCh != 0) {
        ret++;
        char *pParamEnd = uCxAtUtilFindParamEnd(pParam);
        if (pParamEnd == NULL) {
            return -ret;
        }
        if (*pParamEnd == 0) {
            last = true;
        } else {
            *pParamEnd = 0;
        }

        switch (*pFmtCh) {
            case 'd': {
                char * pEnd;
                int32_t *pI = va_arg(args, int32_t *);
                U_CX_AT_PORT_ASSERT(pI != U_CX_AT_UTIL_PARAM_LAST);
                *pI = strtol(pParam, &pEnd, 10);
                if (!isdigit(*pParam) || (*pEnd != 0)) {
                    // Not a valid integer
                    return -ret;
                }
            }
            break;
            case 's': {
                char **ppStr = va_arg(args, char **);
                U_CX_AT_PORT_ASSERT(ppStr != U_CX_AT_UTIL_PARAM_LAST);
                if (*pParam == '"') {
                    pParam++;
                    pParamEnd[-1] = 0;
                }
                *ppStr = pParam;
            }
            break;
            case 'b': {
                int32_t *pLen = va_arg(args, int32_t *);
                uint8_t **ppData = va_arg(args, uint8_t **);
                uint8_t *pBytes;
                size_t len = strlen(pParam);
                U_CX_AT_PORT_ASSERT(pLen != U_CX_AT_UTIL_PARAM_LAST);
                U_CX_AT_PORT_ASSERT(ppData != U_CX_AT_UTIL_PARAM_LAST);
                if ((len % 2) != 0) {
                    return -ret;
                }
                *pLen = len / 2;
                pBytes = (uint8_t *)pParam;
                *ppData = pBytes;
                for (int32_t i = 0; i < *pLen; i++) {
                    if (uCxAtUtilHexToByte(&pParam[i * 2], pBytes) < 0) {
                        return -ret;
                    }
                    pBytes++;
                }
            }
            break;
        }
        if (last) {
            break;
        }
        pFmtCh++;
        pParam = &pParamEnd[1];
    }

    return ret;
}

int32_t uCxAtUtilParseParamsF(char *pParams, const char *pParamFmt, ...)
{
    va_list args;

    va_start(args, pParamFmt);
    int32_t ret = uCxAtUtilParseParamsVaList(pParams, pParamFmt, args);
    va_end(args);

    return ret;
}
