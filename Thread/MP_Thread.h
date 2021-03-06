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

#ifndef MULTI_PLATFORM_THREAD_H
#define MULTI_PLATFORM_THREAD_H
#include "MPCommon.h"
#include <map>

namespace MultiPlatformWrapper
{

typedef int (*MPThreadLoopFunc)(void *pUser1, void *pUser2);
class MPThreadLoopBase
{
public:
	virtual int onMPThreadLoop(void *pUser1, void *pUser2) = 0;
};

typedef enum
{
    // TODO
    // TODO
    // TODO
} ThreadOptTypes;

class MP_Thread
{
public:
	MP_Thread()
	{
	    m_pListener = NULL;
		m_pCallback = NULL;
	}
	virtual ~MP_Thread() {}
	void addOpt(ThreadOptTypes optType, long optValue);
	virtual bool start(MPThreadLoopBase *pListener, void *pUser1, void *pUser2) = 0;
	virtual bool start(MPThreadLoopFunc pCallback, void *pUser1, void *pUser2) = 0;
	virtual bool suspend() = 0;
	virtual bool resume() = 0;
	virtual int stop() = 0;
	static void sleep(unsigned long MS);

protected:
	MPThreadLoopBase* m_pListener;
	MPThreadLoopFunc m_pCallback;
	std::map<ThreadOptTypes, long> m_options;
};
}
#endif
