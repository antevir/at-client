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
#ifndef _U_CX_SOCKET_H_
#define _U_CX_SOCKET_H_

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
    int32_t socket_handle;  /**< Socket identifier to be used for any future operation on that socket. */
    int32_t written_length; /**< Data length that was written. */
} uCxSocketWriteString_t;

typedef struct
{
    int32_t socket_handle;    /**< Socket identifier to be used for any future operation on that socket. */
    int32_t length;           /**< Number of bytes to read. */
    const char * string_data; /**< Data encoded as ascii chars. */
} uCxSocketReadString_t;

typedef struct
{
    int32_t socket_handle;         /**< Socket identifier to be used for any future operation on that socket. */
    uProtocol_t protocol;          /**< IP protocol. */
    uSocketStatus_t socket_status;
} uCxSocketStatus_t;

/* ------------------------------------------------------------
 * COMMAND HANDLERS
 * ---------------------------------------------------------- */

/**
 * Creates a socket and associates it with the specified protocol (TCP or UDP).
 * 
 * Output AT command:
 * > AT+USOCR=<protocol>
 *
 * @param[in]  puCxHandle:    uCX API handle
 * @param      protocol:      IP protocol.
 * @param[out] pSocketHandle: Socket identifier to be used for any future operation on that socket.
 */
int32_t uCxBeginSocketCreate1(uCxHandle_t * puCxHandle, uProtocol_t protocol, int32_t * pSocketHandle);

/**
 * Creates a socket and associates it with the specified protocol (TCP or UDP).
 * 
 * Output AT command:
 * > AT+USOCR=<protocol>,<preferred_protocol_type>
 *
 * @param[in]  puCxHandle:              uCX API handle
 * @param      protocol:                IP protocol.
 * @param      preferred_protocol_type: Selects the IP address type to use.
 * @param[out] pSocketHandle:           Socket identifier to be used for any future operation on that socket.
 */
int32_t uCxBeginSocketCreate2(uCxHandle_t * puCxHandle, uProtocol_t protocol, uPreferredProtocolType_t preferred_protocol_type, int32_t * pSocketHandle);

/**
 * Establish a peer-to-peer connection to the specified remote host on the given remote port.
 * 
 * Output AT command:
 * > AT+USOC=<socket_handle>,<host_address>,<remote_port>
 *
 * @param[in]  puCxHandle:    uCX API handle
 * @param      socket_handle: Socket identifier to be used for any future operation on that socket.
 * @param      host_address:  Remote host IP address or domain name of the remote host.
 * @param      remote_port:   The port of the remote peer.
 */
int32_t uCxSocketConnect(uCxHandle_t * puCxHandle, int32_t socket_handle, const char * host_address, int32_t remote_port);

/**
 * Set the mode in which you would like to receive data in AT mode.
 * NOTE: Any created sockets or created persistent sockets will use the same receive mode as was configured when they were
 * created
 * 
 * Output AT command:
 * > AT+USORM=<read_mode>
 *
 * @param[in]  puCxHandle: uCX API handle
 * @param      read_mode:  Modes to read data in AT
 */
int32_t uCxSocketSetReadMode(uCxHandle_t * puCxHandle, uReadMode_t read_mode);

/**
 * Read the current receive mode
 * 
 * Output AT command:
 * > AT+USORM?
 *
 * @param[in]  puCxHandle: uCX API handle
 * @param[out] pReadMode:  Modes to read data in AT
 */
int32_t uCxBeginSocketGetReadMode(uCxHandle_t * puCxHandle, uReadMode_t * pReadMode);

/**
 * Writes string data to the specified socket.
 * The command can be used for both TCP and UDP sockets after calling ${ref:AT+USOC}. 
 * If socket is not ready to be written, generic negative error will be returned. 
 * Check BSD errno (see BSD standard) by calling ${ref:AT+USOE}.
 * 
 * Output AT command:
 * > AT+USOWS=<socket_handle>,<string_data>
 *
 * @param[in]  puCxHandle:            uCX API handle
 * @param      socket_handle:         Socket identifier to be used for any future operation on that socket.
 * @param      string_data:           Data encoded as ascii chars.
 * @param[out] pSocketWriteStringRsp: Please see \ref uCxSocketWriteString_t
 */
int32_t uCxBeginSocketWriteString(uCxHandle_t * puCxHandle, int32_t socket_handle, const char * string_data, uCxSocketWriteString_t * pSocketWriteStringRsp);

/**
 * Closes the specified socket.
 * 
 * The command blocks the AT command interface until the completion of the socket close operation.
 * When this function returns OK the socket is cleaned up and fully closed.
 * 
 * Output AT command:
 * > AT+USOCL=<socket_handle>
 *
 * @param[in]  puCxHandle:    uCX API handle
 * @param      socket_handle: Socket identifier to be used for any future operation on that socket.
 */
int32_t uCxSocketClose(uCxHandle_t * puCxHandle, int32_t socket_handle);

/**
 * Reads the specified amount of data from the specified socket.
 * Note that the data should include no null terminator characters.
 * 
 * Output AT command:
 * > AT+USORS=<socket_handle>,<length>
 *
 * @param[in]  puCxHandle:           uCX API handle
 * @param      socket_handle:        Socket identifier to be used for any future operation on that socket.
 * @param      length:               Number of bytes to read.
 * @param[out] pSocketReadStringRsp: Please see \ref uCxSocketReadString_t
 */
int32_t uCxBeginSocketReadString(uCxHandle_t * puCxHandle, int32_t socket_handle, int32_t length, uCxSocketReadString_t * pSocketReadStringRsp);

/**
 * Sets the specified socket in listening mode on the specified port of service, waiting for incoming connections (TCP) or
 * data (UDP).
 * 
 * Output AT command:
 * > AT+USOL=<socket_handle>,<port>
 *
 * @param[in]  puCxHandle:    uCX API handle
 * @param      socket_handle: Socket identifier to be used for any future operation on that socket.
 * @param      port:          Port of service, range 1-65535. Port numbers below 1024 are not recommended since they are
 *                            usually reserved
 */
int32_t uCxSocketListen(uCxHandle_t * puCxHandle, int32_t socket_handle, int32_t port);

/**
 * List status for all created sockets.
 * 
 * Output AT command:
 * > AT+USOST?
 *
 * @param[in]  puCxHandle:       uCX API handle
 * @param[out] pSocketStatusRsp: Please see \ref uCxSocketStatus_t
 */
int32_t uCxBeginSocketStatus(uCxHandle_t * puCxHandle, uCxSocketStatus_t * pSocketStatusRsp);

/**
 * Set a socket option. See available options below.
 * 
 * Output AT command:
 * > AT+USOO=<socket_handle>,<option>,<value>
 *
 * @param[in]  puCxHandle:    uCX API handle
 * @param      socket_handle: Socket identifier to be used for any future operation on that socket.
 * @param      option:        Available options to set
 * @param      value:         See option parameter
 */
int32_t uCxSocketSetOption(uCxHandle_t * puCxHandle, int32_t socket_handle, uOption_t option, int32_t value);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _U_CX_SOCKET_H_ */