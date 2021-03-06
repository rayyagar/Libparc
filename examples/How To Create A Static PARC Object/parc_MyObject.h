/*
 * Copyright (c) 2016, Xerox Corporation (Xerox) and Palo Alto Research Center, Inc (PARC)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL XEROX OR PARC BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * ################################################################################
 * #
 * # PATENT NOTICE
 * #
 * # This software is distributed under the BSD 2-clause License (see LICENSE
 * # file).  This BSD License does not make any patent claims and as such, does
 * # not act as a patent grant.  The purpose of this file is for each contributor
 * # to define their intentions with respect to intellectual property.
 * #
 * # Each contributor to this source code is encouraged to state their patent
 * # claims and licensing mechanisms for any contributions made. At the end of
 * # this file contributors may each make their own statements.  Contributor's
 * # claims and grants only apply to the pieces (source code, programs, text,
 * # media, etc) that they have contributed directly to this software.
 * #
 * # There is no guarantee that this file is complete, up to date or accurate. It
 * # is up to the contributors to maintain their section in this file up to date
 * # and up to the user of the software to verify any claims herein.
 * #
 * # Do not remove this header notification.  The contents of this file must be
 * # present in all distributions of the software.  You may only modify your own
 * # intellectual property statements.  Please provide contact information.
 *
 * - Palo Alto Research Center, Inc
 * This software distribution does not grant any rights to patents owned by Palo
 * Alto Research Center, Inc (PARC). Rights to these patents are available via
 * various mechanisms. As of January 2016 PARC has committed to FRAND licensing any
 * intellectual property used by its contributions to this software. You may
 * contact PARC at cipo@parc.com for more information or visit http://www.ccnx.org
 */
/**
 * @file parc_MyObject.h
 * @brief A simple example of how to create static, not allocataed, PARC Objects.
 *
 *
 * @author Glenn Scott, Palo Alto Research Center (PARC)
 * @copyright 2016, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC).  All rights reserved.
 */
#ifndef PARCLibrary_parc_MyObject
#define PARCLibrary_parc_MyObject
#include <stdbool.h>

#include <parc/algol/parc_JSON.h>
#include <parc/algol/parc_HashCode.h>

parcObject_Declare(PARCMyObject);

/**
 * The number of bytes sufficient to contain the MyObject data.
 *
 * This is dependant upon the definition of the underlying `struct MyObject`.
 * If that definition changes, it may be necessary to change this constant.
 */
#define PARCMyObjectSizeOf 24

/**
 * Increase the number of references to a `PARCMyObject` instance.
 *
 * Note that new `PARCMyObject` is not created,
 * only that the given `PARCMyObject` reference count is incremented.
 * Discard the reference by invoking `parcMyObject_Release`.
 *
 * @param [in] instance A pointer to a valid PARCMyObject instance.
 *
 * @return The same value as @p instance.
 *
 * Example:
 * @code
 * {
 *     PARCMyObject *a = parcMyObject_Create();
 *
 *     PARCMyObject *b = parcMyObject_Acquire();

 *     parcMyObject_Release(&a);
 *     parcMyObject_Release(&b);
 * }
 * @endcode
 */
PARCMyObject *parcMyObject_Acquire(const PARCMyObject *instance);

#ifdef PARCLibrary_DISABLE_VALIDATION
#  define parcMyObject_OptionalAssertValid(_instance_)
#else
#  define parcMyObject_OptionalAssertValid(_instance_) parcMyObject_AssertValid(_instance_)
#endif

/**
 * Assert that the given `PARCMyObject` instance is valid.
 *
 * @param [in] instance A pointer to a valid PARCMyObject instance.
 *
 * Example:
 * @code
 * {
 *     PARCMyObject *a = parcMyObject_Create();
 *
 *     parcMyObject_AssertValid(a);
 *
 *     printf("Instance is valid.\n");
 *
 *     parcMyObject_Release(&b);
 * }
 * @endcode
 */
void parcMyObject_AssertValid(const PARCMyObject *instance);

/**
 * Create an instance of PARCMyObject
 *
 * @return non-NULL A pointer to a valid PARCMyObject instance.
 * @return NULL An error occurred.
 *
 * Example:
 * @code
 * {
 *     PARCMyObject *a = parcMyObject_Create();
 *
 *     parcMyObject_Release(&a);
 * }
 * @endcode
 */
PARCMyObject *parcMyObject_Create(int x, double y, double z);

/**
 * Set a PARCMyObject instance to it's initial, created state.
 *
 * @return non-NULL A pointer to a valid PARCMyObject instance.
 * @return NULL An error occurred.
 */
PARCMyObject *parcMyObject_Init(PARCMyObject *instance, int x, double y, double z);

PARCMyObject *parcMyObject_Wrap(void *origin);

/**
 * Compares @p instance with @p other for order.
 *
 * Returns a negative integer, zero, or a positive integer as @p instance
 * is less than, equal to, or greater than @p other.
 *
 * @param [in] instance A pointer to a valid PARCMyObject instance.
 * @param [in] other A pointer to a valid PARCMyObject instance.
 *
 * @return <0 Instance is less than @p other.
 * @return 0 Instance a and instance b compare the same.
 * @return >0 Instance a is greater than instance b.
 *
 * Example:
 * @code
 * {
 *     PARCMyObject *a = parcMyObject_Create();
 *     PARCMyObject *b = parcMyObject_Create();
 *
 *     if (parcMyObject_Compare(a, b) == 0) {
 *         printf("Instances are equal.\n");
 *     }
 *
 *     parcMyObject_Release(&a);
 *     parcMyObject_Release(&b);
 * }
 * @endcode
 *
 * @see parcMyObject_Equals
 */
int parcMyObject_Compare(const PARCMyObject *instance, const PARCMyObject *other);

/**
 * Create an independent copy the given `PARCBuffer`
 *
 * A new buffer is created as a complete copy of the original.
 *
 * @param [in] original A pointer to a valid PARCMyObject instance.
 *
 * @return NULL Memory could not be allocated.
 * @return non-NULL A pointer to a new `PARCMyObject` instance.
 *
 * Example:
 * @code
 * {
 *     PARCMyObject *a = parcMyObject_Create();
 *
 *     PARCMyObject *copy = parcMyObject_Copy(&b);
 *
 *     parcMyObject_Release(&b);
 *     parcMyObject_Release(&copy);
 * }
 * @endcode
 */
PARCMyObject *parcMyObject_Copy(const PARCMyObject *original);

/**
 * Print a human readable representation of the given `PARCMyObject`.
 *
 * @param [in] instance A pointer to a valid PARCMyObject instance.
 * @param [in] indentation The indentation level to use for printing.
 *
 * Example:
 * @code
 * {
 *     PARCMyObject *a = parcMyObject_Create();
 *
 *     parcMyObject_Display(a, 0);
 *
 *     parcMyObject_Release(&a);
 * }
 * @endcode
 */
void parcMyObject_Display(const PARCMyObject *instance, int indentation);

/**
 * Determine if two `PARCMyObject` instances are equal.
 *
 * The following equivalence relations on non-null `PARCMyObject` instances are maintained: *
 *   * It is reflexive: for any non-null reference value x, `parcMyObject_Equals(x, x)` must return true.
 *
 *   * It is symmetric: for any non-null reference values x and y, `parcMyObject_Equals(x, y)` must return true if and only if
 *        `parcMyObject_Equals(y x)` returns true.
 *
 *   * It is transitive: for any non-null reference values x, y, and z, if
 *        `parcMyObject_Equals(x, y)` returns true and
 *        `parcMyObject_Equals(y, z)` returns true,
 *        then `parcMyObject_Equals(x, z)` must return true.
 *
 *   * It is consistent: for any non-null reference values x and y, multiple invocations of `parcMyObject_Equals(x, y)`
 *         consistently return true or consistently return false.
 *
 *   * For any non-null reference value x, `parcMyObject_Equals(x, NULL)` must return false.
 *
 * @param [in] x A pointer to a valid PARCMyObject instance.
 * @param [in] y A pointer to a valid PARCMyObject instance.
 *
 * @return true The instances x and y are equal.
 *
 * Example:
 * @code
 * {
 *     PARCMyObject *a = parcMyObject_Create();
 *     PARCMyObject *b = parcMyObject_Create();
 *
 *     if (parcMyObject_Equals(a, b)) {
 *         printf("Instances are equal.\n");
 *     }
 *
 *     parcMyObject_Release(&a);
 *     parcMyObject_Release(&b);
 * }
 * @endcode
 * @see parcMyObject_HashCode
 */
bool parcMyObject_Equals(const PARCMyObject *x, const PARCMyObject *y);

/**
 * Returns a hash code value for the given instance.
 *
 * The general contract of `HashCode` is:
 *
 * Whenever it is invoked on the same instance more than once during an execution of an application,
 * the `HashCode` function must consistently return the same value,
 * provided no information used in a corresponding comparisons on the instance is modified.
 *
 * This value need not remain consistent from one execution of an application to another execution of the same application.
 * If two instances are equal according to the {@link parcMyObject_Equals} method,
 * then calling the {@link parcMyObject_HashCode} method on each of the two instances must produce the same integer result.
 *
 * It is not required that if two instances are unequal according to the
 * {@link parcMyObject_Equals} function,
 * then calling the `parcMyObject_HashCode`
 * method on each of the two objects must produce distinct integer results.
 *
 * @param [in] instance A pointer to a valid PARCMyObject instance.
 *
 * @return The hashcode for the given instance.
 *
 * Example:
 * @code
 * {
 *     PARCMyObject *a = parcMyObject_Create();
 *
 *     PARCHashCode hashValue = parcMyObject_HashCode(buffer);
 *     parcMyObject_Release(&a);
 * }
 * @endcode
 */
PARCHashCode parcMyObject_HashCode(const PARCMyObject *instance);

/**
 * Determine if an instance of `PARCMyObject` is valid.
 *
 * Valid means the internal state of the type is consistent with its required current or future behaviour.
 * This may include the validation of internal instances of types.
 *
 * @param [in] instance A pointer to a valid PARCMyObject instance.
 *
 * @return true The instance is valid.
 * @return false The instance is not valid.
 *
 * Example:
 * @code
 * {
 *     PARCMyObject *a = parcMyObject_Create();
 *
 *     if (parcMyObject_IsValid(a)) {
 *         printf("Instance is valid.\n");
 *     }
 *
 *     parcMyObject_Release(&a);
 * }
 * @endcode
 *
 */
bool parcMyObject_IsValid(const PARCMyObject *instance);

/**
 * Release a previously acquired reference to the given `PARCMyObject` instance,
 * decrementing the reference count for the instance.
 *
 * The pointer to the instance is set to NULL as a side-effect of this function.
 *
 * If the invocation causes the last reference to the instance to be released,
 * the instance is deallocated and the instance's implementation will perform
 * additional cleanup and release other privately held references.
 *
 * @param [in,out] instancePtr A pointer to a pointer to the instance to release.
 *
 * Example:
 * @code
 * {
 *     PARCMyObject *a = parcMyObject_Create();
 *
 *     parcMyObject_Release(&a);
 * }
 * @endcode
 */
void parcMyObject_Release(PARCMyObject **instancePtr);

/**
 * Create a `PARCJSON` instance (representation) of the given object.
 *
 * @param [in] instance A pointer to a valid PARCMyObject instance.
 *
 * @return NULL Memory could not be allocated to contain the `PARCJSON` instance.
 * @return non-NULL An allocated C string that must be deallocated via parcMemory_Deallocate().
 *
 * Example:
 * @code
 * {
 *     PARCMyObject *a = parcMyObject_Create();
 *
 *     PARCJSON *json = parcMyObject_ToJSON(a);
 *
 *     printf("JSON representation: %s\n", parcJSON_ToString(json));
 *     parcJSON_Release(&json);
 *
 *     parcMyObject_Release(&a);
 * }
 * @endcode
 */
PARCJSON *parcMyObject_ToJSON(const PARCMyObject *instance);

/**
 * Produce a null-terminated string representation of the specified `PARCMyObject`.
 *
 * The result must be freed by the caller via {@link parcMemory_Deallocate}.
 *
 * @param [in] instance A pointer to a valid PARCMyObject instance.
 *
 * @return NULL Cannot allocate memory.
 * @return non-NULL A pointer to an allocated, null-terminated C string that must be deallocated via {@link parcMemory_Deallocate}.
 *
 * Example:
 * @code
 * {
 *     PARCMyObject *a = parcMyObject_Create();
 *
 *     char *string = parcMyObject_ToString(a);
 *
 *     parcMyObject_Release(&a);
 *
 *     parcMemory_Deallocate(&string);
 * }
 * @endcode
 *
 * @see parcMyObject_Display
 */
char *parcMyObject_ToString(const PARCMyObject *instance);

#endif
