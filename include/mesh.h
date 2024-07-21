#pragma once
#include "global.h"
#include "defines.h"
#include "constantbuffer.h"
#include "d3d11.h"

enum ShaderLayoutFormat{
DATA_FORMAT_FLOAT2D = DXGI_FORMAT_R32G32_FLOAT,
DATA_FORMAT_FLOAT3D = DXGI_FORMAT_R32G32B32_FLOAT,
};

struct Vertex;
struct Indice;

struct ShaderInputLayout{
  const char* semanticName;
  u32 semanticeIndex = 0;
  u32 byteOffset = 0;
  ShaderLayoutFormat m_format = DATA_FORMAT_FLOAT3D;
};

struct Mesh{
  const wchar_t* m_psPath;
  const wchar_t* m_vsPath;
  const std::vector<Vertex>* m_vertices;
  const std::vector<VertexT>* m_verticesT;
  const std::vector<Indice>* m_indices;
  unsigned int requiresTexture = 0;
  std::vector<ShaderInputLayout> m_shaderInputs;
  std::vector<ConstantBuffer> m_constantBuffers;

};
