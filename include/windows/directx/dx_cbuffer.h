#pragma once

#include "defines.h"
#include "d3d_err.h"
#include "constantbuffer.h"

#include <d3d11.h>


struct DirectCBuffer{
  ID3D11Buffer* m_pBuffer;
  ConstantBufferDest m_shaderDest;
};

DirectCBuffer newCBuffer(ID3D11Device* device, const ConstantBuffer& cbo);

void freeCBuffer(ID3D11Buffer* pBuffer);
