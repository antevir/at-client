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
#ifndef _U_CX_SYSTEM_H_
#define _U_CX_SYSTEM_H_

#include <stddef.h>
#include <stdint.h>
#include "u_cx_types.h"
#include "u_cx.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* ------------------------------------------------------------
 * RESPONSE STRUCTS
 * ---------------------------------------------------------- */

typedef struct
{
    int32_t baud_rate;    /**< Baudrate */
    int32_t flow_control;
} uCxSystemGetUartSettings_t;

typedef struct
{
    int32_t pre_timeout;    /**< Minimum time (ms) of no data activity required before the escape sequence is sent. Factory
                                 default: 1000 */
    int32_t post_timeout;   /**< Minimum time (ms) of no data activity required after the escape sequence is sent. Factory
                                 default: 1000 */
    int32_t escape_timeout; /**< Maximum time interval (ms) between escape characters. Factory default: 200 */
} uCxSystemGetEscSequenceSettings_t;

/* ------------------------------------------------------------
 * COMMAND HANDLERS
 * ---------------------------------------------------------- */

/**
 * Reset to factory defined defaults. A reboot is required before using the new settings.
 * 
 * Output AT command:
 * > AT+USYFR
 *
 * @param[in]  puCxHandle: uCX API handle
 */
int32_t uCxSystemFactoryReset(uCxHandle_t * puCxHandle);

/**
 * Configure new UART settings that will be used after restart
 * 
 * Output AT command:
 * > AT+USYUS=<baud_rate>
 *
 * @param[in]  puCxHandle: uCX API handle
 * @param      baud_rate:  Baudrate
 */
int32_t uCxSystemSetUartSettings1(uCxHandle_t * puCxHandle, int32_t baud_rate);

/**
 * Configure new UART settings that will be used after restart
 * 
 * Output AT command:
 * > AT+USYUS=<baud_rate>,<flow_control>
 *
 * @param[in]  puCxHandle:   uCX API handle
 * @param      baud_rate:    Baudrate
 * @param      flow_control: 
 */
int32_t uCxSystemSetUartSettings2(uCxHandle_t * puCxHandle, int32_t baud_rate, int32_t flow_control);

/**
 * Configure new UART settings that will be used after restart
 * 
 * Output AT command:
 * > AT+USYUS=<baud_rate>,<flow_control>,<change_after_confirm>
 *
 * @param[in]  puCxHandle:           uCX API handle
 * @param      baud_rate:            Baudrate
 * @param      flow_control:         
 * @param      change_after_confirm: 
 */
int32_t uCxSystemSetUartSettings3(uCxHandle_t * puCxHandle, int32_t baud_rate, int32_t flow_control, int32_t change_after_confirm);

/**
 * Reads current UART settings from the module
 * 
 * Output AT command:
 * > AT+USYUS?
 *
 * @param[in]  puCxHandle:                uCX API handle
 * @param[out] pSystemGetUartSettingsRsp: Please see \ref uCxSystemGetUartSettings_t
 */
int32_t uCxBeginSystemGetUartSettings(uCxHandle_t * puCxHandle, uCxSystemGetUartSettings_t * pSystemGetUartSettingsRsp);

/**
 * Force start of the boot loader.
 * 
 * Output AT command:
 * > AT+USYFWU=<bootloader_mode>,<baud_rate>
 *
 * @param[in]  puCxHandle:      uCX API handle
 * @param      bootloader_mode: 
 * @param      baud_rate:       
 */
int32_t uCxSystemFirmwareUpdate2(uCxHandle_t * puCxHandle, uBootloaderMode_t bootloader_mode, int32_t baud_rate);

/**
 * Force start of the boot loader.
 * 
 * Output AT command:
 * > AT+USYFWU=<bootloader_mode>,<baud_rate>,<flow_control>
 *
 * @param[in]  puCxHandle:      uCX API handle
 * @param      bootloader_mode: 
 * @param      baud_rate:       
 * @param      flow_control:    
 */
int32_t uCxSystemFirmwareUpdate3(uCxHandle_t * puCxHandle, uBootloaderMode_t bootloader_mode, int32_t baud_rate, int32_t flow_control);

/**
 * Set echo off
 * 
 * Output AT command:
 * > ATE0
 *
 * @param[in]  puCxHandle: uCX API handle
 */
int32_t uCxSystemSetEchoOff(uCxHandle_t * puCxHandle);

/**
 * Set echo on
 * 
 * Output AT command:
 * > ATE1
 *
 * @param[in]  puCxHandle: uCX API handle
 */
int32_t uCxSystemSetEchoOn(uCxHandle_t * puCxHandle);

/**
 * Read current echo setting
 * 
 * Output AT command:
 * > ATE?
 *
 * @param[in]  puCxHandle: uCX API handle
 * @param[out] pEchoOn:    
 */
int32_t uCxBeginSystemGetEcho(uCxHandle_t * puCxHandle, uEchoOn_t * pEchoOn);

/**
 * Write escape character. This settings change the decimal value of the escape character used by some modes, such as
 * transparent mode for example, to detect an escape sequence and exit.
 * 
 * Output AT command:
 * > ATS2=<escape_char>
 *
 * @param[in]  puCxHandle:  uCX API handle
 * @param      escape_char: Escape character. Factory default: 43
 */
int32_t uCxSystemSetEscSequenceChar(uCxHandle_t * puCxHandle, int32_t escape_char);

/**
 * Read escape character
 * 
 * Output AT command:
 * > ATS2?
 *
 * @param[in]  puCxHandle:  uCX API handle
 * @param[out] pEscapeChar: Escape character. Factory default: 43
 */
int32_t uCxBeginSystemGetEscSequenceChar(uCxHandle_t * puCxHandle, int32_t * pEscapeChar);

/**
 * Write line termination character. This setting changes the decimal value of the character recognized by the DCE from the
 * DTE to terminate an incoming command line. It is also generated by the DCE as part of the header, trailer, and
 * terminator for result codes and information text along with the S4 parameter. The previous value of S3 is used to
 * determine the command line termination character for entry of the command line containing the S3 setting command.
 * However, the result code issued shall use the value of S3 as set during the processing of the command line. For example,
 * if S3 was previously set to 13 and the command line "ATS3=30" is issued, the command line shall be terminated with a CR,
 * character (13), but the result code issued will use the character with the ordinal value 30 instead of the CR.
 * 
 * Output AT command:
 * > ATS3=<line_term>
 *
 * @param[in]  puCxHandle: uCX API handle
 * @param      line_term:  Command line termination character. Factory default: 13
 */
int32_t uCxSystemSetLineTermChar(uCxHandle_t * puCxHandle, int32_t line_term);

/**
 * Read line termination character
 * 
 * Output AT command:
 * > ATS3?
 *
 * @param[in]  puCxHandle: uCX API handle
 * @param[out] pLineTerm:  Command line termination character. Factory default: 13
 */
int32_t uCxBeginSystemGetLineTermChar(uCxHandle_t * puCxHandle, int32_t * pLineTerm);

/**
 * Write response format character. This setting changes the decimal value of the character generated by the DCE as part of
 * the header, trailer, and terminator for result codes and information text, along with the S3 parameter. If the value of
 * S4 is changed in a command line, the result code issued in response to that command line will use the new value of S4.
 * 
 * Output AT command:
 * > ATS4=<resp_format>
 *
 * @param[in]  puCxHandle:  uCX API handle
 * @param      resp_format: Response format character. Factory default: 10
 */
int32_t uCxSystemSetRspFormatChar(uCxHandle_t * puCxHandle, int32_t resp_format);

/**
 * Read response format character
 * 
 * Output AT command:
 * > ATS4?
 *
 * @param[in]  puCxHandle:  uCX API handle
 * @param[out] pRespFormat: Response format character. Factory default: 10
 */
int32_t uCxBeginSystemGetRspFormatChar(uCxHandle_t * puCxHandle, int32_t * pRespFormat);

/**
 * Writes backspace character. This setting changes the decimal value of the character recognized by the DCE as a request
 * to delete from the command line, the immediately preceding character.
 * 
 * Output AT command:
 * > ATS5=<backspace>
 *
 * @param[in]  puCxHandle: uCX API handle
 * @param      backspace:  Backspace character. Factory default: 8
 */
int32_t uCxSystemSetBackspaceChar(uCxHandle_t * puCxHandle, int32_t backspace);

/**
 * Read backspace character
 * 
 * Output AT command:
 * > ATS5?
 *
 * @param[in]  puCxHandle: uCX API handle
 * @param[out] pBackspace: Backspace character. Factory default: 8
 */
int32_t uCxBeginSystemGetBackspaceChar(uCxHandle_t * puCxHandle, int32_t * pBackspace);

/**
 * Configures the transparent mode escape sequence settings.
 * 
 * Output AT command:
 * > AT+UTMES=<pre_timeout>,<post_timeout>,<escape_timeout>
 *
 * @param[in]  puCxHandle:     uCX API handle
 * @param      pre_timeout:    Minimum time (ms) of no data activity required before the escape sequence is sent. Factory
 *                             default: 1000
 * @param      post_timeout:   Minimum time (ms) of no data activity required after the escape sequence is sent. Factory
 *                             default: 1000
 * @param      escape_timeout: Maximum time interval (ms) between escape characters. Factory default: 200
 */
int32_t uCxSystemSetEscSequenceSettings(uCxHandle_t * puCxHandle, int32_t pre_timeout, int32_t post_timeout, int32_t escape_timeout);

/**
 * Reads current transparent mode escape sequence settings.
 * 
 * Output AT command:
 * > AT+UTMES?
 *
 * @param[in]  puCxHandle:                       uCX API handle
 * @param[out] pSystemGetEscSequenceSettingsRsp: Please see \ref uCxSystemGetEscSequenceSettings_t
 */
int32_t uCxBeginSystemGetEscSequenceSettings(uCxHandle_t * puCxHandle, uCxSystemGetEscSequenceSettings_t * pSystemGetEscSequenceSettingsRsp);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _U_CX_SYSTEM_H_ */