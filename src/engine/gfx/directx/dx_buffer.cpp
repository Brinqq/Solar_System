#include "dx_buffer.h"
#include "direct3d.h"
#include "d3d_err.h"
#include "primitives.h"

#include <d3d11.h>

//TODO: Do u free D3D11_BUFFER_DESC manually?

  ID3D11Buffer* pBuffer;

DirectBufferObject::~DirectBufferObject(){
  delete m_pBufferDesc;
  if(m_pBuffer != nullptr){m_pBuffer->Release();}
}

void DirectBufferObject::initAsVertexBuffer(const Direct3D& direct3d, std::vector<Vertex> bufferData, const b8 isMutable){
  m_bufferSize = sizeof(Vertex)*bufferData.size();
  m_stride = sizeof(Vertex);
  m_pBufferDesc = new D3D11_BUFFER_DESC;
  D3D11_BUFFER_DESC bd = {};
  D3D11_SUBRESOURCE_DATA sd = {};
  bd.Usage = D3D11_USAGE_IMMUTABLE;
  if(isMutable){bd.Usage = D3D11_USAGE_DEFAULT;}
  bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
  bd.CPUAccessFlags = 0;
  bd.MiscFlags = 0;
  bd.StructureByteStride = m_stride;
  bd.ByteWidth = m_bufferSize;
  sd.pSysMem = &bufferData[0];
  DXCALL(direct3d.getDeviceObj()->CreateBuffer(&bd, &sd, &m_pBuffer))
  m_pBuffer->GetDesc(m_pBufferDesc);
}

void DirectBufferObject::initAsVertexBufferWithTexture(const Direct3D& direct3d, std::vector<VertexT> bufferData, const b8 isMutable){
  m_bufferSize = sizeof(VertexT)*bufferData.size();
  m_stride = sizeof(VertexT);
  m_pBufferDesc = new D3D11_BUFFER_DESC;
  D3D11_BUFFER_DESC bd = {};
  D3D11_SUBRESOURCE_DATA sd = {};
  bd.Usage = D3D11_USAGE_IMMUTABLE;
  if(isMutable){bd.Usage = D3D11_USAGE_DEFAULT;}
  bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
  bd.CPUAccessFlags = 0;
  bd.MiscFlags = 0;
  bd.StructureByteStride = m_stride;
  bd.ByteWidth = m_bufferSize;
  sd.pSysMem = &bufferData[0];
  DXCALL(direct3d.getDeviceObj()->CreateBuffer(&bd, &sd, &m_pBuffer))
  m_pBuffer->GetDesc(m_pBufferDesc);
}

void DirectBufferObject::initAsIndexBuffer(const Direct3D& direct3d, std::vector<Indice> bufferData, const b8 isMutable){
  m_indiceCount = bufferData.size()*3;
  m_bufferSize = sizeof(Indice)*bufferData.size();
  m_stride = sizeof(u16);
  m_pBufferDesc = new D3D11_BUFFER_DESC;
  D3D11_BUFFER_DESC bd = {};
  D3D11_SUBRESOURCE_DATA sd = {};
  bd.Usage = D3D11_USAGE_IMMUTABLE;
  if(isMutable){bd.Usage = D3D11_USAGE_DEFAULT;}
  bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
  bd.CPUAccessFlags = 0;
  bd.MiscFlags = 0;
  bd.StructureByteStride = m_stride;
  bd.ByteWidth = m_bufferSize;
  sd.pSysMem = &bufferData[0];
  DXCALL(direct3d.getDeviceObj()->CreateBuffer(&bd, &sd, &m_pBuffer))
  m_pBuffer->GetDesc(m_pBufferDesc);
}


const u32 DirectBufferObject::getBufferSize()const{
  return m_pBufferDesc->ByteWidth;
}


