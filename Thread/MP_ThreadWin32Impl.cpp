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

#include "MP_ThreadWin32Impl.h"

#if defined (WIN32)
namespace MultiPlatformWrapper
{
MP_ThreadWin32Impl::MP_ThreadWin32Impl() : MP_Thread()
{
    m_threadHandle = NULL;
    m_threadID = 0;
	m_pUser1 = NULL;
	m_pUser2 = NULL;
}

MP_ThreadWin32Impl::~MP_ThreadWin32Impl()
{
}

bool MP_ThreadWin32Impl::start(MPThreadLoopBase *pListener, void *pUser1, void *pUser2)
{
    return startThread(pListener, NULL, pUser1, pUser2);
}

bool MP_ThreadWin32Impl::start(MPThreadLoopFunc pCallback, void *pUser1, void *pUser2)
{
    return startThread(NULL, pCallback, pUser1, pUser2);
}

bool MP_ThreadWin32Impl::suspend()
{
    return false;
}

bool MP_ThreadWin32Impl::resume()
{
    return false;
}

int MP_ThreadWin32Impl::stop()
{
    // Wait for stop 
    ::WaitForSingleObject(m_threadHandle, 0);

	// Terminate thread
	DWORD exitCode = 0;
	if (!::TerminateThread(m_threadHandle, exitCode))
	{
	    return 0;
	}

    return exitCode;
}

bool MP_ThreadWin32Impl::startThread(MPThreadLoopBase *pListener, MPThreadLoopFunc pCallback, void *pUser1, void *pUser2)
{
    if (pListener == NULL && pCallback == NULL)
    {
        return false;
    }
	
    // Save paramenter 
    m_pUser1 = pUser1;
	m_pUser2 = pUser2;
	m_pListener = pListener;
	m_pCallback = pCallback;

	// Create and start the thread 
    LPSECURITY_ATTRIBUTES  threadOpt = NULL;
    SIZE_T  stackSize = 0;
    LPTHREAD_START_ROUTINE loopFunc = win_thread_loop;
    LPVOID  userParam  = this;
    DWORD  flags = 0;
    m_threadHandle = ::CreateThread(threadOpt, stackSize, loopFunc, userParam, flags, &m_threadID);
	if (m_threadHandle == NULL)
	{
	    return false;
	}
	
    return true;
}

DWORD WINAPI MP_ThreadWin32Impl::win_thread_loop(LPVOID pUser)
{
    MP_ThreadWin32Impl* pThis = (MP_ThreadWin32Impl*)pUser;

	if (pThis->m_pCallback != NULL)
	{
	    return pThis->m_pCallback(pThis->m_pUser1, pThis->m_pUser2);
	}

	if (pThis->m_pListener != NULL)
	{
	    return pThis->m_pListener->onMPThreadLoop(pThis->m_pUser1, pThis->m_pUser2);
	}

	return 0;
}
}
#endif
