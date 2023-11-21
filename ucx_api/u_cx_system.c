/*
* This file was automatically generated using csnake v0.3.5.
*
* This file should not be edited directly, any changes will be
* overwritten next time the script is run.
*
* Source code for csnake is available at:
* https://gitlab.com/andrejr/csnake
*
* csnake is also available on PyPI, at :
* https://pypi.org/project/csnake
*/
#include "u_cx_at_client.h"
#include "u_cx_system.h"

int32_t uCxSystemReboot(uCxHandle_t * puCxHandle)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+CPWROFF", "", U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxSystemStoreConfiguration(uCxHandle_t * puCxHandle)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT&W", "", U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxSystemFactoryReset(uCxHandle_t * puCxHandle)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+USYFR", "", U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxSystemDefaultSettings(uCxHandle_t * puCxHandle)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+USYDS", "", U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxSystemSetUartSettings1(uCxHandle_t * puCxHandle, int32_t baud_rate)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+USYUS=", "d", baud_rate, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxSystemSetUartSettings2(uCxHandle_t * puCxHandle, int32_t baud_rate, int32_t flow_control)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+USYUS=", "dd", baud_rate, flow_control, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxSystemSetUartSettings3(uCxHandle_t * puCxHandle, int32_t baud_rate, int32_t flow_control, int32_t change_after_confirm)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+USYUS=", "ddd", baud_rate, flow_control, change_after_confirm, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxBeginSystemGetUartSettings(uCxHandle_t * puCxHandle, uCxSystemGetUartSettings_t * pSystemGetUartSettingsRsp)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    uCxAtClientCmdBeginF(pAtClient, "AT+USYUS?", "", U_CX_AT_UTIL_PARAM_LAST);
    return uCxAtClientCmdGetRspParamsF(pAtClient, "+USYUS:", "dd", &pSystemGetUartSettingsRsp->baud_rate, &pSystemGetUartSettingsRsp->flow_control);
}

int32_t uCxSystemFirmwareUpdate2(uCxHandle_t * puCxHandle, uBootloaderMode_t bootloader_mode, int32_t baud_rate)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+USYFWU=", "dd", bootloader_mode, baud_rate, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxSystemFirmwareUpdate3(uCxHandle_t * puCxHandle, uBootloaderMode_t bootloader_mode, int32_t baud_rate, int32_t flow_control)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+USYFWU=", "ddd", bootloader_mode, baud_rate, flow_control, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxSystemSetEchoOff(uCxHandle_t * puCxHandle)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "ATE0", "", U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxSystemSetEchoOn(uCxHandle_t * puCxHandle)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "ATE1", "", U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxBeginSystemGetEcho(uCxHandle_t * puCxHandle, uEchoOn_t * pEchoOn)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    uCxAtClientCmdBeginF(pAtClient, "ATE?", "", U_CX_AT_UTIL_PARAM_LAST);
    return uCxAtClientCmdGetRspParamsF(pAtClient, "", "d", pEchoOn);
}

int32_t uCxSystemSetEscSequenceChar(uCxHandle_t * puCxHandle, int32_t escape_char)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "ATS2=", "d", escape_char, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxBeginSystemGetEscSequenceChar(uCxHandle_t * puCxHandle, int32_t * pEscapeChar)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    uCxAtClientCmdBeginF(pAtClient, "ATS2?", "", U_CX_AT_UTIL_PARAM_LAST);
    return uCxAtClientCmdGetRspParamsF(pAtClient, "", "d", pEscapeChar);
}

int32_t uCxSystemSetLineTermChar(uCxHandle_t * puCxHandle, int32_t line_term)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "ATS3=", "d", line_term, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxBeginSystemGetLineTermChar(uCxHandle_t * puCxHandle, int32_t * pLineTerm)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    uCxAtClientCmdBeginF(pAtClient, "ATS3?", "", U_CX_AT_UTIL_PARAM_LAST);
    return uCxAtClientCmdGetRspParamsF(pAtClient, "", "d", pLineTerm);
}

int32_t uCxSystemSetRspFormatChar(uCxHandle_t * puCxHandle, int32_t resp_format)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "ATS4=", "d", resp_format, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxBeginSystemGetRspFormatChar(uCxHandle_t * puCxHandle, int32_t * pRespFormat)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    uCxAtClientCmdBeginF(pAtClient, "ATS4?", "", U_CX_AT_UTIL_PARAM_LAST);
    return uCxAtClientCmdGetRspParamsF(pAtClient, "", "d", pRespFormat);
}

int32_t uCxSystemSetBackspaceChar(uCxHandle_t * puCxHandle, int32_t backspace)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "ATS5=", "d", backspace, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxBeginSystemGetBackspaceChar(uCxHandle_t * puCxHandle, int32_t * pBackspace)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    uCxAtClientCmdBeginF(pAtClient, "ATS5?", "", U_CX_AT_UTIL_PARAM_LAST);
    return uCxAtClientCmdGetRspParamsF(pAtClient, "", "d", pBackspace);
}

int32_t uCxSystemSetEscSequenceSettings(uCxHandle_t * puCxHandle, int32_t pre_timeout, int32_t post_timeout, int32_t escape_timeout)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+UTMES=", "ddd", pre_timeout, post_timeout, escape_timeout, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxBeginSystemGetEscSequenceSettings(uCxHandle_t * puCxHandle, uCxSystemGetEscSequenceSettings_t * pSystemGetEscSequenceSettingsRsp)
{
    uCxAtClient_t *pAtClient = puCxHandle->pAtClient;
    uCxAtClientCmdBeginF(pAtClient, "AT+UTMES?", "", U_CX_AT_UTIL_PARAM_LAST);
    return uCxAtClientCmdGetRspParamsF(pAtClient, "+UTMES:", "ddd", &pSystemGetEscSequenceSettingsRsp->pre_timeout, &pSystemGetEscSequenceSettingsRsp->post_timeout, &pSystemGetEscSequenceSettingsRsp->escape_timeout);
}
