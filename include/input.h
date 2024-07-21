#pragma once
#include "global.h"
#include "defines.h"

#include "direct3d.h"
#include <GLFW/glfw3.h>

#include "camera.h"
#include "camera.h"


//TODO: please fix
namespace Input {
  inline Direct3D* pDirect3d;
  inline Window* pWindow;
  inline Camera* pCamera;
  
  constexpr float cameraMove = 0.01;
  constexpr float posOrNeg = 1;

  inline double lastFrameMousePosX = 0;
  inline double lastFrameMousePosY = 0;
  inline double mouseXMoveDistance;
  inline double mouseYMoveDistance;
  inline bool mouseMoved = false;

  inline bool A_KEY_DOWN = false;
  inline bool D_KEY_DOWN =false;
  inline bool S_KEY_DOWN = false;
  inline bool W_KEY_DOWN =false;


  inline void update(){
    if(W_KEY_DOWN == true){
      pCamera->setCameraPos(0.0f, 0.0f, cameraMove, posOrNeg);
    }

    if(S_KEY_DOWN == true){
      pCamera->setCameraPos(0.0f, 0.0f, cameraMove, -posOrNeg);
    }

    if(D_KEY_DOWN == true){
      pCamera->setCameraPos(cameraMove, 0.0f, 0.0f, posOrNeg);
    }

    if(A_KEY_DOWN == true){
      pCamera->setCameraPos(cameraMove, 0.0f, 0.0f, -posOrNeg);
    }
    
    if(mouseMoved){
      pCamera->updateRotation((float)mouseXMoveDistance, (float)mouseYMoveDistance);
    }
  }
  

  void closeWindow();
  void unlockCursor();
  void changeMousePos(double x, double y);

  static void inputKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if(key == GLFW_KEY_Z && action == GLFW_PRESS){
      pDirect3d->switchRasterizerState(RS_WIREFRAME);
    }

    if(key == GLFW_KEY_X && action == GLFW_PRESS){
      pDirect3d->switchRasterizerState(RS_DEFAULT);
    }

    if(key == GLFW_KEY_Q && action == GLFW_PRESS){
      pCamera->test(0.07f,0.0f);
    }

    if(key == GLFW_KEY_E && action == GLFW_PRESS){
    pCamera->test(-0.07f, 0.0f);

    }

    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
      closeWindow();
    }
    
    if(key == GLFW_KEY_W && action == GLFW_RELEASE){ W_KEY_DOWN = false;}
    if(key == GLFW_KEY_W && action == GLFW_PRESS|| W_KEY_DOWN == true){
      W_KEY_DOWN = true;
      // pCamera->setCameraPos(0.0f, 0.0f, cameraMove, -posOrNeg);
    }

    if(key == GLFW_KEY_S && action == GLFW_RELEASE){ S_KEY_DOWN = false;}
    if(key == GLFW_KEY_S && action == GLFW_PRESS|| S_KEY_DOWN == true){
      S_KEY_DOWN = true;
      // pCamera->setCameraPos(0.0f, 0.0f, cameraMove, posOrNeg);
    }

    if(key == GLFW_KEY_A && action == GLFW_RELEASE){ A_KEY_DOWN = false;}
    if(key == GLFW_KEY_A && action == GLFW_PRESS || A_KEY_DOWN == true){
      A_KEY_DOWN = true;
      // pCamera->setCameraPos(cameraMove, 0.0f, 0.0f, posOrNeg);
    }

    if(key == GLFW_KEY_D && action == GLFW_RELEASE){ D_KEY_DOWN = false;}
    if(key == GLFW_KEY_D && action == GLFW_PRESS || D_KEY_DOWN == true){
      D_KEY_DOWN = true;
      // pCamera->setCameraPos(cameraMove, 0.0f, 0.0f, -posOrNeg);
    }

  }

}




class InputHandler{
    private:
    GLFWwindow* m_windowHandle;
    void updateCursor();
    public:
      void init(Direct3D* d3d);
      void update();
      InputHandler(GLFWwindow& window, Window* win);
      InputHandler() = default;
      ~InputHandler() = default;

      double m_mouseX, m_mouseY;
};
