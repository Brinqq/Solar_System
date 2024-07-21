#pragma once




class Window;
class Direct3D;
class Mesh;


class Renderable{
  public:
    Mesh* m_pMesh;
};

class Renderer{
  private: 
    const Direct3D* m_pDirectX;
    const Window* m_pWindow;
  public:
    Renderer() = delete;
    ~Renderer();
    Renderer(const Renderer& other) = delete;
    Renderer(const Window& window);
    unsigned int addRenderable(const Renderable& render);
     

};
