/** @file
 * @brief Basic logging facility
 */

#ifndef U_CX_LOG_H
#define U_CX_LOG_H

#include <stdarg.h>
#include <stdint.h>

#include "u_cx_at_config.h"

/* ----------------------------------------------------------------
 * COMPILE-TIME MACROS
 * -------------------------------------------------------------- */

/* Log channels (used as input for U_CX_LOG_BEGIN() and U_CX_LOG_LINE()) */
#define U_CX_LOG_CHANNEL_TX     U_CX_LOG_AT, ANSI_CYN "[AT TX]"
#define U_CX_LOG_CHANNEL_RX     U_CX_LOG_AT, ANSI_MAG "[AT RX]"

/* Simple line logging printf style (\n will be added automatically) */
#define U_CX_LOG_LINE(logCh, format, ...)  _U_CX_LOG_BEGIN_FMT(logCh, format ANSI_RST "\n", ##__VA_ARGS__)

/* Log API for splitting up line in several U_CX_LOG() calls */
#define U_CX_LOG_BEGIN(logCh)              _U_CX_LOG_BEGIN_FMT(logCh, "")
#define U_CX_LOG(logCh, format, ...)       _U_CX_LOG(logCh, format, ##__VA_ARGS__)
#define U_CX_LOG_END(logCh)                _U_CX_LOG(logCh, ANSI_RST "\n")



#if U_CX_LOG_USE_ANSI_COLOR
# define ANSI_BLU "\e[0;34m"
# define ANSI_CYN "\e[0;36m"
# define ANSI_GRN "\e[0;32m"
# define ANSI_MAG "\e[0;35m"
# define ANSI_YEL "\e[0;33m"
# define ANSI_RST "\e[0m"
#else
# define ANSI_BLU
# define ANSI_CYN
# define ANSI_GRN
# define ANSI_MAG
# define ANSI_YEL
# define ANSI_RST
#endif

/* Internal defines - do not use! */
#define _U_CX_LOG_BEGIN_FMT(enabled, chText, format, ...)   \
    if (enabled) {                                          \
        uCxLogPrintTime();                                  \
        U_CX_PORT_PRINTF(chText " " format, ##__VA_ARGS__); \
    }
#define _U_CX_LOG(enabled, chText, format, ...)  \
    if (enabled) {                               \
        U_CX_PORT_PRINTF(format, ##__VA_ARGS__); \
    }

/* ----------------------------------------------------------------
 * TYPES
 * -------------------------------------------------------------- */

/* ----------------------------------------------------------------
 * VARIABLES
 * -------------------------------------------------------------- */

/* ----------------------------------------------------------------
 * PUBLIC FUNCTIONS
 * -------------------------------------------------------------- */

void uCxLogPrintTime(void);

#endif // U_CX_LOG_H