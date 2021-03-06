/*
 * Copyright (c) 2015, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC)
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
 * @file parc_ObjectTesting.h
 * @brief Support for LongBow runtime and unit testing of PARCObject implementations.
 *
 * @author Glenn Scott, Palo Alto Research Center (Xerox PARC)
 * @copyright 2015, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC).  All rights reserved.
 */
#ifndef PARC_Library_parc_ObjectTest_h
#define PARC_Library_parc_ObjectTest_h

#include <stdarg.h>
#include <stdbool.h>

#include <parc/algol/parc_Object.h>
#include <parc/algol/parc_HashCode.h>

/**
 * Test if a PARCObject subclass behaves well as a PARCObject when passed to the various PARCObject functions.
 *
 * @param [in] inst1 A pointer to an instance that will be used as the base comparison for remaining parameters.
 * @param [in] inst2 A pointer to an instance that is known to be equal to @p inst1, but is not @p inst1.
 * @param [in] inst3 A pointer to an instance that is known to be equal to @p inst1 & @p inst2, but is not @p inst1 or @p inst2.
 * @param [in] lesser A pointer to and instance that are known to be lesser than @p inst1.
 * @param [in] greater A pointer to and instance that are known to be greater than @p inst1.
 *
 * @see parcObjectTesting_AssertEqualsFunction
 * @see parcObjectTesting_AssertCompareTo
 * @see parcObjectTesting_AssertAcquire
 * @see parcObjectTesting_AssertHashCode
 */

void parcObjectTesting_AssertObjectConformance(const PARCObject *inst1,
                                               const PARCObject *inst2,
                                               const PARCObject *inst3,
                                               const PARCObject *lesser,
                                               const PARCObject *greater);

/**
 * Ensure that a function implements the Equals contract.
 *
 *   The equality function must implement the following equivalence relations on non-null instances:
 *
 *   * It is reflexive: for any non-null reference value x, equals(x, x) must return true.
 *
 *   * It is symmetric: for any non-null reference values x and y, equals(x, y) must return true if and only if
 *        equals(y x) returns true.
 *
 *   * It is transitive: for any non-null reference values x, y, and z, if
 *        equals(x, y) returns true and
 *        equals(y, z) returns true,
 *        then  equals(x, z) must return true.
 *
 *   * It is consistent: for any non-null reference values x and y, multiple invocations of equals(x, y)
 *         consistently return true or consistently return false.
 *
 *   * For any non-null reference value x, equals(x, NULL)) must return false.
 *
 * @param [in] _function_ A pointer to a function that will be called to determine if it conforms to the Equals contract.
 * @param [in] _x_ A pointer to a value that will be used as the base comparison for remaining parameters.
 * @param [in] _y_ A pointer to a value that is known to be equal to @p x, but is not @p x.
 * @param [in] _z_ A pointer to a value that is known to be equal to @p x and to @p y, but is neither @p x nor @p y.
 * @param [in] ... A list of pointers to values that are known to be not equal to @p x, @p y, or @p z.
 * @see parcObjectTesting_AssertEqualsImpl
 */
#define parcObjectTesting_AssertEqualsFunction(_function_, _x_, _y_, _z_, ...) \
    parcObjectTesting_AssertEqualsFunctionImpl((bool (*)(const void *, const void *))_function_, _x_, _y_, _z_, __VA_ARGS__, NULL)

/**
 * Compares instance a known set of other instances for order.
 *
 * The comparison function that this evaluates <i>sgn(a - b)</i> required to return a negative integer,
 * zero, or a positive integer as <code>a</code> is less than,
 * equal to, or greater than <code>b</code>.
 *
 * The function must ensure that:
 *   <ul>
 *     <li>sgn(compareTo(a, b)) == -sgn(b, a) for all values of a and b.</li>
 *     <li>the relation is transitive: (compareTo(x, y)>0 && compareTo(y, z)>0) implies compareTo(x, z)>0.</li>
 *     <li>compareTo(x, y)== 0 implies that sgn(compareTo(x, z)) == sgn(compareTo(y, z)), for all values of z.</li>
 *   </ul>
 *
 *   This also stipulates that
 *   <code>compareTo(NULL, NULL)) == 0</code>,
 *   <code>compareTo(not-NULL, NULL)) > 0</code>,
 *   <code>compareTo(NULL, not-NULL)) < 0</code>.
 *
 * It is strongly recommended, but not strictly required that relation(compareTo(x, y)==0) == equals(x, y)) is true.
 * Any module that implements the compareTo function and violates this condition
 * should clearly indicate this fact.
 * For example, "Note: this implementation has a natural ordering that is inconsistent with equals."
 *
 * @param [in] compareTo A pointer to a function implementing the CompareTo function signature.
 * @param [in] exemplar The pivotal value under test.
 * @param [in] equivalent A NULL terminated array of values that are all equivalent to <code>value</code>.
 * @param [in] lesser A NULL terminated array of values that are all less than <code>value</code>.
 * @param [in] greater A NULL terminated array of values that are all greater than <code>value</code>.
 * @see parcObjectTesting_AssertCompareTo
 */
#define parcObjectTesting_AssertCompareTo(function, value, equality, lesser, greater) \
    parcObjectTesting_AssertCompareToImpl((int (*)(const void *, const void *))function, (void *) value, (void *) equality, (void *) lesser, (void *) greater)

#define parcObjectTesting_AssertAcquireReleaseContract(_function_, _instance_) \
    parcObjectTesting_AssertAcquireReleaseContractImpl((void *(*)(const PARCObject *))_function_, _instance_)
/**
 * Assert the acquire/release contract given the Acquire function of a PARCObject implementation.
 *
 * Paragraphs Of Explanation
 *
 * @param [in] acquireFunction A pointer to the acquireFunction to invoke.
 * @param [in] instance A pointer to a PARCObject implementation that will be used to acquire and release references.
 */
void parcObjectTesting_AssertAcquireReleaseContractImpl(void *(acquireFunction) (const PARCObject *),
                                                        const PARCObject *instance);


#define parcObjectTesting_AssertAcquire(_instance_) \
    parcObjectTesting_AssertAcquireReleaseImpl((const PARCObject *) _instance_)

/**
 * Assert that the given PARCObject's Acquire/Release contract is correct.
 *
 * @param [in] instance A pointer to a PARCObject instance.
 */
void parcObjectTesting_AssertAcquireReleaseImpl(const PARCObject *instance);

/**
 * Ensure that a function implements the Equals contract.
 *
 *   The equality function must implement the following equivalence relations on non-null instances:
 *
 *   * It is reflexive: for any non-null reference value x, equals(x, x) must return true.
 *
 *   * It is symmetric: for any non-null reference values x and y, equals(x, y) must return true if and only if
 *        equals(y x) returns true.
 *
 *   * It is transitive: for any non-null reference values x, y, and z, if
 *        equals(x, y) returns true and
 *        equals(y, z) returns true,
 *        then  equals(x, z) must return true.
 *
 *   * It is consistent: for any non-null reference values x and y, multiple invocations of equals(x, y)
 *         consistently return true or consistently return false.
 *
 *   * For any non-null reference value x, equals(x, NULL)) must return false.
 *
 * @param [in] equalsFunction A pointer to a function that will be called to determine if it conforms to the Equals contract.
 * @param [in] x A pointer to a value that will be used as the base comparison for remaining parameters.
 * @param [in] y A pointer to a value that is known to be equal to @p x, but is not @p x.
 * @param [in] z A pointer to a value that is known to be equal to @p x and to @p y, but is neither @p x nor @p y.
 * @param [in] ... A NULL terminated variable number of parameters consisting of pointers to values that are known to be not equal to @p x, @p y, or @p z.
 * @see parcObjectTesting_AssertEquals
 */
void parcObjectTesting_AssertEqualsFunctionImpl(bool (*equalsFunction)(const void *a, const void *b), const void *x, const void *y, const void *z, ...);

/**
 * Ensure that a PARCObject implements the Equals contract.
 *
 *   The PARCObject's `Equals()` function must implement the following equivalence relations on non-null instances:
 *
 *   * It is reflexive: for any non-null reference value x, equals(x, x) must return true.
 *
 *   * It is symmetric: for any non-null reference values x and y, equals(x, y) must return true if and only if
 *        equals(y x) returns true.
 *
 *   * It is transitive: for any non-null reference values x, y, and z, if
 *        equals(x, y) returns true and
 *        equals(y, z) returns true,
 *        then  equals(x, z) must return true.
 *
 *   * It is consistent: for any non-null reference values x and y, multiple invocations of equals(x, y)
 *         consistently return true or consistently return false.
 *
 *   * For any non-null reference value x, equals(x, NULL)) must return false.
 *
 * @param [in] object A pointer to a valid PARCObject instance.
 * @param [in] y A pointer to a value that is known to be equal to @p object, but is not the same as @p object.
 * @param [in] z A pointer to a value that is known to be equal to @p object and to @p y, but is neither the same as @p object nor @p y.
 * @param [in] ... A NULL terminated variable number of parameters consisting of pointers to values that are known to be not equal to @p object, @p y, or @p z.
 */
void parcObjectTesting_AssertEquals(const PARCObject *object, const void *y, const void *z, ...);

/**
 * Compares instance <code>a</code> with instance <code>b</code> for order.
 *
 * The comparison function that this evaluates <i>sgn(a - b)</i> required to return a negative integer,
 * zero, or a positive integer as <code>a</code> is less than,
 * equal to, or greater than <code>b</code>.
 *
 * The function must ensure that:
 *   <ul>
 *     <li>sgn(compareTo(a, b)) == -sgn(b, a) for all values of a and b.</li>
 *     <li>the relation is transitive: (compareTo(x, y)>0 && compareTo(y, z)>0) implies compareTo(x, z)>0.</li>
 *     <li>compareTo(x, y)== 0 implies that sgn(compareTo(x, z)) == sgn(compareTo(y, z)), for all values of z.</li>
 *   </ul>
 *
 *   This also stipulates that
 *   <code>compareTo(NULL, NULL)) == 0</code>,
 *   <code>compareTo(not-NULL, NULL)) > 0</code>,
 *   <code>compareTo(NULL, not-NULL)) < 0</code>.
 *
 * It is strongly recommended, but not strictly required that relation(compareTo(x, y)==0) == equals(x, y)) is true.
 * Any module that implements the compareTo function and violates this condition
 * should clearly indicate this fact.
 * For example, "Note: this implementation has a natural ordering that is inconsistent with equals."
 *
 * @param [in] compareTo A pointer to a function implementing the CompareTo function signature.
 * @param [in] exemplar The pivotal value under test.
 * @param [in] equivalent A NULL terminated array of values that are all equivalent to <code>value</code>.
 * @param [in] lesser A NULL terminated array of values that are all less than <code>value</code>.
 * @param [in] greater A NULL terminated array of values that are all greater than <code>value</code>.
 * @see parcObjectTesting_AssertCompareTo
 */
bool parcObjectTesting_AssertCompareToImpl(int (*compareTo)(const void *a, const void *b),
                                           const void *exemplar,
                                           const void **equivalent,
                                           const void **lesser,
                                           const void **greater);

/**
 * Assert the HashCode contract on a PARCObject.
 *
 * @param [in] x A pointer to a valid PARCObject.
 * @param [in] y A pointer to a valid PARCObject, that must be equal to @p x, but not the same.
 *
 * Example:
 * @code
 * {
 *     <#example#>
 * }
 * @endcode
 */
void parcObjectTesting_AssertHashCode(const PARCObject *x, const void *y);

/**
 * Assert the HashCode function contract.
 *
 * @param [in] hashCode A pointer to a function implementing the hash code function.
 */
void parcObjectTesting_AssertHashCodeImpl(PARCHashCode (*hashCode)(const void *a), void *a);
#endif
