/** @file
 * @brief uConnectXpress AT param parser
 */

#ifndef U_CX_AT_PARAMS_H
#define U_CX_AT_PARAMS_H

#include <stdint.h>
#include <stdbool.h>

/* ----------------------------------------------------------------
 * COMPILE-TIME MACROS
 * -------------------------------------------------------------- */

#define U_SOCK_ADDRESS_STRING_MAX_LENGTH_BYTES  42

/* ----------------------------------------------------------------
 * TYPES
 * -------------------------------------------------------------- */

typedef enum {
    U_SOCK_ADDRESS_TYPE_V4 = 0,
    U_SOCK_ADDRESS_TYPE_V6 = 6
} uSockIpAddressType_t;

typedef struct {
    uSockIpAddressType_t type;
    union {
        uint32_t ipv4;
        uint32_t ipv6[4];
    } address;
} uSockIpAddress_t;

/* ----------------------------------------------------------------
 * VARIABLES
 * -------------------------------------------------------------- */

/* ----------------------------------------------------------------
 * PUBLIC FUNCTIONS
 * -------------------------------------------------------------- */

/** Convert an IP address string into a struct.
 *
 * @param pAddressString the null terminated string to convert.
 *                       The string can be a IPv4 and IPv6 address.
 * @param[out] pAddress  a pointer to a place to put the address.
 * @return               zero on success else negative error code.
 */
int32_t uSockStringToIpAddress(const char *pAddressString,
                               uSockIpAddress_t *pAddress);

/** Convert an IP address struct into a string.
 *
 * @param pIpAddress    a pointer to the IP address to convert.
 * @param[out] pBuffer  a buffer in which to place the string.
 *                      Allow U_SOCK_ADDRESS_STRING_MAX_LENGTH_BYTES
 *                      for a full IPv6 address and terminator.
 * @param sizeBytes  the amount of memory pointed to by
 *                   pBuffer.
 * @return           on success the length of the string, not
 *                   including the terminator (i.e. what
 *                   strlen() would return) else negative
 *                   error code.
 */
int32_t uSockIpAddressToString(const uSockIpAddress_t *pIpAddress,
                               char *pBuffer, size_t sizeBytes);


#endif // U_CX_AT_PARAMS_H
