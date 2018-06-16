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
