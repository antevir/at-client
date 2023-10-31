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
#include "u_cx_system.h"

int32_t uCxSystemFactoryReset(uCxAtClient_t * pAtClient)
{
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+USYFR", "", U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxSystemSetUartSettings1(uCxAtClient_t * pAtClient, int32_t baud_rate)
{
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+USYUS=", "d", baud_rate, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxSystemSetUartSettings2(uCxAtClient_t * pAtClient, int32_t baud_rate, int32_t flow_control)
{
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+USYUS=", "dd", baud_rate, flow_control, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxSystemSetUartSettings3(uCxAtClient_t * pAtClient, int32_t baud_rate, int32_t flow_control, int32_t change_after_confirm)
{
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+USYUS=", "ddd", baud_rate, flow_control, change_after_confirm, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxBeginSystemGetUartSettings(uCxAtClient_t * pAtClient, uCxSystemGetUartSettings_t * pSystemGetUartSettingsRsp)
{
    uCxAtClientCmdBeginF(pAtClient, "AT+USYUS?", "", U_CX_AT_UTIL_PARAM_LAST);
    return uCxAtClientCmdGetRspParamsF(pAtClient, "+USYUS:", "dd", &pSystemGetUartSettingsRsp->baud_rate, &pSystemGetUartSettingsRsp->flow_control);
}

int32_t uCxSystemFirmwareUpdate2(uCxAtClient_t * pAtClient, uBootloaderMode_t bootloader_mode, int32_t baud_rate)
{
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+USYFWU=", "dd", bootloader_mode, baud_rate, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxSystemFirmwareUpdate3(uCxAtClient_t * pAtClient, uBootloaderMode_t bootloader_mode, int32_t baud_rate, int32_t flow_control)
{
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+USYFWU=", "ddd", bootloader_mode, baud_rate, flow_control, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxSystemSetEchoOff(uCxAtClient_t * pAtClient)
{
    return uCxAtClientExecSimpleCmdF(pAtClient, "ATE0", "", U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxSystemSetEchoOn(uCxAtClient_t * pAtClient)
{
    return uCxAtClientExecSimpleCmdF(pAtClient, "ATE1", "", U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxBeginSystemGetEcho(uCxAtClient_t * pAtClient, uEchoOn_t * pEchoOn)
{
    uCxAtClientCmdBeginF(pAtClient, "ATE?", "", U_CX_AT_UTIL_PARAM_LAST);
    return uCxAtClientCmdGetRspParamsF(pAtClient, "", "d", pEchoOn);
}

int32_t uCxSystemSetEscSequenceChar(uCxAtClient_t * pAtClient, int32_t escape_char)
{
    return uCxAtClientExecSimpleCmdF(pAtClient, "ATS2=", "d", escape_char, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxBeginSystemGetEscSequenceChar(uCxAtClient_t * pAtClient, int32_t * pEscapeChar)
{
    uCxAtClientCmdBeginF(pAtClient, "ATS2?", "", U_CX_AT_UTIL_PARAM_LAST);
    return uCxAtClientCmdGetRspParamsF(pAtClient, "", "d", pEscapeChar);
}

int32_t uCxSystemSetLineTermChar(uCxAtClient_t * pAtClient, int32_t line_term)
{
    return uCxAtClientExecSimpleCmdF(pAtClient, "ATS3=", "d", line_term, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxBeginSystemGetLineTermChar(uCxAtClient_t * pAtClient, int32_t * pLineTerm)
{
    uCxAtClientCmdBeginF(pAtClient, "ATS3?", "", U_CX_AT_UTIL_PARAM_LAST);
    return uCxAtClientCmdGetRspParamsF(pAtClient, "", "d", pLineTerm);
}

int32_t uCxSystemSetRspFormatChar(uCxAtClient_t * pAtClient, int32_t resp_format)
{
    return uCxAtClientExecSimpleCmdF(pAtClient, "ATS4=", "d", resp_format, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxBeginSystemGetRspFormatChar(uCxAtClient_t * pAtClient, int32_t * pRespFormat)
{
    uCxAtClientCmdBeginF(pAtClient, "ATS4?", "", U_CX_AT_UTIL_PARAM_LAST);
    return uCxAtClientCmdGetRspParamsF(pAtClient, "", "d", pRespFormat);
}

int32_t uCxSystemSetBackspaceChar(uCxAtClient_t * pAtClient, int32_t backspace)
{
    return uCxAtClientExecSimpleCmdF(pAtClient, "ATS5=", "d", backspace, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxBeginSystemGetBackspaceChar(uCxAtClient_t * pAtClient, int32_t * pBackspace)
{
    uCxAtClientCmdBeginF(pAtClient, "ATS5?", "", U_CX_AT_UTIL_PARAM_LAST);
    return uCxAtClientCmdGetRspParamsF(pAtClient, "", "d", pBackspace);
}

int32_t uCxSystemSetEscSequenceSettings(uCxAtClient_t * pAtClient, int32_t pre_timeout, int32_t post_timeout, int32_t escape_timeout)
{
    return uCxAtClientExecSimpleCmdF(pAtClient, "AT+UTMES=", "ddd", pre_timeout, post_timeout, escape_timeout, U_CX_AT_UTIL_PARAM_LAST);
}

int32_t uCxBeginSystemGetEscSequenceSettings(uCxAtClient_t * pAtClient, uCxSystemGetEscSequenceSettings_t * pSystemGetEscSequenceSettingsRsp)
{
    uCxAtClientCmdBeginF(pAtClient, "AT+UTMES?", "", U_CX_AT_UTIL_PARAM_LAST);
    return uCxAtClientCmdGetRspParamsF(pAtClient, "+UTMES:", "ddd", &pSystemGetEscSequenceSettingsRsp->pre_timeout, &pSystemGetEscSequenceSettingsRsp->post_timeout, &pSystemGetEscSequenceSettingsRsp->escape_timeout);
}
