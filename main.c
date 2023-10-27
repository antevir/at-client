#include <string.h>
#include <stdio.h>

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
    uCxAtClientInit(rxBuf, sizeof(rxBuf), &client);
    uCxAtClientExecSimpleCmd(&client, "TESTING");
    client.urcCallback = myUrc;
    uCxAtClientCmdBeginF(&client, "AT+HEJ=", "dhsb", 123, 65535, "foo", 3, "abc",
                         U_CX_AT_UTIL_PARAM_LAST);
    printf("\n");
    char *pRsp = uCxAtClientCmdGetRspParamLine(&client, "+RSP");
    if (pRsp) {
        printf("Got response: %s\n", pRsp);
    }

    printf("status: %d\n", uCxAtClientCmdEnd(&client));
}