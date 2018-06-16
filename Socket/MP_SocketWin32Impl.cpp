#include "MP_SocketWin32Impl.h"

#if defined (WIN32)
namespace MultiPlatformWrapper
{
static int transSentFlags(SendFlags win32SentFlag)
{
    return 0;
}

static int transRecvFlags(RecvFlags win32RecvFlag)
{
    int flag = 0;

	if (win32RecvFlag & RECV_FLAG_BLOCK_WAIT)
	{
	   flag |= MSG_PEEK;
	}
	if (win32RecvFlag & RECV_FLAG_ONLY_CHECK)
	{
	    flag |= MSG_WAITALL;
	}

    return flag;
}

MP_TCPSocketWin32Impl::MP_TCPSocketWin32Impl()
{
    m_socket = ::socket(AF_INET, SOCK_STREAM, 0);
}

MP_TCPSocketWin32Impl::MP_TCPSocketWin32Impl(SOCKET socket)
{
    m_socket = socket;
}

MP_TCPSocketWin32Impl::~MP_TCPSocketWin32Impl()
{
    if (m_socket == INVALID_SOCKET)
    {
        return;
    }

	//::shutdown(m_socket, SD_SEND);  // It is useless in signel process situation
    ::closesocket(m_socket);
}

bool MP_TCPSocketWin32Impl::addOpt(SocketOptTypes optType, long optValue)
{
    bool result = true;
    switch (optType)
    {
        case OPT_DIRECT_CLOSE:
		{
			if (optValue)
			{
				struct linger so_linger;
				so_linger.l_onoff = TRUE;
				so_linger.l_linger = 0;
				int iResult = ::setsockopt(m_socket, SOL_SOCKET, SO_LINGER, (char*)&so_linger, sizeof(so_linger));
				if (iResult == SOCKET_ERROR) 
				{
					result = false;
				} 
			}
			else
			{
                #if 0
				BOOL bOptVal = FALSE;
				int bOptLen = sizeof(BOOL);
				int iResult = 0;
				
				iResult = ::setsockopt(m_socket, SOL_SOCKET, SO_DONTLINGER, (char *) &bOptVal, bOptLen);
				if (iResult == SOCKET_ERROR) 
				{
					result = false;
				} 
                #endif
			}
        }
		break;

		default:
			break;
    }
    return result;
}

bool MP_TCPSocketWin32Impl::bind(IN const char* localIP, IN unsigned long localPORT)
{
    if (m_socket == INVALID_SOCKET)
    {
        return false;
    }

	if (localIP == NULL)
	{
	    return false;
	}
	
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//::inet_addr(localIP);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = ::htons(localPORT);
    int result = ::bind(m_socket, (SOCKADDR*)&addrSrv, sizeof(addrSrv));
    if (result == SOCKET_ERROR) 
	{
	    printLastError();
        return false;
    }

    return true;
}

bool MP_TCPSocketWin32Impl::connect(IN const char* remoteIP, IN unsigned long remotePORT)
{
    if (m_socket == INVALID_SOCKET)
    {
        return false;
    }

	if (remoteIP == NULL)
	{
	    return false;
	}

	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = ::inet_addr(remoteIP);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = ::htons(remotePORT);

	int result = ::connect(m_socket, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
	if (result == SOCKET_ERROR)
	{
	    printLastError();
		return false;
	}

    return true;
}

bool MP_TCPSocketWin32Impl::select_r(unsigned long maxWaitMS)
{
    return win32select(m_socket, maxWaitMS, true, false);
}

bool MP_TCPSocketWin32Impl::select_w(unsigned long maxWaitMS)
{
    return win32select(m_socket, maxWaitMS, false, true);
}

bool MP_TCPSocketWin32Impl::listen()
{
    if (m_socket == INVALID_SOCKET)
    {
        return false;
    }

	int result = ::listen(m_socket, SOMAXCONN);
	if (result == SOCKET_ERROR)
	{
	    printLastError();
		return false;
	}

    return true;
}

MP_TCPSocket* MP_TCPSocketWin32Impl::accept()
{
    if (m_socket == INVALID_SOCKET)
    {
        return false;
    }

    SOCKET newSock = ::accept(m_socket, NULL, NULL);
	if (newSock == NULL)
	{
	    printLastError();
	    return NULL;
	}
	
    return new MP_TCPSocketWin32Impl(newSock);
}

MP_TCPSocket* MP_TCPSocketWin32Impl::accept(OUT char* pRemoteIP, OUT unsigned long &remotePort)
{
    if (m_socket == INVALID_SOCKET)
    {
        return false;
    }
	if (pRemoteIP == NULL)
	{
	    /* It is OK */
	}

	SOCKADDR_IN clientAddr;
	int addrLen = sizeof(SOCKADDR_IN);

    SOCKET newSock = ::accept(m_socket, (sockaddr*)&clientAddr, &addrLen);
	if (newSock == NULL)
	{
	    printLastError();
	    return NULL;
	}

	sockaddr_in* pSinAddr = (sockaddr_in*)&clientAddr;
	const char *pIP = inet_ntoa(pSinAddr->sin_addr);
	if (pIP != NULL && pRemoteIP != NULL)
	{
	    memcpy(pRemoteIP, pIP, strlen(pIP));
	}
	remotePort = pSinAddr->sin_port;

    return new MP_TCPSocketWin32Impl(newSock);
}

signed int MP_TCPSocketWin32Impl::send(IN const char* pBuffer, IN unsigned int hopeLength, IN SendFlags flags)
{
    if (m_socket == INVALID_SOCKET)
    {
        return MP_SOCKET_ERROR_PARAM;
    }
	if (pBuffer == NULL)
	{
	    return MP_SOCKET_ERROR_PARAM;
	}

    int sentFlag = transSentFlags(flags);
	int sentLen = ::send(m_socket, pBuffer, hopeLength, sentFlag);
	if (sentLen == 0 || sentLen == SOCKET_ERROR)
	{
		return getLastError();
	}

    return sentLen;
}

signed int MP_TCPSocketWin32Impl::recv(OUT char* pBuffer, IN unsigned int hopeLength, IN RecvFlags flags)
{
    if (m_socket == INVALID_SOCKET)
    {
        return MP_SOCKET_ERROR_PARAM;
    }
	if (pBuffer == NULL)
	{
	    return MP_SOCKET_ERROR_PARAM;
	}

    int recvFlag = transRecvFlags(flags);
	int recvLen = ::recv(m_socket, pBuffer, hopeLength, recvFlag);
    if (recvLen == 0 || recvLen == SOCKET_ERROR)  /* There is NOT any data now, or other errors */
    {
        return getLastError();
    }
	else
	{
	    return recvLen;
	}
}

MP_UDPSocketWin32Impl::MP_UDPSocketWin32Impl()
{
    m_socket = ::socket(AF_INET, SOCK_DGRAM, 0);
}

MP_UDPSocketWin32Impl::~MP_UDPSocketWin32Impl()
{
    if (m_socket == INVALID_SOCKET)
    {
        return;
    }

	//::shutdown(m_socket, SD_SEND);  // It is useless in signel process situation
    ::closesocket(m_socket);
}

bool MP_UDPSocketWin32Impl::addOpt(SocketOptTypes optType, long optValue)
{
    if (m_socket == INVALID_SOCKET)
    {
        return false;
    }

    return false;
}

bool MP_UDPSocketWin32Impl::bind(IN const char* localORremoteIP, IN unsigned long localORremotePORT)
{
    if (m_socket == INVALID_SOCKET)
    {
        return false;
    }
	if (localORremoteIP == NULL)
	{
	    return false;
	}

	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = ::inet_addr(localORremoteIP);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = ::htons(localORremotePORT);
    int result = ::bind(m_socket, (SOCKADDR*)&addrSrv, sizeof(addrSrv));
    if (result == SOCKET_ERROR) 
	{
	    printLastError();
        return false;
    }

    return true;
}

bool MP_UDPSocketWin32Impl::select_r(unsigned long maxWaitMS)
{
    return win32select(m_socket, maxWaitMS, true, false);
}

bool MP_UDPSocketWin32Impl::select_w(unsigned long maxWaitMS)
{
    return win32select(m_socket, maxWaitMS, false, true);
}

signed int MP_UDPSocketWin32Impl::sendto(IN const char* pBuffer, IN unsigned int hopeLength, IN SendFlags flags)
{
    if (m_socket == INVALID_SOCKET)
    {
        return MP_SOCKET_ERROR_PARAM;
    }
	if (pBuffer == NULL)
	{
	    return MP_SOCKET_ERROR_PARAM;
	}

    int sentFlag = transSentFlags(flags);
	int sentLen = ::send(m_socket, pBuffer, hopeLength, sentFlag);
	if (sentLen == 0 || sentLen == SOCKET_ERROR)
	{
	    return getLastError();
	}

    return sentLen;
}

signed int MP_UDPSocketWin32Impl::sendto(IN const char* remoteIP, IN unsigned long remotePORT,
						  IN const char* pBuffer, IN unsigned int hopeLength, IN SendFlags flags)
{
    if (m_socket == INVALID_SOCKET)
    {
        return MP_SOCKET_ERROR_PARAM;
    }
	if (remoteIP == NULL || pBuffer == NULL)
	{
	    return MP_SOCKET_ERROR_PARAM;
	}

	sockaddr_in remoteAddr;
    remoteAddr.sin_family = AF_INET;
    remoteAddr.sin_port = htons(remotePORT);
    remoteAddr.sin_addr.s_addr = inet_addr(remoteIP);

    int sentFlag = transSentFlags(flags);
    int sentLen = ::sendto(m_socket, pBuffer, hopeLength, sentFlag, (SOCKADDR*)&remoteAddr, sizeof(remoteAddr));
	if (sentLen == 0 || sentLen == SOCKET_ERROR)
	{
	    return getLastError();
	}

    return sentLen;
}

signed int MP_UDPSocketWin32Impl::recvfrom(OUT char* pBuffer, IN unsigned int hopeLength, IN RecvFlags flags)
{
    unsigned long portInfo = 0;
    return recvfrom(NULL, portInfo, pBuffer, hopeLength, flags);
}

signed int MP_UDPSocketWin32Impl::recvfrom(OUT char* remoteIP, OUT unsigned long &remotePORT,
							  OUT char* pBuffer, IN unsigned int hopeLength, IN RecvFlags flags)
{
    if (m_socket == INVALID_SOCKET)
    {
        return MP_SOCKET_ERROR_PARAM;
    }
	if (remoteIP == NULL || pBuffer == NULL)
	{
	    return MP_SOCKET_ERROR_PARAM;
	}

    sockaddr_in SenderAddr;
    int SenderAddrSize = sizeof (SenderAddr);

	// Receive 
    int recvFlag = transRecvFlags(flags);
	int recvLen = ::recvfrom(m_socket, pBuffer, hopeLength, recvFlag, (SOCKADDR *)&SenderAddr, &SenderAddrSize);
	sockaddr_in* pSinAddr = (sockaddr_in*)&SenderAddr;
	const char *pIP = inet_ntoa(pSinAddr->sin_addr);
	if (pIP != NULL && remoteIP != NULL)
	{
	    memcpy(remoteIP, pIP, strlen(pIP));
	}
	remotePORT = pSinAddr->sin_port;

    // Switch the result 
    if (recvLen == 0 || recvLen == SOCKET_ERROR)  /* There is NOT any data now, or other errors */
    {
        return getLastError();
    }
	else
	{
	    return recvLen;
	}
}

bool MP_SocketWin32Impl::win32setOpt(SOCKET socketH, SocketOptTypes optType, long optValue)
{
    switch (optType)
    {
        case OPT_RECV_NON_BLOCKING:
        {
			return win32setNBlockRecv(socketH);
        }
        break;
        
        case OPT_RECV_BLOCKING:
        {
			return win32setBlockRecv(socketH);
        }
        break;
		
        case OPT_SEND_NON_BLOCKING:
        {
			return win32setNBlockSend(socketH);
        }
        break;
		
        case OPT_SEND_BLOCKING:
        {
			return win32setBlockSend(socketH);
        }
        break;
    }
}

bool MP_SocketWin32Impl::win32select(SOCKET socketH, unsigned long maxWaitMS, bool isCheckRead, bool isCheckWrite)
{
    if (socketH == INVALID_SOCKET)
    {
        return false;
    }

    fd_set fd_read;
	FD_ZERO(&fd_read); 
	FD_SET(socketH, &fd_read); 

    fd_set fd_write;
	FD_ZERO(&fd_write); 
	FD_SET(socketH, &fd_write); 

	struct timeval tv = {maxWaitMS / 1000, (maxWaitMS % 1000) * 1000};   
	int result = ::select(0, (isCheckRead ? &fd_read : NULL), (isCheckWrite ? &fd_write : NULL), NULL, &tv); 
	if (result == 0) 
	{	 
		return false; 
	} 

    return true;
}

bool MP_SocketWin32Impl::win32setBlockRecv(SOCKET socketH)
{
	return false;
}

bool MP_SocketWin32Impl::win32setNBlockRecv(SOCKET socketH)
{
	return false;
}

bool MP_SocketWin32Impl::win32setBlockSend(SOCKET socketH)
{
	return false;
}

bool MP_SocketWin32Impl::win32setNBlockSend(SOCKET socketH)
{
	return false;
}

signed int MP_SocketWin32Impl::getLastError()
{
    int lastError = printLastError();
	return transErrorCode(lastError);
}

signed int MP_SocketWin32Impl::printLastError()
{
	int lastError = ::WSAGetLastError();
	printf("MP_TCPSocketWin32Impl::printLastError: Error occurs, code = %d\n", lastError);

	return lastError;
}

signed int MP_SocketWin32Impl::transErrorCode(int win32ErrorCode)
{
    switch (win32ErrorCode)
    {
        case WSAECONNRESET:  /* Connection reset by peer. */
		case WSAEDISCON:     /* Graceful shutdown in progress. Return by recv or recvfrom. */
		case WSAENOTCONN:    /* Socket is not connected. */
			{
				return MP_SOCKET_ERROR_PEER_DOWN;
			}
		    break;
			
        case WSAENETDOWN:     /* Network is down. */
		case WSAENETUNREACH:  /* Network is unreachable. */
		case WSAENETRESET:    /* Network dropped connection on reset. */
			{
				return MP_SOCKET_ERROR_NET_DOWN;
			}
		    break;
			
		case WSAECONNABORTED: /* Software caused connection abort. */
		case WSAESHUTDOWN:    /* Cannot send after socket shutdown. */
		case WSAETIMEDOUT:    /* Connection timed out. */
		case WSAECONNREFUSED: /* Connection refused. */
		case WSAEHOSTDOWN:    /* Peer Host is down. */
			{
				return MP_SOCKET_ERROR_PEER_DOWN;
			}
			break;

		default:
			{
				return MP_SOCKET_ERROR_OTHER;
			}
			break;
    }
}
}
#endif
