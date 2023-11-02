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

void myUrc(struct uCxAtClient *pClient, void *pTag, char *pLine, size_t lineLength)
{
    printf("Got URC: %s\n", pLine);
}

int main(void)
{
    uCxAtClient_t client;

    static char rxBuf[1024];
    static char urcBuf[1024];
    static const uCxAtClientConfig_t config = {
        .pRxBuffer = &rxBuf[0],
        .rxBufferLen = sizeof(rxBuf),
        .pUrcBuffer = &urcBuf[0],
        .urcBufferLen = sizeof(urcBuf),
        .pStreamHandle = NULL,
        .write = uCxAtWrite,
        .read = uCxAtRead
    };

    uCxAtClientInit(&config, &client);
    uCxAtClientSetUrcCallback(&client, myUrc, NULL);
    uCxAtClientExecSimpleCmd(&client, "ATE0");
    for (int i = 0; i < 3; i++) {
        uCxAtClientCmdBeginF(&client, "ATI", "d", 9, U_CX_AT_UTIL_PARAM_LAST);
        char *pRsp = uCxAtClientCmdGetRspParamLine(&client, "");
        if (pRsp) {
            printf("%d Got response: %s\n", i, pRsp);
        }
        uCxAtClientCmdEnd(&client);
    }
}