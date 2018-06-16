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
#ifndef MULTI_PLATFORM_SOCKET_H
#define MULTI_PLATFORM_SOCKET_H
#include <string>
#include "MPCommon.h"

namespace MultiPlatformWrapper
{
typedef enum
{
    OPT_RECV_NON_BLOCKING = 1,
    OPT_RECV_BLOCKING,
    OPT_SEND_NON_BLOCKING,
    OPT_SEND_BLOCKING,

	OPT_DIRECT_CLOSE,
} SocketOptTypes;
#define OPT_VALUE_TRUE   1
#define OPT_VALUE_FALSE  0

typedef enum
{
    SEND_FLAG_NOTHING = 0x00,
} SendFlags;

typedef enum
{
    RECV_FLAG_NOTHING = 0x00,
    RECV_FLAG_BLOCK_WAIT = 0x01,
	RECV_FLAG_ONLY_CHECK = 0x02,
} RecvFlags;

/*---------- Socket Error Codes Begin ------------*/
#define MP_SOCKET_ERROR_PARAM      -1
#define MP_SOCKET_ERROR_NET_DOWN   -10
#define MP_SOCKET_ERROR_PEER_DOWN  -20
#define MP_SOCKET_ERROR_NO_DATA    -30
#define MP_SOCKET_ERROR_OTHER      -100
/*---------- Socket Error Codes End ------------*/

class MP_Socket
{
public:
	static bool initEnviroment();
	static bool terminateEnviroment();
};

class MP_TCPSocket
{
public:
	virtual ~MP_TCPSocket() {}
	virtual bool addOpt(SocketOptTypes optType, long optValue) = 0;
	virtual bool bind(IN const char* localIP, IN unsigned long localPORT) = 0;
	virtual bool connect(IN const char* remoteIP, IN unsigned long remotePORT) = 0;
	
    virtual bool select_r(unsigned long maxWaitMS) = 0;
	virtual bool select_w(unsigned long maxWaitMS) = 0;
	
	virtual bool listen() = 0;
	virtual MP_TCPSocket* accept() = 0;
	virtual MP_TCPSocket* accept(OUT char* pRemoteIP, OUT unsigned long &remotePort) = 0;

    virtual signed int send(IN const char* pBuffer, IN unsigned int hopeLength, IN SendFlags flags) = 0;
	virtual signed int recv(OUT char* pBuffer, IN unsigned int hopeLength, IN RecvFlags flags) = 0;
};

class MP_UDPSocket
{
public:
	virtual ~MP_UDPSocket() {}
	virtual bool addOpt(SocketOptTypes optType, long optValue) = 0;
	virtual bool bind(IN const char* localORremoteIP, IN unsigned long localORremotePORT) = 0;
	
    virtual bool select_r(unsigned long maxWaitMS) = 0;
	virtual bool select_w(unsigned long maxWaitMS) = 0;
	
    virtual signed int sendto(IN const char* pBuffer, IN unsigned int hopeLength, IN SendFlags flags) = 0;
    virtual signed int sendto(IN const char* remoteIP, IN unsigned long remotePORT,
		                     IN const char* pBuffer, IN unsigned int hopeLength, IN SendFlags flags) = 0;
    virtual signed int recvfrom(OUT char* pBuffer, IN unsigned int hopeLength, IN RecvFlags flags) = 0;
    virtual signed int recvfrom(OUT char* remoteIP, OUT unsigned long &remotePORT,
		                        OUT char* pBuffer, IN unsigned int hopeLength, IN RecvFlags flags) = 0;

};

}
#endif
