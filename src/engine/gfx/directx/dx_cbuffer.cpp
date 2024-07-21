#include "dx_cbuffer.h"


DirectCBuffer newCBuffer(ID3D11Device* device, const ConstantBuffer& cbo){
  DirectCBuffer cBuffer = {nullptr, cbo.m_dest};
  ID3D11Buffer* pBuffer = (ID3D11Buffer*)malloc(sizeof(ID3D11Buffer));
  D3D11_BUFFER_DESC bd;
  D3D11_SUBRESOURCE_DATA sd;
  bd.Usage = D3D11_USAGE_DYNAMIC;
  bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
  bd.MiscFlags = 0;
  bd.ByteWidth = cbo.m_byteSize;
  bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
  bd.StructureByteStride = 0;
  sd.pSysMem = cbo.m_data;
  DXCALL(device->CreateBuffer(&bd, &sd, &pBuffer))
  cBuffer.m_pBuffer = pBuffer;
  return cBuffer; 
}

void freeCBuffer(ID3D11Buffer* pBuffer){
  free(pBuffer);
}
