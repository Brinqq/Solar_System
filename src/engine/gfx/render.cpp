#include "render.h"
#include "direct3d.h"
#include "window.h"
#include "mesh.h"

// TODO: Please fix the const cast in Render constructer


Renderer::Renderer(const Window& window){
  m_pDirectX = new Direct3D(const_cast<Window&>(window));
  m_pWindow = &window;
}

Renderer::~Renderer(){
  free((Direct3D*)m_pDirectX);
}

unsigned int Renderer::addRenderable(const Renderable& renderable){
  
  return 1;
};


