/*
 * Copyright (c) 2013-2014, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Patent rights are not granted under this agreement. Patent rights are
 *       available under FRAND terms.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL XEROX or PARC BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/**
 * @file parc_Notifier.h
 * @ingroup threading
 * @brief Inter-thread/process notification
 *
 * A 1-way event notification system.  The first call to parcNotifier_SetEvent() will post an
 * event to the parcNotifier_Socket().  Subsequent calls will not post an event.  When the
 * event consumer is ready to handle the event, it calls parcNotifier_PauseEvents(), then processes
 * the events, then calls parcNotifier_StartEvents().
 *
 * @code
 * {
 *    // example code on the event consumer's side
 *    struct pollfd pfd;
 *    pfd.fd = parcNotifier_Socket(notifier);
 *    pfd.events = POLLIN;
 *
 *    while(1) {
 *       if (poll(&fd, 1, -1)) {
 *           parcNotifier_PauseEvents(notifier);
 *
 *           // process events, such as reading from a RingBuffer
 *           void *data;
 *           while (parcRingBuffer1x1_Get(ring, &data)) {
 *              // handle data
 *           }
 *
 *           parcNotifier_StartEvents(notifier);
 *       }
 *    }
 * }
 * @endcode
 *
 * The notification system guarantees that no notifications will be missed.  However, there may be
 * extra notifications.  For example, in the above code, if an event is signalled between the
 * parcNotifier_PauseEvents() and parcRingBuffer1x1_Get() calls, then on parcNotifier_StartEvents()
 * an extra event will be triggered, even though the ring buffer is empty.
 *
 * @author Marc Mosko, Palo Alto Research Center (Xerox PARC)
 * @copyright 2013-2014, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC).  All rights reserved.
 */

#ifndef libparc_parc_Notifier_h
#define libparc_parc_Notifier_h

#include <stdbool.h>

struct parc_notifier;
typedef struct parc_notifier PARCNotifier;

/**
 * Create a new instance of `PARCNotifier`
 *
 * @return  A new instance of `PARCNotifier`
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
PARCNotifier *parcNotifier_Create(void);

/**
 * Increase the number of references to a `PARCNotifier`.
 *
 * Note that new `PARCNotifier` is not created,
 * only that the given `PARCNotifier` reference count is incremented.
 * Discard the reference by invoking `parcNotifier_Release`.
 *
 * @param [in] instance A pointer to a `PARCNotifier` instance.
 *
 * @return The input `PARCNotifier` pointer.
 *
 * Example:
 * @code
 * {
 *     PARCNotifier *a = parcNotifier_Create(...);
 *
 *     PARCNotifier *b = parcNotifier_Acquire(a);
 *
 *     parcNotifier_Release(&a);
 *     parcNotifier_Release(&b);
 * }
 * @endcode
 */
PARCNotifier *parcNotifier_Acquire(const PARCNotifier *notifier);

/**
 * Release a previously acquired reference to the specified instance,
 * decrementing the reference count for the instance.
 *
 * The pointer to the instance is set to NULL as a side-effect of this function.
 *
 * If the invocation causes the last reference to the instance to be released,
 * the instance is deallocated and the instance's implementation will perform
 * additional cleanup and release other privately held references.
 *
 * @param [in,out] instancePtr A pointer to a pointer to the instance to release, which will be set to NULL.
 *
 * Example:
 * @code
 * {
 *     PARCNotifier *a = parcNotifier_Create(...);
 *
 *     parcNotifier_Release(&a);
 * }
 * @endcode
 */
void parcNotifier_Release(PARCNotifier **notifier);

/**
 * Fetches the notification socket
 *
 * The notification socket may be used in select() or poll() or similar
 * functions.  You should not read or write to the socket.
 *
 * @param [in] notifier The instance of `PARCNotifier`
 *
 * @return The notification socket.
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
int parcNotifier_Socket(PARCNotifier *notifier);

/**
 * Sends a notification to the notifier socket
 *
 * @param [in] notifier The instance of `PARCNotifier`
 *
 * @return True is successsful, else false.
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
bool parcNotifier_Notify(PARCNotifier *notifier);

/**
 * Pause the event stream of the Notifier
 *
 * @param [in] notifier The instance of `PARCNotifier`
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
void parcNotifier_PauseEvents(PARCNotifier *notifier);

/**
 * Restart the event stream of the Notifier
 *
 * @param [in] notifier The instance of `PARCNotifier`
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
void parcNotifier_StartEvents(PARCNotifier *notifier);
#endif // libparc_parc_Notifier_h
