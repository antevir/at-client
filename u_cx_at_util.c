/** @file
 * @brief Short description of the purpose of the file
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


static inline int hexToNibble(char hexChar)
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
}

int uCxAtUtilHexToByte(char *pHex, uint8_t *pOutByte)
{
    int highNibble = hexToNibble(pHex[0]);
    int lowNibble = hexToNibble(pHex[1]);
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

    if (insideString || escape || (pIter == pStr)) {
        return NULL;
    }

    return pIter;
}

int uCxAtUtilParseParamsVaList(char *pParams, const char *pParamFmt, va_list args)
{
    const char *pFmtCh = pParamFmt;
    char *pParam = pParams;
    bool last = false;
    int ret = 0;

    while (*pFmtCh != 0) {
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
                int *pI = va_arg(args, int *);
                ASSERT(pI != U_CX_AT_UTIL_PARAM_LAST);
                *pI = atoi(pParam);
            }
            break;
            case 's': {
                char **ppStr = va_arg(args, char **);
                ASSERT(ppStr != U_CX_AT_UTIL_PARAM_LAST);
                if (*pParam == '"') {
                    pParam++;
                    pParamEnd[-1] = 0;
                }
                *ppStr = pParam;
            }
            break;
            case 'b': {
                int *pLen = va_arg(args, int *);
                uint8_t **ppData = va_arg(args, uint8_t **);
                uint8_t *pBytes;
                size_t len = strlen(pParam);
                ASSERT(pLen != U_CX_AT_UTIL_PARAM_LAST);
                ASSERT(ppData != U_CX_AT_UTIL_PARAM_LAST);
                if ((len % 2) != 0) {
                    return -ret;
                }
                *pLen = len / 2;
                pBytes = pParam;
                *ppData = pBytes;
                for (int i = 0; i < *pLen; i++) {
                    if (uCxAtUtilHexToByte(&pParam[i * 2], pBytes) < 0) {
                        return -ret;
                    }
                    pBytes++;
                }
            }
            break;
        }
        ret++;
        if (last) {
            break;
        }
        pFmtCh++;
        pParam = &pParamEnd[1];
    }

    return ret;
}

int uCxAtUtilParseParamsF(char *pParams, const char *pParamFmt, ...)
{
    va_list args;

    va_start(args, pParamFmt);
    int ret = uCxAtUtilParseParamsVaList(pParams, pParamFmt, args);
    va_end(args);

    return ret;
}
