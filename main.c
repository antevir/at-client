#include <string.h>
#include <stdio.h>
#include "ubxlib.h"

#include "u_cx_at_client.h"
#include "u_cx_at_util.h"

void myUrc(char *pUrcLine)
{
    printf("Got URC: %s\n", pUrcLine);
}

int main(void)
{
    uCxAtClient_t client;

    char *s1;
    char *s2;
    int d1, d2;
    int len;
    uint8_t *pData;
    char buf[64];
    char rxBuf[1024];
    strcpy(buf, "\"hej\",123,hopp,-100,10200a0b0c01");
    int ret = uCxAtUtilParseParamsF(buf, "sdsdb", &s1, &d1, &s2, &d2, &len, &pData);
    printf("ret: %d, s1: %s, d1: %d, s2: %s, d2: %d\n", ret, s1, d1, s2, d2);
    printf("len: %d, pData: %02x%02x%02x%02x%02x%02x\n", len, pData[0], pData[1], pData[2], pData[3],
           pData[4], pData[5]);

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
    client.urcCallback = myUrc;
    for (int i = 0; i < 3; i++) {
        uCxAtClientCmdBeginF(&client, "ATI", "d", 9, U_CX_AT_UTIL_PARAM_LAST);
        char *pRsp = uCxAtClientCmdGetRspParamLine(&client, "");
        if (pRsp) {
            printf("%d Got response: %s\n", i, pRsp);
        }
        uCxAtClientCmdEnd(&client);
    }
}