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
#ifndef MULTI_PLATFORM_SOCKET_LINUX_IMPL_H
#define MULTI_PLATFORM_SOCKET_LINUX_IMPL_H
#include "MP_Socket.h"
#include "MPCommon.h"

#if defined (LINUX)
namespace MultiPlatformWrapper
{
class MP_TCPSocketLinuxImpl : public MP_TCPSocket
{
public:
	MP_TCPSocketLinuxImpl() {}
	~MP_TCPSocketLinuxImpl() {}

public:
	bool addOpt(SocketOptTypes optType, long optValue);
	bool bind(IN const char* localIP, IN unsigned long localPORT);
	bool connect(IN const char* remoteIP, IN unsigned long remotePORT);
	
    bool select_r(unsigned long maxWaitMS);
	bool select_w(unsigned long maxWaitMS);

	bool listen();
	MP_TCPSocket* accept();
	MP_TCPSocket* accept(OUT char* pRemoteIP, OUT unsigned long &remotePort);

	signed int send(IN const char* pBuffer, IN unsigned int hopeLength, IN SendFlags flags);
	signed int recv(OUT char* pBuffer, IN unsigned int hopeLength, IN RecvFlags flags);

private:
	
};

class MP_UDPSocketLinuxImpl : public MP_UDPSocket
{
public:
	MP_UDPSocketLinuxImpl() {}
	~MP_UDPSocketLinuxImpl() {}

public:
	bool addOpt(SocketOptTypes optType, long optValue);
	bool bind(IN const char* localORremoteIP, IN unsigned long localORremotePORT);
	
    bool select_r(unsigned long maxWaitMS);
	bool select_w(unsigned long maxWaitMS);
	
    signed int sendto(IN const char* pBuffer, IN unsigned int hopeLength, IN SendFlags flags);
    signed int sendto(IN const char* remoteIP, IN unsigned long remotePORT,
					 IN const char* pBuffer, IN unsigned int hopeLength, IN SendFlags flags);
    signed int recvfrom(OUT char* pBuffer, IN unsigned int hopeLength, IN RecvFlags flags);
    signed int recvfrom(OUT char* remoteIP, OUT unsigned long &remotePORT,
					  OUT char* pBuffer, IN unsigned int hopeLength, IN RecvFlags flags);

};
}
#endif
#endif
