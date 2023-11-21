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
    TEST_ASSERT_EQUAL(&gClient, pClient);
    TEST_ASSERT_EQUAL(STREAM_HANDLER, pStreamHandle);
    (void)pData;
    (void)length;
    (void)timeoutMs;
    return -1;
}

static void uAtClientSendCmdVaList_wrapper(uCxAtClient_t *pClient, const char *pCmd,
                                           const char *pParamFmt, ...)
{
    va_list args;
    va_start(args, pParamFmt);
    uCxAtClientSendCmdVaList(pClient, pCmd, pParamFmt, args);
    va_end(args);
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
}
