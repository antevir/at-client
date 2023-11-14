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


/* U_CX_AT_PORT_ASSERT is used for asserts. To disable asserts just define U_CX_AT_PORT_ASSERT
 * to nothing like this:
 * #define U_CX_AT_PORT_ASSERT(COND)
 */
#ifndef U_CX_AT_PORT_ASSERT
# include <assert.h>
# define U_CX_AT_PORT_ASSERT(COND) assert(COND)
#endif

/* Porting layer for printf().*/
#ifndef U_CX_PORT_PRINTF
# include <stdio.h>
# define U_CX_PORT_PRINTF   printf
#endif

/* Configuration for enabling logging off AT protocol.*/
#ifndef U_CX_LOG_AT
# define U_CX_LOG_AT 1
#endif

/* Configuration for enabling ANSI color for logs.*/
#ifndef U_CX_LOG_USE_ANSI_COLOR
# define U_CX_LOG_USE_ANSI_COLOR 1
#endif

#endif // U_CX_AT_CONFIG_H