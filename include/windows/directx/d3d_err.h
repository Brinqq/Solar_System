#pragma once
#include "global.h"
#include "defines.h"
#include "windows.h"

#include <d3d11.h>
#include <d3d11sdklayers.h>


class Window;


class DXDebug{
  private:
    ID3D11Device* m_pDeviceHandle;
    ID3D11InfoQueue* m_pInfoQueue;
    std::vector<D3D11_MESSAGE*> m_messages;
    u64 m_msgCount = 0;
    void getNewInfoMessages();
    void printInfoMessages();
  public:
    void clearInfoQueue();
    void init();
    DXDebug(ID3D11Device* pDevice):m_pDeviceHandle(pDevice){}
    DXDebug() = default;
    ~DXDebug();
};



class DXError{
  private:
    HRESULT m_hr;
    const std::string m_type = "Directx Error";
    std::string m_outputStringBuffer;
    std::string m_hrDescription;
    char* m_file;
    char* m_outputString;
    int m_line;
    void initOutputString();
    void translateHResult();
    void throwError();
  public:
    DXError() = delete;
    DXError(int line, char* file, HRESULT hr);
    ~DXError();
    const int getLine() const{ return m_line; }
    const char* getFile() const{ return m_file; }

  private:
};


#ifdef MODE_DEBUG
#define DXINFO(call) call; m_debug.clearInfoQueue();
#define DXCALL(hr) if(hr != S_OK){DXError(__LINE__,(char*)__FILE__, hr);}
#else
#define DXCALL(hr)
#endif

void setDeviceDXErrors(ID3D11Device& device);
void setWindowDXErrors(Window& window);
