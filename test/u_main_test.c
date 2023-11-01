#include <string.h>
#include <stdio.h>

#include "u_cx_at_client.h"
#include "u_cx_at_util.h"

static int32_t uCxAtRead(uCxAtClient_t *pClient, void *pStreamHandle, void *pData, size_t length)
{
    (void)pClient;
    (void)pStreamHandle;
    return (int32_t)fread(pData, 1, length, stdin);
}

static int32_t uCxAtWrite(uCxAtClient_t *pClient, void *pStreamHandle, const void *pData, size_t length)
{
    (void)pClient;
    (void)pStreamHandle;
    return (int32_t)fwrite(pData, 1, length, stdout);
}

void myUrc(char *pUrcLine)
{
    printf("Got URC: %s\n", pUrcLine);
}

int main(void)
{
    uCxAtClient_t client;

    static char rxBuf[1024];
    static const uCxAtClientConfig_t config = {
        .pRxBuffer = &rxBuf[0],
        .rxBufferLen = sizeof(rxBuf),
        .pStreamHandle = NULL,
        .write = uCxAtWrite,
        .read = uCxAtRead
    };

    uCxAtClientInit(&config, &client);
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