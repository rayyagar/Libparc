/*
 * Copyright (c) 2016, Xerox Corporation (Xerox) and Palo Alto Research Center, Inc (PARC)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
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
#include <stdio.h>

#include <parc/algol/parc_Memory.h>
#include "parc_MyObject.h"

/*
 * Three kinds of static PARC Objects
 *
 * static or global objects defined within a module
 *
 * local objects defined within a function.
 *
 */

PARCMyObject *globalObject = parcObject_Instance(PARCMyObject, sizeof(void*), PARCMyObjectSizeOf);

void
aGlobalObject(void)
{
    int x = 1;
    int y = 2;
    double z = 3.14;
    
    parcObject_InitInstance(globalObject, PARCMyObject);
    parcMyObject_Init(globalObject, x, y, z);
    
    parcMyObject_Display(globalObject, 0);

    parcMyObject_Release(&globalObject);
}

static PARCMyObject *staticModuleObject = parcObject_Instance(PARCMyObject, sizeof(void*), PARCMyObjectSizeOf);

void
aStaticModuleObject(void)
{
    int x = 1;
    int y = 2;
    double z = 3.14;
    
    parcObject_InitInstance(staticModuleObject, PARCMyObject);
    parcMyObject_Init(staticModuleObject, x, y, z);
    
    parcMyObject_Display(staticModuleObject, 0);
    
    parcMyObject_Release(&staticModuleObject);
}

void
aLocalObject(void)
{
    int x = 1;
    int y = 2;
    double z = 3.14;
    
    PARCMyObject *localObject = parcObject_Instance(PARCMyObject, sizeof(void*), PARCMyObjectSizeOf);
    
    parcObject_InitInstance(localObject, PARCMyObject);
    parcMyObject_Init(localObject, x, y, z);
    
    parcMyObject_Display(localObject, 0);

    parcMyObject_Release(&localObject);
}

void
aWrappedObject(void)
{
    int x = 1;
    int y = 2;
    double z = 3.14;
    
    PARCMyObject *wrappedObject = parcMyObject_Wrap((char[parcObject_TotalSize(sizeof(void*), PARCMyObjectSizeOf)]) { 0 });
    parcMyObject_Init(wrappedObject, x, y, z);
    
    parcMyObject_Display(wrappedObject, 0);

    parcMyObject_Release(&wrappedObject);
}

int
main(int argc, const char *argv[argc])
{
    aGlobalObject();
    
    aStaticModuleObject();
    
    aLocalObject();
    
    aWrappedObject();
    
    return 0;
}
