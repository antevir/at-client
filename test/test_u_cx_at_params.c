#include <string.h>
#include <stdbool.h>

#include "unity.h"
#include "u_cx_at_params.h"

/* ----------------------------------------------------------------
 * TYPES
 * -------------------------------------------------------------- */

typedef struct {
    const char *pString;
    const uSockIpAddress_t expectedAddr;
} uIpTestEntry_t;

/* ----------------------------------------------------------------
 * STATIC VARIABLES
 * -------------------------------------------------------------- */

/* ----------------------------------------------------------------
 * STATIC FUNCTIONS
 * -------------------------------------------------------------- */

/* ----------------------------------------------------------------
 * TEST FUNCTIONS
 * -------------------------------------------------------------- */

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uSockStringToIpAddress_withValidIpv4Str_expectSuccess(void)
{
    uSockIpAddress_t ipAddress;
    int32_t ret = uSockStringToIpAddress("0.16.32.48", &ipAddress);
    TEST_ASSERT_EQUAL(0, ret);
    TEST_ASSERT_EQUAL(U_SOCK_ADDRESS_TYPE_V4, ipAddress.type);
    TEST_ASSERT_EQUAL(0x00102030, ipAddress.address.ipv4);
}

void test_uSockStringToIpAddress_withValidIpv6Str_expectSuccess(void)
{
    uIpTestEntry_t testEntries[] = {
        {
            .pString = "[0000:1000:2000:3000:4000:5000:6000:7000]",
            .expectedAddr = { .address.ipv6 = { 0x60007000, 0x40005000, 0x20003000, 0x00001000 } }
        },
        {
            .pString = "0000:1000:2000:3000:4000:5000:6000:7000",
            .expectedAddr = { .address.ipv6 = { 0x60007000, 0x40005000, 0x20003000, 0x00001000 } }
        },
        {
            .pString = "0:1000:2000:3000:4000:5000:6000:7000",
            .expectedAddr = { .address.ipv6 = { 0x60007000, 0x40005000, 0x20003000, 0x00001000 } }
        },
        {
            .pString = "::2000:3000:4000:5000:6000:7000",
            .expectedAddr = { .address.ipv6 = { 0x60007000, 0x40005000, 0x20003000, 0x00000000 } }
        },
        {
            .pString = "[::2000:3000:4000:5000:6000:7000]",
            .expectedAddr = { .address.ipv6 = { 0x60007000, 0x40005000, 0x20003000, 0x00000000 } }
        },
        {
            .pString = "[::2000:3000:4000:5000:6000:FFFF]",
            .expectedAddr = { .address.ipv6 = { 0x6000FFFF, 0x40005000, 0x20003000, 0x00000000 } }
        },
        { 0 }
    };

    uIpTestEntry_t *pEntry = &testEntries[0];
    while (pEntry->pString) {
        uSockIpAddress_t ipAddress;
        int32_t ret = uSockStringToIpAddress(pEntry->pString, &ipAddress);
        TEST_ASSERT_EQUAL(0, ret);
        TEST_ASSERT_EQUAL(U_SOCK_ADDRESS_TYPE_V6, ipAddress.type);
        TEST_ASSERT_EQUAL_MEMORY(&pEntry->expectedAddr.address.ipv6,
                                 &ipAddress.address.ipv6,
                                 sizeof(ipAddress.address.ipv6));
        pEntry++;
    }
}

void test_uSockStringToIpAddress_withInvalidIpv4Str_expectError(void)
{
    uSockIpAddress_t ipAddress;
    TEST_ASSERT_LESS_THAN(0, uSockStringToIpAddress("0.16.32", &ipAddress));
    TEST_ASSERT_LESS_THAN(0, uSockStringToIpAddress("0.16.32.48.64", &ipAddress));
    TEST_ASSERT_LESS_THAN(0, uSockStringToIpAddress("0.16.32.48.", &ipAddress));
    TEST_ASSERT_LESS_THAN(0, uSockStringToIpAddress("256.16.32.48", &ipAddress));
    TEST_ASSERT_LESS_THAN(0, uSockStringToIpAddress(".16.32.0", &ipAddress));
    TEST_ASSERT_LESS_THAN(0, uSockStringToIpAddress(" .16.32.0", &ipAddress));
    TEST_ASSERT_LESS_THAN(0, uSockStringToIpAddress("0.16.32.", &ipAddress));
    TEST_ASSERT_LESS_THAN(0, uSockStringToIpAddress("A.16.32.48", &ipAddress));
    TEST_ASSERT_LESS_THAN(0, uSockStringToIpAddress("0,16.32.48", &ipAddress));
}

void test_uSockStringToIpAddress_withInvalidIpv6Str_expectError(void)
{
    uSockIpAddress_t ipAddress;
    TEST_ASSERT_LESS_THAN(0, uSockStringToIpAddress("", &ipAddress));
    TEST_ASSERT_LESS_THAN(0, uSockStringToIpAddress("[0:0:0:0:0:0:0:0", &ipAddress));
    TEST_ASSERT_LESS_THAN(0, uSockStringToIpAddress("0:0:0:0:0:0:0:0]", &ipAddress));
    TEST_ASSERT_LESS_THAN(0, uSockStringToIpAddress("0:0:0:0:0:0:0:0:0", &ipAddress));
    TEST_ASSERT_LESS_THAN(0, uSockStringToIpAddress("0:0:0:0:0:0:0", &ipAddress));
    TEST_ASSERT_LESS_THAN(0, uSockStringToIpAddress("G:0:0:0:0:0:0:0", &ipAddress));
    TEST_ASSERT_LESS_THAN(0, uSockStringToIpAddress("0.0:0:0:0:0:0:0", &ipAddress));
}

void test_uSockIpAddressToString_withIpv4Addr_expectValidIpString(void)
{
    const uSockIpAddress_t ipAddress = {
        .type = U_SOCK_ADDRESS_TYPE_V4,
        .address.ipv4 = 0x00102030
    };
    char buffer[15 + 1];
    int32_t ret = uSockIpAddressToString(&ipAddress, &buffer[0], sizeof(buffer));
    TEST_ASSERT_EQUAL(10, ret);
    TEST_ASSERT_EQUAL_STRING("0.16.32.48", buffer);
}

void test_uSockIpAddressToString_withIpv6Addr_expectValidIpString(void)
{
    const uSockIpAddress_t ipAddress = {
        .type = U_SOCK_ADDRESS_TYPE_V6,
        .address.ipv6 = {
            0x60007000,
            0x40005000,
            0x20003000,
            0x00001000
        }
    };
    char buffer[2 /* "[]" */ + 32 /* "0000" */ + 7 /* ":" */ + 1 /* null */];
    TEST_ASSERT_EQUAL(U_SOCK_ADDRESS_STRING_MAX_LENGTH_BYTES, sizeof(buffer));
    int32_t ret = uSockIpAddressToString(&ipAddress, &buffer[0], sizeof(buffer));
    TEST_ASSERT_EQUAL(41, ret);
    TEST_ASSERT_EQUAL_STRING("[0000:1000:2000:3000:4000:5000:6000:7000]", buffer);
}

void test_uSockIpAddressToString_withIpv4AddrAndLimitedBuf_expectNoBufferOverflow(void)
{
    const uSockIpAddress_t ipAddress = {
        .type = U_SOCK_ADDRESS_TYPE_V4,
        .address.ipv4 = 0xFFFFFFFF
    };
    char buffer[15 + 1];
    int32_t ret = uSockIpAddressToString(&ipAddress, &buffer[0], sizeof(buffer));
    TEST_ASSERT_EQUAL(15, ret);
    TEST_ASSERT_EQUAL_STRING("255.255.255.255", buffer);
}

void test_uSockIpAddressToString_withTooSmallBuffer_expectError(void)
{
    const uSockIpAddress_t ipAddress = {
        .type = U_SOCK_ADDRESS_TYPE_V4,
        .address.ipv4 = 0xFFFFFFFF
    };
    char buffer[15];
    int32_t ret = uSockIpAddressToString(&ipAddress, &buffer[0], sizeof(buffer));
    TEST_ASSERT_LESS_THAN(0, ret);
}