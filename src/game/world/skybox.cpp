#include "skybox.h"

const std::vector<Vertex> skyboxVertices = {
    {-1.0f, -1.0f,  -0.9f},
    { 1.0f, -1.0f,  0.9f},
    { 1.0f,  1.0f,  -0.9f},
    {-1.0f,  1.0f,  -0.9f},
    {-1.0f, -1.0f, 0.9f}, 
    { 1.0f, -1.0f, 0.9f},
    { 1.0f,  1.0f, 0.9f},
    {-1.0f,  1.0f, 0.9f}
};


const std::vector<Indice> skyboxIndices = {
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



const std::vector<VertexT> testSkyboxV = {
  {-0.5, -0.5f, 0.9f,0.0,1.0},
  {-0.5, 0.5f, 0.9f,0.0,0.0},
  {0.5, 0.5f, 0.9f, 1.0,0.0},
  {0.5, -0.5f, 0.9f,1.0,1.0},
};

const std::vector<Indice> testSkyboxI = {
  {0,1,2},
  {0,2,3},
};



Mesh Game::getNewSkyBox(){
  Mesh mesh;
  mesh.m_verticesT = &testSkyboxV; 
  mesh.m_indices = &testSkyboxI;
  mesh.m_shaderInputs = {{"Position",0  ,0}, {"TexCoord",0,12,DATA_FORMAT_FLOAT2D}};
  mesh.m_vsPath = L"C:/main/dev/projects/solar-system/bin/shaders/skybox_vs.cso";
  mesh.m_psPath = L"C:/main/dev/projects/solar-system/bin/shaders/skybox_ps.cso";
  mesh.requiresTexture = 1;
  return mesh;
}
