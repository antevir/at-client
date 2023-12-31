#include <string.h>
#include <stdbool.h>

#include "unity.h"
#include "mock_u_cx_log.h"
#include "mock_u_cx_at_config.h"
#include "u_cx_at_util.h"
#include "u_cx_at_params.h"
#include "u_cx_at_client.h"

/* ----------------------------------------------------------------
 * COMPILE-TIME MACROS
 * -------------------------------------------------------------- */

#define CONTEXT_VALUE  ((void *)0x11223344)
#define STREAM_HANDLER ((void *)0x44332211)

#define BIN_HDR(DATA_LENGTH) \
    0x01,(DATA_LENGTH) >> 8,(DATA_LENGTH) & 0xFF

/* ----------------------------------------------------------------
 * TYPES
 * -------------------------------------------------------------- */

static int32_t write(uCxAtClient_t *pClient, void *pStreamHandle,
                     const void *pData, size_t length);

static int32_t read(uCxAtClient_t *pClient, void *pStreamHandle,
                    void *pData, size_t length, int32_t timeoutMs);


/* ----------------------------------------------------------------
 * STATIC VARIABLES
 * -------------------------------------------------------------- */

static uint8_t gRxBuffer[1024];
static uint8_t gUrcBuffer[1024];

static uint8_t gTxBuffer[1024];
static size_t gTxBufferPos;

static uint8_t *gPRxDataPtr;
static int32_t gRxDataLen;

static uCxAtClientConfig_t gClientConfig = {
    .pContext = CONTEXT_VALUE,
    .pRxBuffer = gRxBuffer,
    .rxBufferLen = sizeof(gRxBuffer),
    .pStreamHandle = STREAM_HANDLER,
    .pUrcBuffer = gUrcBuffer,
    .urcBufferLen = sizeof(gUrcBuffer),
    .read = read,
    .write = write,
};

static uCxAtClient_t gClient;

/* ----------------------------------------------------------------
 * STATIC FUNCTIONS
 * -------------------------------------------------------------- */

static int32_t write(uCxAtClient_t *pClient, void *pStreamHandle,
                     const void *pData, size_t length)
{
    TEST_ASSERT_EQUAL(&gClient, pClient);
    TEST_ASSERT_EQUAL(STREAM_HANDLER, pStreamHandle);
    assert(length < sizeof(gTxBuffer) - gTxBufferPos);
    memcpy(&gTxBuffer[gTxBufferPos], pData, length);
    gTxBufferPos += length;
    return length;
}

static int32_t read(uCxAtClient_t *pClient, void *pStreamHandle,
                    void *pData, size_t length, int32_t timeoutMs)
{
    (void)timeoutMs;
    TEST_ASSERT_EQUAL(&gClient, pClient);
    TEST_ASSERT_EQUAL(STREAM_HANDLER, pStreamHandle);
    int32_t cpyLen = U_MIN((int32_t)length, gRxDataLen);
    if (cpyLen > 0) {
        memcpy(pData, gPRxDataPtr, cpyLen);
        gPRxDataPtr += cpyLen;
    }
    return cpyLen;
}

static void uAtClientSendCmdVaList_wrapper(uCxAtClient_t *pClient, const char *pCmd,
                                           const char *pParamFmt, ...)
{
    va_list args;
    va_start(args, pParamFmt);
    uCxAtClientSendCmdVaList(pClient, pCmd, pParamFmt, args);
    va_end(args);

    gTxBuffer[gTxBufferPos] = 0;
}

/* ----------------------------------------------------------------
 * TEST FUNCTIONS
 * -------------------------------------------------------------- */

void setUp(void)
{
    uCxLogPrintTime_Ignore();
    uCxAtClientInit(&gClientConfig, &gClient);
    memset(&gTxBuffer[0], 0xc0, sizeof(gTxBuffer));
    gTxBufferPos = 0;
    gPRxDataPtr = NULL;
    gRxDataLen = -1;

    uPortGetTickTimeMs_IgnoreAndReturn(0);
}

void tearDown(void)
{
}


void test_uCxAtClientSendCmdVaList_withIpAddress(void)
{
    uSockIpAddress_t ipAddr = {
        .type = U_SOCK_ADDRESS_TYPE_V4,
        .address.ipv4 = 0x00102030
    };
    uAtClientSendCmdVaList_wrapper(&gClient, "AT+FOO=", "i",
                                   &ipAddr, U_CX_AT_UTIL_PARAM_LAST);
    TEST_ASSERT_EQUAL_STRING("AT+FOO=0.16.32.48\r", &gTxBuffer[0]);
}


void test_uCxAtClientSendCmdVaList_withMacAddress(void)
{
    uMacAddress_t macAddr = {
        .address = {0x00,0x11,0x22,0x33,0x44,0x55}
    };
    uAtClientSendCmdVaList_wrapper(&gClient, "AT+FOO=", "m",
                                   &macAddr, U_CX_AT_UTIL_PARAM_LAST);
    TEST_ASSERT_EQUAL_STRING("AT+FOO=001122334455\r", &gTxBuffer[0]);
}

void test_uCxAtClientSendCmdVaList_withBdAddress(void)
{
    uBtLeAddress_t btLeAddr = {
        .type = U_BD_ADDRESS_TYPE_PUBLIC,
        .address = {0x00,0x11,0x22,0x33,0x44,0x55}
    };
    uAtClientSendCmdVaList_wrapper(&gClient, "AT+FOO=", "b",
                                   &btLeAddr, U_CX_AT_UTIL_PARAM_LAST);
    TEST_ASSERT_EQUAL_STRING("AT+FOO=001122334455p\r", &gTxBuffer[0]);
}

void test_uCxAtClientSendCmdVaList_withByteArray(void)
{
    uint8_t data[] = {0x00,0x11,0x22,0x33,0x44,0x55};
    uAtClientSendCmdVaList_wrapper(&gClient, "AT+FOO=", "h",
                                   &data[0], sizeof(data), U_CX_AT_UTIL_PARAM_LAST);
    TEST_ASSERT_EQUAL_STRING("AT+FOO=001122334455\r", &gTxBuffer[0]);
}

void test_uCxAtClientSendCmdVaList_withBinary(void)
{
    uint8_t data[] = {0x00,0x11,0x22,0x33,0x44,0x55};
    uint8_t expected[] = { 'A','T','+','F','O','O','=',BIN_HDR(6),0x00,0x11,0x22,0x33,0x44,0x55};
    uAtClientSendCmdVaList_wrapper(&gClient, "AT+FOO=", "B",
                                   &data[0], sizeof(data), U_CX_AT_UTIL_PARAM_LAST);
    TEST_ASSERT_EQUAL_MEMORY(expected, &gTxBuffer[0], sizeof(expected));
    TEST_ASSERT_EQUAL(sizeof(expected), gTxBufferPos);
}

void test_uCxAtClientCmdGetRspParamLine_withBinary(void)
{
    uint8_t binaryBuf[6] = {0};
    size_t binaryLen = sizeof(binaryBuf);
    uint8_t rxData[] = { '+','F','O','O',':','\"','f','o','o','\"',BIN_HDR(6),0x00,0x11,0x22,0x33,0x44,0x55};
    uint8_t expectedBinData[] = {0x00,0x11,0x22,0x33,0x44,0x55};

    // Start by putting the client in command state
    uCxAtClientCmdBeginF(&gClient, "", "", U_CX_AT_UTIL_PARAM_LAST);

    gPRxDataPtr = &rxData[0];
    gRxDataLen = sizeof(rxData);
    char *pRsp = uCxAtClientCmdGetRspParamLine(&gClient, "+FOO:", binaryBuf, &binaryLen);
    TEST_ASSERT_EQUAL_MEMORY(expectedBinData, binaryBuf, sizeof(binaryBuf));
    TEST_ASSERT_EQUAL(sizeof(binaryBuf), binaryLen);
    TEST_ASSERT_EQUAL_STRING("\"foo\"", pRsp);
}
