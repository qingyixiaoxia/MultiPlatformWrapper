/* Copyright Wenjing Li. and other Node contributors. All rights reserved.
* Author: Wenjing Li, GitHub Address: http://www.github.com/qingyixiaoxia
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to
* deal in the Software without restriction, including without limitation the
* rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
* sell copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
* IN THE SOFTWARE.
*/

#include "MP_MutexFactory.h"
#include "MP_MutexLinuxImpl.h"
#include "MP_MutexWin32Impl.h"

namespace MultiPlatformWrapper
{
MP_Mutex* MP_MutexFactory::createMutex(IN MPBaseLibraryType type, IN const char* pName)
{
    switch (type)
    {
        #if defined (WIN32)
        case MP_BASE_LIBRARY_WIN32:
			return new MP_MutexWin32Impl(pName);
			break;
		#endif

        #if defined (LINUX)
		case MP_BASE_LIBRARY_LINUX:
			return new MP_MutexLinuxImpl(pName);
			break;
		#endif

		default:
			return NULL;
    }
}
}
