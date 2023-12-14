#include <string.h>
#include <stdio.h>
#include <time.h>

#include "u_cx_at_client.h"
#include "u_cx_at_util.h"
#include "u_cx.h"
#include "u_cx_urc.h"

static uint64_t gBootTime;

static int32_t uCxAtRead(uCxAtClient_t *pClient, void *pStreamHandle, void *pData, size_t length, int32_t timeoutMs)
{
    (void)pClient;
    (void)pStreamHandle;
    (void)timeoutMs;
    return (int32_t)fread(pData, 1, length, stdin);
}

static int32_t uCxAtWrite(uCxAtClient_t *pClient, void *pStreamHandle, const void *pData, size_t length)
{
    (void)pClient;
    (void)pStreamHandle;
    return (int32_t)fwrite(pData, 1, length, stdout);
}

void myUrc(struct uCxAtClient *pClient, void *pTag, char *pLine, size_t lineLength,
           uint8_t *pBinaryData, size_t binaryDataLen)
{
    printf("Got URC: %s\n", pLine);
}

void callbackUEDGP(struct uCxHandle *puCxHandle, uPingResponse_t ping_response, int32_t response_time)
{
    printf("callbackUEDGP: %d, %d\n", ping_response, response_time);
}

void networkUpUrc(struct uCxHandle *puCxHandle)
{
    printf("networkUpUrc\n");
}

static int32_t getTickTimeMs(void)
{
    struct timespec time;
    clock_gettime(CLOCK_MONOTONIC_RAW, &time);
    uint64_t timeMs = (time.tv_sec * 1000) + (time.tv_nsec / (1000 * 1000));
    return (int32_t)timeMs;
}

int32_t uPortGetTickTimeMs(void)
{
    int32_t timeMs = getTickTimeMs() - gBootTime;
    return timeMs;
}

int main(void)
{
    uCxAtClient_t client;
    uCxHandle_t ucxHandle;

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

    gBootTime = getTickTimeMs();

    uCxAtClientInit(&config, &client);
    uCxInit(&client, &ucxHandle);
    uCxUrcRegisterWiFiStationNetworkUp(&ucxHandle, networkUpUrc);
    ucxHandle.callbacks.UEDGP = callbackUEDGP;

    //uCxAtClientHandleRx(&client);
    uCxAtClientSetUrcCallback(&client, myUrc, NULL);
    uCxAtClientExecSimpleCmdF(&client, "AT+BIN", "B", "abc123", 6);
    uCxAtClientExecSimpleCmd(&client, "ATE0");
}