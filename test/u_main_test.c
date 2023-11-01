#include <string.h>
#include <stdio.h>

#include "u_cx_at_client.h"
#include "u_cx_at_util.h"

int32_t uCxAtRead(struct uCxAtClient *pClient, void *pData, size_t length)
{
    (void)pClient;
    return (int32_t)fread(pData, 1, length, stdin);
}

int32_t uCxAtWrite(struct uCxAtClient *pClient, const void *pData, size_t length)
{
    (void)pClient;
    return (int32_t)fwrite(pData, 1, length, stdout);
}

void myUrc(char *pUrcLine)
{
    printf("Got URC: %s\n", pUrcLine);
}

int main(void)
{
    uCxAtClient_t client;

    char rxBuf[1024];

    uCxAtClientInit(NULL, rxBuf, sizeof(rxBuf), &client);
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