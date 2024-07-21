
#pragma once
#include "GLFW/glfw3.h"
#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3native.h"
#include "input.h"

class Window{
  InputHandler m_inputHandler;
  int m_height, m_width;
  void fpsCounterUpdate();
  HWND m_hwnd;
  void initHwnd();
  public:
  GLFWwindow* m_windowInstance;
  void closeWindow(){glfwSetWindowShouldClose(m_windowInstance, GLFW_TRUE);}
  void initInput(Direct3D& d3d);
  Window();
  ~Window();
  Window(const Window&) = delete;
  Window& operator=(const Window&) = delete;
  int getWindowStatus();
  void update();
  const HWND getHwnd()const;
  void throwErrorBox(char* pString) noexcept;
};
