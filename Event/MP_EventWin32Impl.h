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

#ifndef MULTI_PLATFORM_EVENT_WIN32_IMPL_H
#define MULTI_PLATFORM_EVENT_WIN32_IMPL_H
#include "MP_Event.h"
#include <windows.h>
#include "MPCommon.h"

#if defined (WIN32)
namespace MultiPlatformWrapper
{
class MP_EventWin32Impl : public MP_Event
{
public:
	MP_EventWin32Impl(const char *pName);
	~MP_EventWin32Impl();

public:
	bool wait(MP_Mutex &mutex);
	bool timewait(MP_Mutex &mutex, unsigned long MS);
	bool notifyOne();
	bool notifyAll();

private:
	
};

}
#endif
#endif
