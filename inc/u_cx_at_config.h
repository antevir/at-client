/** @file
 * @brief Configuration file for the uCX AT client
 */
#ifndef U_CX_AT_CONFIG_H
#define U_CX_AT_CONFIG_H

/* To override the default settings you can define U_CX_AT_CONFIG_FILE
 * to include a custom configuration header file
 */
#ifdef U_CX_AT_CONFIG_FILE
# include U_CX_AT_CONFIG_FILE
#endif

struct uCxAtClient;

/* U_CX_AT_PORT_WRITE can be used to redefine the function that will be called
 * when writing to the AT interface (typically UART)
 */
#ifndef U_CX_AT_PORT_WRITE
extern size_t uCxAtWrite(struct uCxAtClient *pClient, const void *pData, size_t length);
# define U_CX_AT_PORT_WRITE(AT_CLIENT, DATA, DATA_LEN) uCxAtWrite(AT_CLIENT, DATA, DATA_LEN)
#endif

/* U_CX_AT_PORT_READ can be used to redefine the function that will be called
 * when reading from the AT interface (typically UART)
 */
#ifndef U_CX_AT_PORT_READ
extern size_t uCxAtRead(struct uCxAtClient *pClient, void *pData, size_t length);
# define U_CX_AT_PORT_READ(AT_CLIENT, DATA, DATA_LEN) uCxAtRead(AT_CLIENT, DATA, DATA_LEN)
#endif


/* U_CX_AT_PORT_ASSERT is used for asserts. To disable asserts just define U_CX_AT_PORT_ASSERT
 * to nothing like this:
 * #define U_CX_AT_PORT_ASSERT(COND)
 */
#ifndef U_CX_AT_PORT_ASSERT
# define U_CX_AT_PORT_ASSERT(COND) assert(COND)
#endif

#endif // U_CX_AT_CONFIG_H