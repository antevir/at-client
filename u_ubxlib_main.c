/** @file
 * @brief Short description of the purpose of the file
 */
#include <stdio.h>

#include "ubxlib.h"
#include "u_cx_at_client.h"

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

static void urcHandler(char *pUrcLine)
{
    printf("Got URC: %s\n", pUrcLine);
}

/* ----------------------------------------------------------------
 * PUBLIC FUNCTIONS
 * -------------------------------------------------------------- */

size_t uCxAtRead(struct uCxAtClient *pClient, void *pData, size_t length)
{
    return uPortUartRead(U_PTR_TO_INT32(pClient->streamHandle), pData, length);
}

void uCxAtWrite(struct uCxAtClient *pClient, const void *pData, size_t length)
{
    uPortUartWrite(U_PTR_TO_INT32(pClient->streamHandle), pData, length);
}

int main(void)
{
    char rxBuf[1024];
    uCxAtClient_t client;

    // Initiate ubxlib
    uPortInit();
    // Get the uart
    uPortUartInit();
    int32_t handleOrErrorCode = uPortUartOpen(
                                    0,
                                    115200,
                                    NULL,
                                    1024,
                                    -1,
                                    -1,
                                    -1,
                                    -1);
    if (handleOrErrorCode < 0) {
        printf("* Failed to open uart\n");
        return 1;
    }

    uCxAtClientInit(U_INT32_TO_PTR(handleOrErrorCode), rxBuf, sizeof(rxBuf), &client);
    uCxAtClientExecSimpleCmd(&client, "ATE0");
    client.urcCallback = urcHandler;
    for (int i = 0; i < 3; i++) {
        uCxAtClientCmdBeginF(&client, "ATI", "d", 9, U_CX_AT_UTIL_PARAM_LAST);
        char *pRsp = uCxAtClientCmdGetRspParamLine(&client, "");
        if (pRsp) {
            printf("%d Got response: %s\n", i, pRsp);
        }
        uCxAtClientCmdEnd(&client);
    }
}
