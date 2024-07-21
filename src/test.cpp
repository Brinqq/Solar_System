#include "test.h"
#include "global.h"
#include "constantbuffer.h"
#include "window.h"
#include "direct3d.h"
#include "d3d_err.h"
#include "primitives.h"
#include "d3dref.h"
#include "skybox.h"
#include "dx_texture.h"
#include "camera.h"
#include "planets.h"
#include "input.h"

#include "DirectXMath.h"

std::vector<Vertex> cubeVertices = {
    {-0.5f, -0.5f,  0.0f},
    { 0.5f, -0.5f,  0.0f},
    { 0.5f,  0.5f,  0.0f},
    {-0.5f,  0.5f,  0.0f},
    {-0.5f, -0.5f, 1.0f}, 
    { 0.5f, -0.5f, 1.0f},
    { 0.5f,  0.5f, 1.0f},
    {-0.5f,  0.5f, 1.0f}
};


std::vector<Indice> cubeIndices = {
    {0, 1, 2},
    {2, 3, 0},
    {1, 5, 6},
    {6, 2, 1},
    {7, 6, 5},
    {5, 4, 7},
    {4, 0, 3},
    {3, 7, 4},
    {3, 2, 6},
    {6, 7, 3},
    {4, 5, 1},
    {1, 0, 4}
};

float angleo = 1.0;

ColorCBuffer color = {1.0f, 0.0f, 5.0f};
TransformCBuffer transform = {
  {
}
};

DirectX::XMMATRIX view;

Camera camera;

float f = 0.0f;

void updateTransform(float speed){
  angleo += speed;
  transform = {
    DirectX::XMMatrixTranspose(
      DirectX::XMMatrixRotationY(angleo)*
      DirectX::XMMatrixRotationZ(angleo)*
      DirectX::XMMatrixTranslation(0,0, 2) * camera.viewMatrix * camera.projectionMatrix
    )
  };
}

std::vector<Vertex> sphere;
std::vector<Indice> sphereIndices;

void initMesh(Mesh& mesh){
  mesh.m_vsPath = L"C:/main/dev/projects/solar-system/bin/shaders/test_triangle_vs.cso";
  mesh.m_psPath = L"C:/main/dev/projects/solar-system/bin/shaders/test_triangle_ps.cso";
  generateSphere(0.7, 30, 30, sphere, sphereIndices);
  mesh.m_vertices = &sphere;
  mesh.m_indices = &sphereIndices;
  mesh.m_shaderInputs = {{"Position"}};
  ConstantBuffer colorCBuffer {toVoidPtr(color),CONSTANT_BUFFER_PS,16};
  ConstantBuffer transformCBuffer {toVoidPtr(transform), CONSTANT_BUFFER_VS, sizeof(transform)};
  mesh.m_constantBuffers.emplace_back(colorCBuffer);
  mesh.m_constantBuffers.emplace_back(transformCBuffer);
}

void input(){
  Input::pCamera = &camera;
}

void start(){
  Mesh mesh;
  Window window;
  initMesh(mesh);
  input();
  Mesh skybox = Game::getNewSkyBox();
  Direct3D direct3d(window);
  setWindowDXErrors(window);
  window.initInput(direct3d);
  u32 a = direct3d.newRenderObject(mesh);
  u32 skyboxId = direct3d.newRenderObject(skybox);
  while(!window.getWindowStatus()){
    Input::update();
    updateTransform(0.01);
    direct3d.test(transform.transform);
    window.update();
    direct3d.testUpdate();
   }
}
