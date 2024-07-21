#include <stdio.h>
#include "string"
#include "window.h"
#include "error.h"

#include "direct3d.h"

struct FrameCounter{
  std::string fps, frameTime;
  double prevTime, newTime, timeDiff;
  unsigned int frameCount = 0;

};

static FrameCounter frames;

void Window::fpsCounterUpdate(){
  frames.newTime = glfwGetTime();
  frames.timeDiff = frames.newTime - frames.prevTime;
  frames.frameCount++;
  if(frames.timeDiff >= 1 / 3.0){
    frames.fps = std::to_string((1.0/ frames.timeDiff)*frames.frameCount);
    frames.frameTime = std::to_string((frames.timeDiff / frames.frameCount)* 1000);
    std::string newTitle = "solar-system - fps: " + frames.fps + " - FrameTime: " + frames.frameTime + "ms";
    glfwSetWindowTitle(m_windowInstance, newTitle.c_str());
    frames.prevTime = frames.newTime;
    frames.frameCount = 0;
  }
}

void Window::initInput(Direct3D& d3d){
  glfwSetInputMode(m_windowInstance, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetKeyCallback(m_windowInstance, Input::inputKeyCallback);
  m_inputHandler.init(&d3d);
}

Window::Window():m_width(1920), m_height(1080){ 
  glfwInit();
  m_windowInstance = glfwCreateWindow(m_width, m_height, "solar-system", nullptr, nullptr);
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  frames.prevTime = glfwGetTime();
  m_hwnd = glfwGetWin32Window(m_windowInstance);
  m_inputHandler = InputHandler(*m_windowInstance, this);
}

Window::~Window(){
  glfwDestroyWindow(m_windowInstance);
  glfwTerminate();
}

int Window::getWindowStatus(){
  return glfwWindowShouldClose(m_windowInstance);
}

void Window::update(){
  fpsCounterUpdate();
  glfwPollEvents();
  double x = 0, y = 0;
  glfwGetCursorPos(m_windowInstance, &x, &y);
  Input::changeMousePos(x, y);
}

void Window::throwErrorBox(char* pString) noexcept{
  int msgBox = MessageBox(m_hwnd, pString, NULL, MB_OK|MB_ICONERROR);
  if(msgBox == IDOK){
    exit(0);
  }
}

const HWND Window::getHwnd() const{
  return m_hwnd;
}
