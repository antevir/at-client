/** @file
 * @brief Queue for incoming URCs
 *
 * This queue is used by u_cx_at_client for supporting calls
 * to u_cx_at_client directly from URC handler.
 */

#ifndef U_CX_AT_URC_QUEUE_H
#define U_CX_AT_URC_QUEUE_H

#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stddef.h>

#include "u_cx_at_util.h"
#include "u_cx_at_params.h"

/* ----------------------------------------------------------------
 * COMPILE-TIME MACROS
 * -------------------------------------------------------------- */

/* ----------------------------------------------------------------
 * TYPES
 * -------------------------------------------------------------- */

typedef struct {
    uint16_t strLineLen;  // String length excluding null term
    uint16_t payloadSize; // Binary payload length (0 if none)
    uint8_t data[];       // Layout is {strLineLen}{null term}{payloadSize}
} uUrcEntry_t;

typedef struct uCxAtUrcQueue {
    uint8_t *pBuffer;
    size_t bufferLen;
    size_t bufferPos;
    U_CX_MUTEX_HANDLE queueMutex;
    U_CX_MUTEX_HANDLE dequeueMutex;
    uUrcEntry_t *pEnqueueEntry;
    uUrcEntry_t *pDequeueEntry;
} uCxAtUrcQueue_t;

/* ----------------------------------------------------------------
 * VARIABLES
 * -------------------------------------------------------------- */

/* ----------------------------------------------------------------
 * PUBLIC FUNCTIONS
 * -------------------------------------------------------------- */

/**
  * @brief  AT URC queue init
  *
  * This function must be called before any other uCxAtUrcQueueXxx function is called.
  *
  * @param[out] pUrcQueue: a pointer to an AT URC queue struct that will be initialized.
  * @param[in]  pBuffer:   the buffer to be used by the URC queue.
  * @param      bufferLen: the length of the buffer to be used by the URC queue.
  */
void uCxAtUrcQueueInit(uCxAtUrcQueue_t *pUrcQueue, void *pBuffer, size_t bufferLen);

/**
  * @brief  AT URC queue deinit
  *
  * Calling this will release any resources allocated by uCxAtUrcQueueInit().
  *
  * @param[in]  pUrcQueue: the URC queue initialized with uCxAtUrcQueueInit().
  *
  */
void uCxAtUrcQueueDeInit(uCxAtUrcQueue_t *pUrcQueue);


/**
  * @brief  Begin enqueueing a URC entry
  *
  * NOTE: When this function returns true caller must call either uCxAtUrcQueueEnqueueEnd()
  *       OR uCxAtUrcQueueEnqueueAbort() to complete the enqueueing.
  *
  * @param[in]  pUrcQueue: the URC queue initialized with uCxAtUrcQueueInit().
  * @return                true on success, false if there are no room for the URC string.
  */
bool uCxAtUrcQueueEnqueueBegin(uCxAtUrcQueue_t *pUrcQueue, const char *pUrcLine, size_t urcLineLen);

/**
  * @brief  Get payload pointer for current enqueue entry
  *
  * @param[in]  pUrcQueue: the URC queue initialized with uCxAtUrcQueueInit().
  * @param[out] ppPayload: the pointer value will be set to the address of the payload buffer.
  * @return                the available payload space.
  */
size_t uCxAtUrcQueueEnqueueGetPayloadPtr(uCxAtUrcQueue_t *pUrcQueue, uint8_t **ppPayload);

/**
  * @brief  Complete the URC enqueueing
  *
  * @param[in]  pUrcQueue:   the URC queue initialized with uCxAtUrcQueueInit().
  * @param      payloadSize: the size of the payload added by writing to pointer
  *                          fetched with uCxAtUrcQueueEnqueueGetPayloadPtr().
  *                          Set to 0 if there are no payload.
  */
void uCxAtUrcQueueEnqueueEnd(uCxAtUrcQueue_t *pUrcQueue, size_t payloadSize);

/**
  * @brief  Abort the URC enqueueing
  *
  * Useful when the payload can't be fitted into the queue.
  *
  * @param[in]  pUrcQueue:   the URC queue initialized with uCxAtUrcQueueInit().
  */
void uCxAtUrcQueueEnqueueAbort(uCxAtUrcQueue_t *pUrcQueue);

/**
  * @brief  Begin URC dequeueing
  *
  * NOTE: When this function returns a non-NULL value caller must call uCxAtUrcQueueDequeueEnd()
  *       to complete the dequeueing.
  *
  * @param[in]  pUrcQueue: the URC queue initialized with uCxAtUrcQueueInit().
  * @return                NULL if queue is empty otherwise a URC entry pointer.
  */
uUrcEntry_t *uCxAtUrcQueueDequeueBegin(uCxAtUrcQueue_t *pUrcQueue);

/**
  * @brief  End URC dequeueing
  *
  * When the entry pEntry has been processed, call this function to pop
  * the entry from the queue.
  *
  * @param[in]  pUrcQueue: the URC queue initialized with uCxAtUrcQueueInit().
  */
void uCxAtUrcQueueDequeueEnd(uCxAtUrcQueue_t *pUrcQueue, uUrcEntry_t *pEntry);

#endif // U_CX_AT_URC_QUEUE_H
