
#include "input.h"
#include "global.h"
#include "GLFW/glfw3.h"

#include "direct3d.h"
#include "Window.h"

void Input::closeWindow(){
  pWindow->closeWindow();
}

void InputHandler::init(Direct3D* d3d){
Input::pDirect3d = d3d;
}

void InputHandler::update(){
  updateCursor();
}

void InputHandler::updateCursor(){
  glfwGetCursorPos(m_windowHandle, &m_mouseX, &m_mouseY);
}


InputHandler::InputHandler(GLFWwindow& window, Window* win){m_windowHandle = &window; Input::pWindow = win;}

