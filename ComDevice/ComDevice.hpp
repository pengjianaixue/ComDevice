#ifndef _COMDEVICE_H_F6E6E156D_45F6_4A2B_A786_64A674453E1F
#define _COMDEVICE_H_F6E6E156D_45F6_4A2B_A786_64A674453E1F
#if _MSC_VER >1100
#pragma once
#endif
#include <windows.h>
#include <iostream>
#include <process.h> 
#include <deque>
//C++ 11֧��
//#if _MSC_VER >=1700
//#include <thread>
//#include <mutex>
//#include <atomic>
//#endif // 0
#ifdef WIN32
using namespace std;
/** ����ͨ����
*
*  ����ʵ���˶Դ��ڵĻ�������
*  ����ʵ���˴��ڵ��첽��ͬ�������ֲ�����ʽ������������С��Ƶ�ʽϵ�ʱ�������ͬ��ģʽ����������
*  �������ݺ�Ƶ����ʱ������첽ģʽ
*  �����������ָ�����ڵ����ݡ�����ָ�����ݵ�����
*/
class CSerialPort
{
	
public:
	enum COMTYPE
	{
		Synchronous_mode = 0,//ͬ��ģʽ
		Asynchronous_mode    //�첽ģʽ


	};
	inline CSerialPort(COMTYPE comtype= Synchronous_mode);
	inline ~CSerialPort(void);

public:
	

	/** ��ʼ�����ں���
	*
	*  @param:  UINT portNo ���ڱ��,Ĭ��ֵΪ1,��COM1,ע��,������Ҫ����9
	*  @param:  UINT baud   ������,Ĭ��Ϊ9600
	*  @param:  char parity �Ƿ������żУ��,'Y'��ʾ��Ҫ��żУ��,'N'��ʾ����Ҫ��żУ��
	*  @param:  UINT databits ����λ�ĸ���,Ĭ��ֵΪ8������λ
	*  @param:  UINT stopsbits ֹͣλʹ�ø�ʽ,Ĭ��ֵΪ1
	*  @param:  DWORD dwCommEvents Ĭ��ΪEV_RXCHAR,��ֻҪ�շ�����һ���ַ�,�����һ���¼�
	*  @return: bool  ��ʼ���Ƿ�ɹ�
	*  @note:   ��ʹ�����������ṩ�ĺ���ǰ,���ȵ��ñ��������д��ڵĳ�ʼ��
	*����������   /n�������ṩ��һЩ���õĴ��ڲ�������,����Ҫ����������ϸ��DCB����,��ʹ�����غ���
	*           /n������������ʱ���Զ��رմ���,�������ִ�йرմ���
	*  @see:
	*/
	inline bool InitPort(UINT  portNo = 1, UINT  baud = CBR_9600, char  parity = 'N', UINT  databits = 8, UINT  stopsbits = 1, DWORD dwCommEvents = EV_RXCHAR);
	/** ���ڳ�ʼ������
	*
	*  �������ṩֱ�Ӹ���DCB�������ô��ڲ���
	*  @param:  UINT portNo
	*  @param:  const LPDCB & plDCB
	*  @return: bool  ��ʼ���Ƿ�ɹ�
	*  @note:   �������ṩ�û��Զ���ش��ڳ�ʼ������
	*  @see:
	*/
	 inline bool InitPort(UINT  portNo, const LPDCB& plDCB);

	/** ���������߳�
	*
	*  �������߳���ɶԴ������ݵļ���,�������յ������ݴ�ӡ����Ļ���
	*  @return: bool  �����Ƿ�ɹ�
	*  @note:   ���߳��Ѿ����ڿ���״̬ʱ,����flase
	*  @see:
	*/
	 inline bool OpenListenThread();

	/** �رռ����߳�
	*
	*
	*  @return: bool  �����Ƿ�ɹ�
	*  @note:   ���ñ�������,�������ڵ��߳̽��ᱻ�ر�
	*  @see:
	*/
	 inline bool CloseListenTread();

	 /** �����ص��ṹ�����߳�
	 *
	 *
	 *  @return: bool  �����Ƿ�ɹ�
	 *  @note:		   ���ñ�������,������ڱ��������첽ģʽ�£����߳�
					   �������ʹ�õ��ص��ṹ���м�������������Դ�ķѹ���
	 *  @see:
	 */
	 inline bool OpenClearupTread();

	 /** �����̺߳���
	 *
	 *
	 *  @return: void  
	 *  @note:	 ���������첽ģʽ��ʹ�õ��ص��ṹ���м�������������Դ�ķѹ���
	 *  @see:
	 */
	 inline static unsigned  int  WINAPI  Clearupfun(LPVOID lpparam);

	/** �򴮿�д����
	*
	*  ���������е�����д�뵽����
	*  @param:  unsigned char * pData ָ����Ҫд�봮�ڵ����ݻ�����
	*  @param:  unsigned int length ��Ҫд������ݳ���
	*  @return: bool  �����Ƿ�ɹ�
	*  @note:   length��Ҫ����pData��ָ�򻺳����Ĵ�С
	*  @see:
	*/
	 inline bool WriteData(const char* pData, unsigned int length, bool &nCompleteFlag,unsigned int WirtetimeGap);

	/** ��ȡ���ڻ������е��ֽ���
	*
	*
	*  @return: UINT  �����Ƿ�ɹ�
	*  @note:   �����ڻ�������������ʱ,����0
	*  @see:
	*/
	 inline UINT GetBytesInCOM();

	/** ��ȡ���ڽ��ջ�������ָ����������
	*
	*
	*  @param:  char & cRecved ��Ŷ�ȡ���ݵ��ַ�����
	*  @return: bool  ��ȡ�Ƿ�ɹ�
	*  @note:
	*  @see:
	*/
	 inline bool ReadComPort(char *RecviData, DWORD recvlength);
	 /** ��ȡ���ڽ��ջ�������ָ����������
	 *
	 *
	 *  @param:  char & cRecved ��Ŷ�ȡ���ݵ��ַ�����
	 *  @return: bool  ��ȡ�Ƿ�ɹ�
	 *  @note:
	 *  @see:
	 */
	 inline bool SetComTimeOut(unsigned int millsectime);
	 /*
	 
	 
	 
	 */
	 int GetNumofProcessors();
private:

	/** �򿪴���
	*
	*
	*  @param:  UINT portNo �����豸��
	*  @return: bool  ���Ƿ�ɹ�
	*  @note:
	*  @see:
	*/
	inline bool openPort(UINT  portNo);

	/** �رմ���
	*
	*
	*  @return: void  �����Ƿ�ɹ�
	*  @note:
	*  @see:
	*/
	inline void ClosePort();

	/** ���ڼ����߳�
	*
	*  �������Դ��ڵ����ݺ���Ϣ
	*  @param:  void * pParam �̲߳���
	*  @return: UINT WINAPI �̷߳���ֵ
	*  @note:
	*  @see:
	*/
	inline static UINT WINAPI ListenThread(void* pParam);
	/** ���ڼ����߳�
	*
	*  �������Դ��ڵ����ݺ���Ϣ
	*  @param:  void * pParam �̲߳���
	*  @return: UINT WINAPI �̷߳���ֵ
	*  @note:
	*  @see:
	*/
	inline	HANDLE CreateNewCompletionPort(UINT nNumofconcurrentthreads);
	/** ���ڼ����߳�
	*
	*  �������Դ��ڵ����ݺ���Ϣ
	*  @param:  void * pParam �̲߳���
	*  @return: UINT WINAPI �̷߳���ֵ
	*  @note:
	*  @see:
	*/
	inline	bool   BindCompletionPort(HANDLE hBindCompletionPortHandle, HANDLE hOpreationHandle, UINT nCompletionKey);
	/** ������ȫ�˿��¼������߳�
	*
	*  ����IO��ȫ�˿���ɵ��¼�
	*  @param:  void * pParam �̲߳���
	*  @return: UINT WINAPI �̷߳���ֵ
	*  @note:
	*  @see:
	*/
	inline static UINT WINAPI GetQueuedCompletionStatusThread(LPVOID lpparam);
	inline BOOL OpenGetQueuedCompletionStatusThread();

private:

	/** ���ھ�� */
	HANDLE  m_hComm;

	/** �߳��˳���־���� */
	static bool s_bExit;

	/** �߳̾�� */
	volatile HANDLE    m_hListenThread;

	/** ͬ������,�ٽ������� */
	CRITICAL_SECTION   m_csCommunicationSync;       //!< ����������� 
	/** ����ģʽ: Synchronous_mode  ͬ��ģʽ,
				  Asynchronous_mode �첽ģʽ*/
	COMTYPE			   m_thiscomtype;
	//���ڳ�ʱʱ�����ýṹ��
	COMMTIMEOUTS	   m_CommTimeouts;
	//����overlappedָ�������ͷ���Դ
	std::deque<OVERLAPPED*> m_usedoverlappedlist;
	bool				m_ClearupFlags;
	bool				m_bGetQueuedCompletionFlags;
	HANDLE				m_ClearupTread;
	HANDLE				m_CompletionPort;
	HANDLE              m_GetCompletionQueuethread;
	std::deque<HANDLE>	m_GetCompletionQueuethreadHANDLEList;

};

/** �߳��˳���־ */
bool CSerialPort::s_bExit = false;
/** ������������ʱ,sleep���´β�ѯ�����ʱ��,��λ:���� */
const UINT SLEEP_TIME_INTERVAL = 5;
inline CSerialPort::CSerialPort(COMTYPE comtype):m_hListenThread(INVALID_HANDLE_VALUE),m_thiscomtype(Synchronous_mode),
												 m_ClearupFlags(false), m_ClearupTread(NULL), m_CompletionPort(NULL),
												 m_bGetQueuedCompletionFlags(false), m_GetCompletionQueuethread(NULL)
{
	m_hComm = INVALID_HANDLE_VALUE;
	m_hListenThread = INVALID_HANDLE_VALUE;
	InitializeCriticalSection(&m_csCommunicationSync);
	m_thiscomtype = comtype;
	


}

inline CSerialPort::~CSerialPort(void)
{
	CloseListenTread();
	ClosePort();
	m_ClearupFlags = false;
	m_bGetQueuedCompletionFlags = false;
	WaitForSingleObject(m_ClearupTread,INFINITE);
	for (size_t i = 0; i < m_GetCompletionQueuethreadHANDLEList.size(); ++i)
	{
		WaitForSingleObject(m_GetCompletionQueuethreadHANDLEList[i],INFINITE);
	}
	DeleteCriticalSection(&m_csCommunicationSync);
}
bool CSerialPort::InitPort(UINT portNo /*= 1*/, UINT baud /*= CBR_9600*/, char parity /*= 'N'*/,
	UINT databits /*= 8*/, UINT stopsbits /*= 1*/, DWORD dwCommEvents /*= EV_RXCHAR*/)
{

	/** ��ʱ����,���ƶ�����ת��Ϊ�ַ�����ʽ,�Թ���DCB�ṹ */
	char szDCBparam[50];
	sprintf_s(szDCBparam, "baud=%d parity=%c data=%d stop=%d", baud, parity, databits, stopsbits);

	/** ��ָ������,�ú����ڲ��Ѿ����ٽ�������,�����벻Ҫ�ӱ��� */
	if (!openPort(portNo))
	{
		return false;
	}

	/** �����ٽ�� */
	EnterCriticalSection(&m_csCommunicationSync);
	/** �Ƿ��д����� */
	BOOL bIsSuccess = TRUE;
	/** �ڴ˿���������������Ļ�������С,���������,��ϵͳ������Ĭ��ֵ.
	*  �Լ����û�������Сʱ,Ҫע�������Դ�һЩ,���⻺�������
	*/
	//if (bIsSuccess )
	//{
	//bIsSuccess = SetupComm(m_hComm,1024,1024);
	//}
	/** ���ô��ڵĳ�ʱʱ��,����Ϊ0,��ʾ��ʹ�ó�ʱ���� */
	m_CommTimeouts.ReadIntervalTimeout = 0;
	m_CommTimeouts.ReadTotalTimeoutMultiplier = 0;
	m_CommTimeouts.ReadTotalTimeoutConstant = 0;
	m_CommTimeouts.WriteTotalTimeoutMultiplier = 0;
	m_CommTimeouts.WriteTotalTimeoutConstant = 0;
	if (bIsSuccess)
	{
		bIsSuccess = SetCommTimeouts(m_hComm, &m_CommTimeouts);
	}
	DCB  dcb;
	if (bIsSuccess)
	{
		// ��ANSI�ַ���ת��ΪUNICODE�ַ���  
		DWORD dwNum = MultiByteToWideChar(CP_ACP, 0, szDCBparam, -1, NULL, 0);
		wchar_t *pwText = new wchar_t[dwNum];
		if (!MultiByteToWideChar(CP_ACP, 0, szDCBparam, -1, pwText, dwNum))
		{
			bIsSuccess = TRUE;
		}
		/** ��ȡ��ǰ�������ò���,���ҹ��촮��DCB���� */
		bIsSuccess = GetCommState(m_hComm, &dcb) && BuildCommDCB(pwText, &dcb);
		/** ����RTS flow���� */
		dcb.fRtsControl = RTS_CONTROL_ENABLE;
		/** �ͷ��ڴ�ռ� */
		delete[] pwText;
	}
	if (bIsSuccess)
	{
		/** ʹ��DCB�������ô���״̬ */
		bIsSuccess = SetCommState(m_hComm, &dcb);
	}

	/**  ��մ��ڻ����� */
	PurgeComm(m_hComm, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);

	/** �뿪�ٽ�� */
	LeaveCriticalSection(&m_csCommunicationSync);

	return bIsSuccess == TRUE;
}

bool CSerialPort::InitPort(UINT portNo, const LPDCB& plDCB)
{
	/** ��ָ������,�ú����ڲ��Ѿ����ٽ�������,�����벻Ҫ�ӱ��� */
	if (!openPort(portNo))
	{
		return false;
	}

	/** �����ٽ�� */
	EnterCriticalSection(&m_csCommunicationSync);

	/** ���ô��ڲ��� */
	if (!SetCommState(m_hComm, plDCB))
	{
		return false;
		
	}

	/**  ��մ��ڻ����� */
	PurgeComm(m_hComm, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);

	/** �뿪�ٽ�� */
	LeaveCriticalSection(&m_csCommunicationSync);

	return true;
}

void CSerialPort::ClosePort()
{
	/** ����д��ڱ��򿪣��ر��� */
	if (m_hComm != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_hComm);
		m_hComm = INVALID_HANDLE_VALUE;
	}
}

bool CSerialPort::openPort(UINT portNo)
{
	/** �����ٽ�� */
	EnterCriticalSection(&m_csCommunicationSync);

	/** �Ѵ��ڵı��ת��Ϊ�豸�� */
	char szPort[50];
	sprintf_s(szPort, "COM%d", portNo);
	if (Asynchronous_mode == m_thiscomtype)
	{
		/** ��ָ���Ĵ��� */
		m_hComm = CreateFileA(szPort,     /** �豸��,COM1,COM2�� */
			GENERIC_READ | GENERIC_WRITE, /** ����ģʽ,��ͬʱ��д */
			0,                            /** ����ģʽ,0��ʾ������ */
			NULL, 
			/** ��ȫ������,һ��ʹ��NULL */
			OPEN_EXISTING,                /** �ò�����ʾ�豸�������,���򴴽�ʧ�� */
			FILE_FLAG_OVERLAPPED,
			0);
		m_CompletionPort = CreateNewCompletionPort(GetNumofProcessors());
		if (m_CompletionPort != NULL)
		{
			if (!BindCompletionPort(m_CompletionPort, m_hComm, 0))
				return false;
		}
		else
		{
			return false;
		}
		if (CSerialPort::COMTYPE::Asynchronous_mode == m_thiscomtype)
		{
			m_bGetQueuedCompletionFlags = true;
			OpenGetQueuedCompletionStatusThread();

		}


	}
	else if (Synchronous_mode == m_thiscomtype)
	{
		/** ��ָ���Ĵ��� */
		m_hComm = CreateFileA(szPort,	  /** �豸��,COM1,COM2�� */
			GENERIC_READ | GENERIC_WRITE, /** ����ģʽ,��ͬʱ��д */
			0,                            /** ����ģʽ,0��ʾ������ */
			NULL,                         /** ��ȫ������,һ��ʹ��NULL */
			OPEN_EXISTING,                /** �ò�����ʾ�豸�������,���򴴽�ʧ�� */
			0,
			0);
	}
	else
	{
		return false;
	}
	/** �����ʧ�ܣ��ͷ���Դ������ */
	if (m_hComm == INVALID_HANDLE_VALUE)
	{
		LeaveCriticalSection(&m_csCommunicationSync);
		return false;
	}

	/** �˳��ٽ��� */
	LeaveCriticalSection(&m_csCommunicationSync);

	return true;
}

bool CSerialPort::OpenListenThread()
{
	/** ����߳��Ƿ��Ѿ������� */
	if (m_hListenThread != INVALID_HANDLE_VALUE)
	{
		/** �߳��Ѿ����� */
		return false;
	}
	s_bExit = false;
	/** �߳�ID */
	UINT threadId;
	/** �����������ݼ����߳� */
	m_hListenThread = (HANDLE)_beginthreadex(NULL, 0, ListenThread, this, 0, &threadId);
	if (!m_hListenThread)
	{
		return false;
	}
	/** �����̵߳����ȼ�,������ͨ�߳� */
	if (!SetThreadPriority(m_hListenThread, THREAD_PRIORITY_ABOVE_NORMAL))
	{
		return false;
	}

	return true;
}

bool CSerialPort::CloseListenTread()
{
	if (m_hListenThread != INVALID_HANDLE_VALUE)
	{
		/** ֪ͨ�߳��˳� */
		s_bExit = true;
		/** �ȴ��߳��˳� */
		Sleep(10);
		/** ���߳̾����Ч */
		CloseHandle(m_hListenThread);
		m_hListenThread = INVALID_HANDLE_VALUE;
	}
	return true;
}

inline bool CSerialPort::OpenClearupTread()
{
	m_ClearupTread = (HANDLE)_beginthreadex(NULL, 0,Clearupfun, this, 0, NULL);
	if (m_ClearupTread == NULL)
	{
		return false;
	}
	return true;
}

inline  unsigned  int  CSerialPort::Clearupfun(LPVOID lpparam)
{
	CSerialPort *thisclass =   static_cast<CSerialPort*>(lpparam);
	while (thisclass->m_ClearupFlags)
	{
		EnterCriticalSection(&thisclass->m_csCommunicationSync);
		if (!thisclass->m_usedoverlappedlist.empty())
		{
			OVERLAPPED *clearget =  thisclass->m_usedoverlappedlist.front();
			if (clearget!= NULL)
			{
				WaitForSingleObject(clearget->hEvent, 1000);
				CloseHandle(clearget->hEvent);
				delete clearget;
			}
			thisclass->m_usedoverlappedlist.pop_front();


		}
		LeaveCriticalSection(&thisclass->m_csCommunicationSync);
	}
	return 0;
	
}

UINT CSerialPort::GetBytesInCOM()
{
	DWORD dwError = 0;  /** ������ */
	COMSTAT  comstat;   /** COMSTAT�ṹ��,��¼ͨ���豸��״̬��Ϣ */
	memset(&comstat, 0, sizeof(COMSTAT));
	UINT BytesInQue = 0;
	/** �ڵ���ReadFile��WriteFile֮ǰ,ͨ�������������ǰ�����Ĵ����־ */
	if (ClearCommError(m_hComm, &dwError, &comstat))
	{
		BytesInQue = comstat.cbInQue; /** ��ȡ�����뻺�����е��ֽ��� */
	}
	return BytesInQue;
}

UINT WINAPI CSerialPort::ListenThread(void* pParam)
{
	/** �õ������ָ�� */
	CSerialPort *pSerialPort = reinterpret_cast<CSerialPort*>(pParam);

	// �߳�ѭ��,��ѯ��ʽ��ȡ��������  
	while (!pSerialPort->s_bExit)
	{
		UINT BytesInQue = pSerialPort->GetBytesInCOM();
		/** ����������뻺������������,����Ϣһ���ٲ�ѯ */
		if (BytesInQue == 0)
		{
			Sleep(SLEEP_TIME_INTERVAL);
			continue;
		}

		/** ��ȡ���뻺�����е����ݲ������ʾ */
		//cRecvestring = new char [BytesInQue + 1];
		char cRecved = 0x00;
		int Count=0;
		do
		{	
			cRecved = 0x00;
			//if (pSerialPort->ReadComPort() == true)
			//{	
			//	/*cRecvestring[Count] = cRecved;
			//	cout << cRecved;
			//	Count++;*/
			//	continue;
			//}
		} while (--BytesInQue);
		//delete[] cRecvestring;
	}

	return 0;
}

inline HANDLE CSerialPort::CreateNewCompletionPort(UINT nNumofconcurrentthreads)
{
	return CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, nNumofconcurrentthreads);
}

inline bool CSerialPort::BindCompletionPort(HANDLE hBindCompletionPortHandle, HANDLE hOpreationHandle, UINT nCompletionKey)
{
	HANDLE  h = CreateIoCompletionPort(hOpreationHandle, hBindCompletionPortHandle, nCompletionKey, 0);
	return (h== hBindCompletionPortHandle); 
}
inline UINT CSerialPort::GetQueuedCompletionStatusThread(LPVOID lpparam)
{
	CSerialPort *thisclass = static_cast<CSerialPort*> (lpparam);
	if (NULL == thisclass  )
	{
		return 1;
	}
	DWORD dwTransferdBytes = 0;
	ULONG ulCompletionKey;
	LPOVERLAPPED operationverlapped = NULL;
	while (thisclass->m_bGetQueuedCompletionFlags)
	{	
		BOOL bresult = GetQueuedCompletionStatus(thisclass->m_CompletionPort, &dwTransferdBytes, &ulCompletionKey, &operationverlapped, INFINITE);
		if (bresult)
		{	
			
			delete operationverlapped;	
		}
		else
		{
			if (operationverlapped!=NULL)
			{
				delete operationverlapped;
			}
			else
			{

				DWORD error = GetLastError();
				if (error==WAIT_TIMEOUT)
				{
					continue;
				}
			}
		}
	}	
	return 0;
}

inline BOOL CSerialPort::OpenGetQueuedCompletionStatusThread()
{
	UINT numofprocessor = GetNumofProcessors();
	HANDLE *threadhandlelist = new HANDLE[numofprocessor];
	for (size_t i = 0; i < numofprocessor*2; i++)
	{
		threadhandlelist[i] = (HANDLE)_beginthreadex(NULL, 0, GetQueuedCompletionStatusThread, this, 0, NULL);
		if (threadhandlelist[i]!=NULL)
		{
			m_GetCompletionQueuethreadHANDLEList.push_back(threadhandlelist[i]);

		}
		else
		{
#ifdef _DEBUG
			std::cout << "�����߳�"<<"GetQueuedCompletionStatusThread:"<<i<<"ʧ��"<< std::endl;
#endif // DEBUG

		}
	}
	return TRUE;
}

bool CSerialPort::ReadComPort(char *RecviData, DWORD recvlength )
{
	BOOL  bResult = TRUE;
	DWORD BytesRead = 0;
	if (m_hComm == INVALID_HANDLE_VALUE)
	{
		return false;
	}
	//�Խ��ܻ��������г�ʼ��
	UINT BytesInQue = GetBytesInCOM();
	/** ����������뻺������������,����Ϣһ���ٲ�ѯ */
	while (BytesInQue == 0)
	{
		Sleep(SLEEP_TIME_INTERVAL);
		break;
	}
	/** �ٽ������� */
	EnterCriticalSection(&m_csCommunicationSync);

	/** �ӻ�������ȡ���� */
	bResult = ReadFile(m_hComm, &RecviData, recvlength, &BytesRead, NULL);
	if ((!bResult))
	{
		/** ��ȡ������,���Ը��ݸô�����������ԭ�� */
		DWORD dwError = GetLastError();

		/** ��մ��ڻ����� */
		PurgeComm(m_hComm, PURGE_RXCLEAR | PURGE_RXABORT);
		LeaveCriticalSection(&m_csCommunicationSync);
		return false;
	}
	/** �뿪�ٽ��� */
	LeaveCriticalSection(&m_csCommunicationSync);

	return (BytesRead == 1);

}

inline bool CSerialPort::SetComTimeOut(unsigned int millsectime)
{	
	int ret = 0;
	m_CommTimeouts.ReadIntervalTimeout = 0;
	m_CommTimeouts.ReadTotalTimeoutConstant = millsectime;
	m_CommTimeouts.ReadTotalTimeoutMultiplier = 1;
	m_CommTimeouts.WriteTotalTimeoutConstant = millsectime;
	m_CommTimeouts.WriteTotalTimeoutMultiplier=1;
	return 1==(ret=SetCommTimeouts(m_hComm,&m_CommTimeouts));
}

inline int CSerialPort::GetNumofProcessors()
{
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	return si.dwNumberOfProcessors;
}

bool CSerialPort::WriteData (const char* pData, unsigned int length,bool &nCompleteFlag, unsigned int WirtetimeGap)
{
	BOOL   bResult = TRUE;
	DWORD  BytesToSend = 0;
	if (m_hComm == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	if (CSerialPort::COMTYPE::Synchronous_mode == m_thiscomtype)
	{
		/** �򻺳���д��ָ���������� */
		Sleep(WirtetimeGap);
		bResult = WriteFile(m_hComm, pData, length, &BytesToSend, NULL);
		if (!bResult)
		{
			DWORD dwError = GetLastError();
			/** ��մ��ڻ����� */
			PurgeComm(m_hComm, PURGE_RXCLEAR | PURGE_RXABORT);
			//LeaveCriticalSection(&m_csCommunicationSync);
			return false;
		}
	}
	else if (CSerialPort::COMTYPE::Asynchronous_mode == m_thiscomtype)
	{	

		OVERLAPPED *wirteover = new OVERLAPPED;
		*wirteover = { 0 };
		wirteover->Offset = 0;
		wirteover->hEvent = CreateEvent(NULL,FALSE,FALSE,LPCWSTR(""));
		bResult = WriteFile(m_hComm, pData, length, &BytesToSend, wirteover);
		if (bResult!=TRUE)
		{	

			DWORD errorcode = GetLastError();
			if (errorcode!= ERROR_IO_PENDING)
			{	
				delete wirteover;
				return false;
			}
		}
		else
		{
			delete wirteover ;
		
			return false;
		}
	}
	return true;
}
#endif // WIN32
#endif 
