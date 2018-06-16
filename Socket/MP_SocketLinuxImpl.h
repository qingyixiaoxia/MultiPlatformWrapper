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
