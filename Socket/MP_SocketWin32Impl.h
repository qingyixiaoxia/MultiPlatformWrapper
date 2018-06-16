#ifndef MULTI_PLATFORM_SOCKET_WIN32_IMPL_H
#define MULTI_PLATFORM_SOCKET_WIN32_IMPL_H
#include "MP_Socket.h"
#include "MPCommon.h"
#if defined (WIN32)
#include <winsock2.h>
#include <ws2tcpip.h>
#endif

#if defined (WIN32)
namespace MultiPlatformWrapper
{
class MP_SocketWin32Impl
{
protected:
	int printLastError();
	signed int getLastError();
	signed int transErrorCode(int win32ErrorCode);

protected:
	bool win32setOpt(SOCKET socketH, SocketOptTypes optType, long optValue);
	bool win32select(SOCKET socketH, unsigned long maxWaitMS, bool isCheckRead, bool isCheckWrite);

private:
	bool win32setBlockRecv(SOCKET socketH);
	bool win32setNBlockRecv(SOCKET socketH);
	bool win32setBlockSend(SOCKET socketH);
	bool win32setNBlockSend(SOCKET socketH);
};

class MP_TCPSocketWin32Impl : public MP_TCPSocket, public MP_SocketWin32Impl
{
public:
	MP_TCPSocketWin32Impl();
	~MP_TCPSocketWin32Impl();
	
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
	MP_TCPSocketWin32Impl(SOCKET newSocket);

private:
	SOCKET m_socket;
	
};

class MP_UDPSocketWin32Impl : public MP_UDPSocket, public MP_SocketWin32Impl
{
public:
	MP_UDPSocketWin32Impl();
	~MP_UDPSocketWin32Impl();

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
	
private:
	SOCKET m_socket;
};
}
#endif
#endif
