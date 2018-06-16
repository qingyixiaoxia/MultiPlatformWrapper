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
#include "MP_SocketLinuxImpl.h"

#if defined (LINUX)
namespace MultiPlatformWrapper
{
bool MP_TCPSocketLinuxImpl::addOpt(SocketOptTypes optType, long optValue){
    return false;
}

bool MP_TCPSocketLinuxImpl::bind(IN const char* localIP, IN unsigned long localPORT)
{
    return true;
}

bool MP_TCPSocketLinuxImpl::connect(IN const char* remoteIP, IN unsigned long remotePORT)
{
    return true;
}

bool MP_TCPSocketLinuxImpl::select_r(unsigned long maxWaitMS)
{
    return true;
}

bool MP_TCPSocketLinuxImpl::select_w(unsigned long maxWaitMS)
{
    return true;
}

bool MP_TCPSocketLinuxImpl::listen()
{
    return true;
}

MP_TCPSocket* MP_TCPSocketLinuxImpl::accept()
{
    return NULL;
}

MP_TCPSocket* MP_TCPSocketLinuxImpl::accept(OUT char* pRemoteIP, OUT unsigned long &remotePort)
{
    return NULL;
}

signed int MP_TCPSocketLinuxImpl::send(IN const char* pBuffer, IN unsigned int hopeLength, IN SendFlags flags)
{
    return 0;
}

signed int MP_TCPSocketLinuxImpl::recv(OUT char* pBuffer, IN unsigned int hopeLength, IN RecvFlags flags)
{
    return 0;
}

bool MP_UDPSocketLinuxImpl::addOpt(SocketOptTypes optType, long optValue)
{
    return false;
}

bool MP_UDPSocketLinuxImpl::bind(IN const char* localORremoteIP, IN unsigned long localORremotePORT)
{
    return true;
}

bool MP_UDPSocketLinuxImpl::select_r(unsigned long maxWaitMS)
{
    return true;
}

bool MP_UDPSocketLinuxImpl::select_w(unsigned long maxWaitMS)
{
    return true;
}

signed int MP_UDPSocketLinuxImpl::sendto(IN const char* pBuffer, IN unsigned int hopeLength, IN SendFlags flags)
{
    return 0;
}

signed int MP_UDPSocketLinuxImpl::sendto(IN const char* remoteIP, IN unsigned long remotePORT,
						  IN const char* pBuffer, IN unsigned int hopeLength, IN SendFlags flags)
{
    return 0;
}

signed int MP_UDPSocketLinuxImpl::recvfrom(OUT char* pBuffer, IN unsigned int hopeLength, IN RecvFlags flags)
{
    return 0;
}

signed int MP_UDPSocketLinuxImpl::recvfrom(OUT char* remoteIP, OUT unsigned long &remotePORT,
							  OUT char* pBuffer, IN unsigned int hopeLength, IN RecvFlags flags)
{
    return 0;
}
}
#endif
