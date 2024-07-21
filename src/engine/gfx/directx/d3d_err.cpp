#include "d3d_err.h"
#include "sstream"
#include "window.h"


Window* pWindowHandle;
ID3D11Device* Device;

void setDeviceDXErrors(ID3D11Device& device){
  Device = &device;
}

void setWindowDXErrors(Window& window){
  pWindowHandle = &window;
}

DXError::DXError(int line, char* file, HRESULT hr):m_line(line),m_file(file),m_hr(hr){
  if(hr == DXGI_ERROR_DEVICE_REMOVED){
    m_hr = Device->GetDeviceRemovedReason();
  }
  translateHResult();
  initOutputString();
  pWindowHandle->throwErrorBox(m_outputString);
}

DXError::~DXError(){

}


 void DXError::initOutputString(){
   std::stringstream oss;
   oss << m_type<<std::endl
   << "[File] "<< m_file<<std::endl
   <<"[line] "<< m_line<< std::endl
   <<"[Error] "<< m_hrDescription<<std::endl;
  m_outputStringBuffer = oss.str();
  m_outputString = m_outputStringBuffer.data();
}

void DXError::translateHResult(){
  char* pMessageBuffer = nullptr;
  DWORD messageLength = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        nullptr, m_hr, MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT), reinterpret_cast<LPSTR>(&pMessageBuffer),0,nullptr);
  m_hrDescription = pMessageBuffer;
  LocalFree(pMessageBuffer);
}

DXDebug::~DXDebug(){

}

void DXDebug::init(){
  m_pDeviceHandle->QueryInterface(__uuidof(ID3D11InfoQueue), (void**)&m_pInfoQueue);

}

void DXDebug::printInfoMessages(){
  for(D3D11_MESSAGE* value : m_messages){
    printf("%s\n", value->pDescription);
  }
  exit(0);
}

void DXDebug::getNewInfoMessages(){
  m_messages.clear();
  u64 msgLength;
  for(u64 i = 0; i < m_msgCount; i++){
      m_pInfoQueue->GetMessage(i,NULL,&msgLength);
      D3D11_MESSAGE* message = (D3D11_MESSAGE*)malloc(msgLength);
      // m_pInfoQueue->GetMessageA(i, message, &msgLength);
      m_pInfoQueue->GetMessage(i, message, &msgLength);
      m_messages.emplace_back(message);
    }
}

void DXDebug::clearInfoQueue(){
  m_msgCount = m_pInfoQueue->GetNumStoredMessagesAllowedByRetrievalFilter();
  if(m_msgCount != 0){
      getNewInfoMessages();
      printInfoMessages();
      m_pInfoQueue->ClearStoredMessages();
    }


}
