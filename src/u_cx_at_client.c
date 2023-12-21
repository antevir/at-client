/** @file
 * @brief 2nd gen uConnectXpress AT client
 */

#include "limits.h"  // For INT_MAX
#include "stddef.h"  // NULL, size_t etc.
#include "stdint.h"  // int32_t etc.
#include "stdbool.h"
#include "string.h"  // memcpy(), strcmp(), strcspn(), strspm()
#include "stdio.h"   // snprintf()
#include "ctype.h"   // isprint()

#include "u_cx_at_config.h"

#include "u_cx_log.h"
#include "u_cx_at_util.h"
#include "u_cx_at_client.h"

/* ----------------------------------------------------------------
 * COMPILE-TIME MACROS
 * -------------------------------------------------------------- */

#define NO_STATUS   (INT_MAX)

/* Special character sent for entering binary mode */
#define U_CX_SOH_CHAR    0x01


/* ----------------------------------------------------------------
 * TYPES
 * -------------------------------------------------------------- */

enum uCxAtParserCode {
    AT_PARSER_NOP = 0,
    AT_PARSER_GOT_STATUS,
    AT_PARSER_GOT_RSP,
    AT_PARSER_START_BINARY,
    AT_PARSER_ERROR
};

/* ----------------------------------------------------------------
 * STATIC PROTOTYPES
 * -------------------------------------------------------------- */

/* ----------------------------------------------------------------
 * STATIC VARIABLES
 * -------------------------------------------------------------- */

/* ----------------------------------------------------------------
 * STATIC FUNCTIONS
 * -------------------------------------------------------------- */

// Helper function for setting up the RX binary transfer buffer
static void setupBinaryRxBuffer(uCxAtClient_t *pClient, uCxAtRxState_t state,
                                uint8_t *pBuffer, size_t bufferSize)
{
    uCxAtBinaryRx_t *pBinRx = &pClient->binaryRx;
    memset(pBinRx, 0, sizeof(uCxAtBinaryRx_t));
    pBinRx->pBuffer = pBuffer;
    pBinRx->bufferSize = bufferSize;
    pClient->rxState = state;
}

static int32_t parseLine(uCxAtClient_t *pClient, char *pLine, size_t lineLength, bool gotBinaryData)
{
    const struct uCxAtClientConfig *pConfig = pClient->pConfig;
    int32_t ret = AT_PARSER_NOP;

    char *pPtr = pLine;
    bool emptyLine = true;
    while (pPtr < &pLine[lineLength]) {
        if ((*pPtr != '\n') && (*pPtr != '\r')) {
            emptyLine = false;
            break;
        }
        pPtr++;
    }
    if (emptyLine) {
        return AT_PARSER_NOP;
    }

    U_CX_LOG_LINE(U_CX_LOG_CHANNEL_RX, "%s", pLine);

    if (pClient->executingCmd) {
        if ((pClient->pExpectedRsp != NULL) &&
            (*pClient->pExpectedRsp != 0) &&
            (strncmp(pLine, pClient->pExpectedRsp, pClient->pExpectedRspLen) == 0)) {
            pClient->pRspParams = &pLine[pClient->pExpectedRspLen];
            ret = AT_PARSER_GOT_RSP;
        } else if (strcmp(pLine, "OK") == 0) {
            pClient->status = 0;
            ret = AT_PARSER_GOT_STATUS;
        } else if (strcmp(pLine, "ERROR") == 0) {
            pClient->status = -1;
            ret = AT_PARSER_GOT_STATUS;
        } else if ((pLine[0] != '+') && (pLine[0] != '*')) {
            pClient->pRspParams = &pLine[0];
            ret = AT_PARSER_GOT_RSP;
        }
        if ((ret == AT_PARSER_GOT_RSP) && gotBinaryData) {
            // We are receiving an AT response with binary data
            // Setup the binary buffer, but don't return AT_PARSER_GOT_RSP
            // until transfer is done.
            uCxAtBinaryResponseBuf_t *pRspBuf = &pClient->rspBinaryBuf;
            size_t length = 0;
            if (pRspBuf->pBufferLength) {
                length = *pRspBuf->pBufferLength;
                *pRspBuf->pBufferLength = 0;
            }
            setupBinaryRxBuffer(pClient, U_CX_AT_RX_STATE_BINARY_RSP,
                                pRspBuf->pBuffer, length);
            return AT_PARSER_START_BINARY;
        }
    }

    if (ret == AT_PARSER_NOP) {
        // Check if this is URC data
        if ((pLine[0] == '+') || (pLine[0] == '*')) {
            if (!pClient->executingCmd && !gotBinaryData) {
                // If there are no command is currently executing we can just
                // execute the URC handler right away
                if (pClient->urcCallback) {
                    uint8_t *pBinaryData = pClient->binaryRx.pBuffer;
                    size_t binaryLen = pClient->binaryRx.bufferPos;
                    pClient->urcCallback(pClient, pClient->pUrcCallbackTag, pLine, lineLength,
                                         pBinaryData, binaryLen);
                }
            } else {
                // AT client is busy handling AT command
                // Defer callback until command is done

                // We only support deferring one URC at the moment
                U_CX_AT_PORT_ASSERT(pClient->urcBufferPos == 0);

                if (lineLength <= pConfig->urcBufferLen) {
                    memcpy(pConfig->pUrcBuffer, pLine, lineLength);
                    pClient->urcBufferPos = lineLength;
                } else {
                    // URC buffer too small. Fail assert for now.
                    U_CX_AT_PORT_ASSERT(false);
                }

                if (gotBinaryData) {
                    // Place the binary data directly after the URC string
                    uint8_t *pPtr = pConfig->pUrcBuffer;
                    size_t len = pConfig->urcBufferLen - pClient->urcBufferPos;
                    setupBinaryRxBuffer(pClient, U_CX_AT_RX_STATE_BINARY_URC,
                                        &pPtr[pClient->urcBufferPos], len);
                    ret = AT_PARSER_START_BINARY;
                }
            }
        } else {
            // Received unexpected data
            // TODO: Handle
            if (gotBinaryData) {
                setupBinaryRxBuffer(pClient, U_CX_AT_RX_STATE_BINARY_FLUSH, NULL, 0);
                ret = AT_PARSER_START_BINARY;
            }
        }
    }

    return ret;
}

static int32_t parseIncomingChar(uCxAtClient_t *pClient, char ch)
{
    int32_t ret = AT_PARSER_NOP;
    char *pRxBuffer = (char *)pClient->pConfig->pRxBuffer;
    bool gotBinaryData = (ch == U_CX_SOH_CHAR);

    if ((ch == '\r') || (ch == '\n') || gotBinaryData) {
        pRxBuffer[pClient->rxBufferPos] = 0;
        ret = parseLine(pClient, pRxBuffer, pClient->rxBufferPos, gotBinaryData);
        pClient->rxBufferPos = 0;
    } else if (isprint(ch)) {
        pRxBuffer[pClient->rxBufferPos++] = ch;
        if (pClient->rxBufferPos == pClient->pConfig->rxBufferLen) {
            // Overflow - discard everything and start over
            pClient->rxBufferPos = 0;
        }
    }

    return ret;
}

static int32_t handleBinaryRx(uCxAtClient_t *pClient)
{
    int32_t ret = AT_PARSER_NOP;

    // Loop for receiving binary data
    uCxAtBinaryRx_t *pBinRx = &pClient->binaryRx;
    int32_t readStatus;

    static uint8_t lengthBuf[2];
    if (pBinRx->rxHeaderCount < 2) {
        size_t readLen = sizeof(lengthBuf) - pBinRx->rxHeaderCount;
        readStatus = pClient->pConfig->read(pClient, pClient->pConfig->pStreamHandle,
                                            &lengthBuf[pBinRx->rxHeaderCount], readLen,
                                            pClient->pConfig->timeoutMs);
        if (readStatus < (int32_t)readLen) {
            return ret;
        } else {
            // The two length bytes have now been received
            uint16_t length = (lengthBuf[0] << 8) | lengthBuf[1];
            pBinRx->remainingDataBytes = length;
        }
    }

    while (pBinRx->remainingDataBytes > 0) {
        size_t remainingBuf = pBinRx->bufferSize - pBinRx->bufferPos;
        if (remainingBuf > 0) {
            // There are buffer left, continue to read
            size_t readLen = U_MIN(remainingBuf, pBinRx->remainingDataBytes);
            readStatus = pClient->pConfig->read(pClient, pClient->pConfig->pStreamHandle,
                                                &pBinRx->pBuffer[pBinRx->bufferPos], readLen,
                                                pClient->pConfig->timeoutMs);
            if (readStatus > 0) {
                pBinRx->bufferPos += readStatus;
            }
        } else {
            // There are no buffer space - just throw away all data until binary transfer is done
            uint8_t buf[64];
            size_t readLen = U_MIN(sizeof(buf), pBinRx->remainingDataBytes);
            readStatus = pClient->pConfig->read(pClient, pClient->pConfig->pStreamHandle,
                                                &buf[0], readLen,
                                                pClient->pConfig->timeoutMs);
        }

        if (readStatus > 0) {
            pBinRx->remainingDataBytes -= readStatus;
        } else {
            break;
        }
    }

    if (pBinRx->remainingDataBytes == 0) {
        // Binary transfer done
        uCxAtRxState_t rxState = pClient->rxState;
        pClient->rxState = U_CX_AT_RX_STATE_CHARACTER;

        switch (rxState) {
            case U_CX_AT_RX_STATE_BINARY_RSP: {
                uCxAtBinaryResponseBuf_t *pRspBuf = &pClient->rspBinaryBuf;
                // Report back how much data were received
                if (pRspBuf->pBufferLength != NULL) {
                    *pRspBuf->pBufferLength = pClient->binaryRx.bufferPos;
                }
                ret = AT_PARSER_GOT_RSP;
                break;
            }
            case U_CX_AT_RX_STATE_BINARY_URC:
                // TODO
                break;
            default:
                break;
        }
    }

    return ret;
}

static int32_t handleRxData(uCxAtClient_t *pClient)
{
    int32_t ret = AT_PARSER_NOP;

    do {
        int32_t readStatus;

        if (pClient->rxState == U_CX_AT_RX_STATE_CHARACTER) {
            // Loop for receiving string data
            do {
                char ch;
                readStatus = pClient->pConfig->read(pClient, pClient->pConfig->pStreamHandle, &ch, 1,
                                                    pClient->pConfig->timeoutMs);
                if (readStatus != 1) {
                    break;
                }
                ret = parseIncomingChar(pClient, ch);
            } while (ret == AT_PARSER_NOP);
        } else {
            ret = handleBinaryRx(pClient);
        }
    } while (ret == AT_PARSER_START_BINARY);

    return ret;
}

static void handleDeferredUrc(uCxAtClient_t *pClient)
{
    if ((pClient->urcBufferPos > 0) &&
        (pClient->rxState != U_CX_AT_RX_STATE_BINARY_URC)) {

        if (pClient->urcCallback) {
            const struct uCxAtClientConfig *pConfig = pClient->pConfig;
            pClient->urcCallback(pClient, pClient->pUrcCallbackTag,
                                 (char *)pConfig->pUrcBuffer, pClient->urcBufferPos,
                                 NULL, 0); // TODO
        }
        pClient->urcBufferPos = 0;
    }
}

static void cmdBeginF(uCxAtClient_t *pClient, const char *pCmd, const char *pParamFmt, va_list args)
{
    U_CX_MUTEX_LOCK(pClient->cmdMutex);

    // Check that previous command has completed
    // If this assert fails you have probably forgotten to call uCxAtClientCmdEnd()
    U_CX_AT_PORT_ASSERT(!pClient->executingCmd);

    pClient->pRspParams = NULL;
    pClient->executingCmd = true;
    pClient->status = NO_STATUS;
    pClient->cmdStartTime = U_CX_PORT_GET_TIME_MS();
    pClient->cmdTimeout = 10000; // Hard coded for now. TODO: Should be function argument
    uCxAtClientSendCmdVaList(pClient, pCmd, pParamFmt, args);
}

static int32_t cmdEnd(uCxAtClient_t *pClient)
{
    while (pClient->status == NO_STATUS) {
        handleRxData(pClient);

        int32_t now = U_CX_PORT_GET_TIME_MS();
        if ((now - pClient->cmdStartTime) > pClient->cmdTimeout) {
            pClient->status = -1;
            break;
        }
    }

    // cmdEnd() must be preceeded by a cmdBeginF()
    U_CX_AT_PORT_ASSERT(pClient->executingCmd);

    pClient->executingCmd = false;

    U_CX_MUTEX_UNLOCK(pClient->cmdMutex);

    // We may have received URCs during command execution
    handleDeferredUrc(pClient);

    return pClient->status;
}

static inline int32_t writeAndLog(uCxAtClient_t *pClient, const void *pData, size_t dataLen)
{
    const struct uCxAtClientConfig *pConfig = pClient->pConfig;
    U_CX_LOG(U_CX_LOG_CHANNEL_TX, "%s", (char *)pData);
    return pConfig->write(pClient, pConfig->pStreamHandle, pData, dataLen);
}

static inline int32_t writeNoLog(uCxAtClient_t *pClient, const void *pData, size_t dataLen)
{
    const struct uCxAtClientConfig *pConfig = pClient->pConfig;
    return pConfig->write(pClient, pConfig->pStreamHandle, pData, dataLen);
}

/* ----------------------------------------------------------------
 * PUBLIC FUNCTIONS
 * -------------------------------------------------------------- */

void uCxAtClientInit(const uCxAtClientConfig_t *pConfig, uCxAtClient_t *pClient)
{
    memset(pClient, 0, sizeof(uCxAtClient_t));
    pClient->pConfig = pConfig;
    U_CX_MUTEX_CREATE(pClient->cmdMutex);
}

void uCxAtClientDeinit(uCxAtClient_t *pClient)
{
    U_CX_MUTEX_DELETE(pClient->cmdMutex);
}

void uCxAtClientSetUrcCallback(uCxAtClient_t *pClient, uUrcCallback_t urcCallback, void *pTag)
{
    pClient->urcCallback = urcCallback;
    pClient->pUrcCallbackTag = pTag;
}

void uCxAtClientSendCmdVaList(uCxAtClient_t *pClient, const char *pCmd, const char *pParamFmt,
                              va_list args)
{
    bool binaryTransfer = false;
    char buf[U_IP_STRING_MAX_LENGTH_BYTES];
    const struct uCxAtClientConfig *pConfig = pClient->pConfig;

    U_CX_LOG_BEGIN(U_CX_LOG_CHANNEL_TX);

    writeAndLog(pClient, pCmd, strlen(pCmd));
    const char *pCh = pParamFmt;
    while (*pCh != 0) {
        if ((pCh != pParamFmt) && (*pCh != 'B')) { // Don't add ',' for Binary transfer
            writeAndLog(pClient, ",", 1);
        }

        memset(&buf, 0, sizeof(buf));
        switch (*pCh) {
            case 'd': {
                // Digit (integer)
                int i = va_arg(args, int);
                int32_t len = snprintf(buf, sizeof(buf), "%d", i);
                writeAndLog(pClient, buf, len);
            }
            break;
            case 's': {
                // String
                char *pStr = va_arg(args, char *);
                writeAndLog(pClient, "\"", 1);
                writeAndLog(pClient, pStr, strlen(pStr));
                writeAndLog(pClient, "\"", 1);
            }
            break;
            case 'i': {
                // IP address
                uSockIpAddress_t *pIpAddr = va_arg(args, uSockIpAddress_t *);
                int32_t len = uCxIpAddressToString(pIpAddr, buf, sizeof(buf));
                U_CX_AT_PORT_ASSERT(len > 0);
                writeAndLog(pClient, buf, len);
            }
            break;
            case 'm': {
                // MAC address
                uMacAddress_t *pMacAddr = va_arg(args, uMacAddress_t *);
                int32_t len = uCxMacAddressToString(pMacAddr, buf, sizeof(buf));
                U_CX_AT_PORT_ASSERT(len > 0);
                writeAndLog(pClient, buf, len);
            }
            break;
            case 'b': {
                // Bluetooth LE address
                uBtLeAddress_t *pBtLeAddr = va_arg(args, uBtLeAddress_t *);
                int32_t len = uCxBdAddressToString(pBtLeAddr, buf, sizeof(buf));
                U_CX_AT_PORT_ASSERT(len > 0);
                writeAndLog(pClient, buf, len);
            }
            break;
            case 'B': {
                // Binary data transfer
                uint8_t *pData = va_arg(args, uint8_t *);
                int32_t len = va_arg(args, int32_t);
                char binHeader[3] = {
                    U_CX_SOH_CHAR,
                    (uint8_t)(len >> 8),
                    (uint8_t)(len & 0xFF),
                };
                U_CX_AT_PORT_ASSERT(len > 0);
                writeNoLog(pClient, binHeader, sizeof(binHeader));
                writeNoLog(pClient, pData, len);
                U_CX_LOG(U_CX_LOG_CHANNEL_TX, "[%d bytes]", len);

                // Binary transfer must always be last param
                U_CX_AT_PORT_ASSERT(pCh[1] == 0);
                binaryTransfer = true;
            }
            break;
            case 'h': {
                // Binary data transferred as hex string
                uint8_t *pData = va_arg(args, uint8_t *);
                int32_t len = va_arg(args, int32_t);
                for (int32_t i = 0; i < len; i++) {
                    uCxAtUtilByteToHex(pData[i], buf);
                    writeAndLog(pClient, buf, 2);
                }
            }
            break;
        }
        pCh++;
    }

    if (!binaryTransfer) {
        pConfig->write(pClient, pConfig->pStreamHandle, "\r", 1);
    }
    U_CX_LOG_END(U_CX_LOG_CHANNEL_TX);
}

int32_t uCxAtClientExecSimpleCmdF(uCxAtClient_t *pClient, const char *pCmd, const char *pParamFmt,
                                  ...)
{
    va_list args;

    va_start(args, pParamFmt);
    cmdBeginF(pClient, pCmd, pParamFmt, args);
    va_end(args);

    return cmdEnd(pClient);
}

int32_t uCxAtClientExecSimpleCmd(uCxAtClient_t *pClient, const char *pCmd)
{
    return uCxAtClientExecSimpleCmdF(pClient, pCmd, "", NULL);
}

void uCxAtClientCmdBeginF(uCxAtClient_t *pClient, const char *pCmd, const char *pParamFmt, ...)
{
    va_list args;

    va_start(args, pParamFmt);
    cmdBeginF(pClient, pCmd, pParamFmt, args);
    va_end(args);
}

char *uCxAtClientCmdGetRspParamLine(uCxAtClient_t *pClient, const char *pExpectedRsp,
                                    uint8_t *pBinaryBuf, size_t *pBinaryBufLength)
{
    char *pRet = NULL;
    pClient->rspBinaryBuf.pBuffer = pBinaryBuf;
    pClient->rspBinaryBuf.pBufferLength = pBinaryBufLength;
    pClient->pRspParams = NULL;
    pClient->pExpectedRsp = pExpectedRsp;
    if (pExpectedRsp) {
        pClient->pExpectedRspLen = strlen(pExpectedRsp);
    } else {
        pClient->pExpectedRspLen = 0;
    }

    while (pClient->status == NO_STATUS) {
        if (handleRxData(pClient) == AT_PARSER_GOT_RSP) {
            pRet = pClient->pRspParams;
            break;
        }
        // Check for timeout
        int32_t now = U_CX_PORT_GET_TIME_MS();
        if ((now - pClient->cmdStartTime) > pClient->cmdTimeout) {
            return NULL;
        }
    }

    return pRet;
}

int32_t uCxAtClientCmdGetRspParamsF(uCxAtClient_t *pClient, const char *pExpectedRsp,
                                    uint8_t *pBinaryBuf, size_t *pBinaryBufLength,
                                    const char *pParamFmt, ...)
{
    va_list args;
    char *pRspParams = uCxAtClientCmdGetRspParamLine(pClient, pExpectedRsp,
                                                     pBinaryBuf, pBinaryBufLength);
    if (pRspParams == NULL) {
        return -1;
    }
    va_start(args, pParamFmt);
    int32_t ret = uCxAtUtilParseParamsVaList(pRspParams, pParamFmt, args);
    va_end(args);

    return ret;
}

int32_t uCxAtClientCmdEnd(uCxAtClient_t *pClient)
{
    return cmdEnd(pClient);
}

void uCxAtClientHandleRx(uCxAtClient_t *pClient)
{
    U_CX_MUTEX_LOCK(pClient->cmdMutex);

    if (!pClient->executingCmd) {
        handleRxData(pClient);
    }

    U_CX_MUTEX_UNLOCK(pClient->cmdMutex);
}
