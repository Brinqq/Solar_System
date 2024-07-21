#pragma once
//
// #include <windows.h>
//
// #define MODE_DEBUG
//
// #ifdef MODE_DEBUG
// #define DXCALL(hr) if(hr != S_OK){DXError(__LINE__,(char*)__FILE__, hr);}
// #else
// #define DXCALL(hr)
// #endif
//
// class Window;
//
// class Error{
// public:
//   Error() = default;
//   ~Error() = default; 
//
// };
// class DXError{
//   private:
//     HRESULT m_hr;
//     const std::string m_type = "Directx Error";
//     std::string m_outputStringBuffer;
//     std::string m_hrDescription;
//     char* m_file;
//     char* m_outputString;
//     int m_line;
//     void initOutputString();
//     void translateHResult();
//     void throwError();
//   public:
//     DXError() = delete;
//     DXError(int line, char* file, HRESULT hr);
//     ~DXError();
//     const int getLine() const{ return m_line; }
//     const char* getFile() const{ return m_file; }
//
//   private:
// };
//
// void initErrors(Window* window);
