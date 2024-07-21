#pragma once
#include "global.h"
#include "defines.h"
#include "primitives.h"

#include <DirectXMath.h>


class ID3D11Buffer;

enum ConstantBufferDest{
  CONSTANT_BUFFER_PS = 0,
  CONSTANT_BUFFER_VS = 1
};

struct ConstantBuffer{
  void* m_data;
  ConstantBufferDest m_dest;
  u32 m_byteSize;
};

template<typename T>
void* toVoidPtr(T& data){return &data;}

struct ColorCBuffer{
  float r, g, b;
};

struct TransformCBuffer{
  DirectX::XMMATRIX transform;
};
