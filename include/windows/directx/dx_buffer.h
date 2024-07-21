#pragma once
#include "global.h"
#include "defines.h"
#include "primitives.h"
#include "dx_buffer.h"

class Direct3D;
class ID3D11Buffer;
struct D3D11_BUFFER_DESC;
struct Vertex;
struct Indice;
class ID3D11Device;

class DirectBufferObject{
  private:
    void newConstantBuffer() const;
  public:
    ID3D11Buffer* m_pBuffer = nullptr;
    D3D11_BUFFER_DESC* m_pBufferDesc = nullptr;
    u32 m_bufferSize;
    u32 m_stride = 0;
    u32 m_offset = 0;
    u32 m_indiceCount = 0;
    DirectBufferObject() = default;
    ~DirectBufferObject();
    void initAsVertexBuffer(const Direct3D& direct3d, std::vector<Vertex> bufferData, const b8 isMutable = 1);
    void initAsVertexBufferWithTexture(const Direct3D& direct3d, std::vector<VertexT> bufferData, const b8 isMutable = 1);
    void initAsIndexBuffer(const Direct3D& direct3d, std::vector<Indice> bufferData, const b8 isMutable= 1);
    const u32 getBufferSize()const;
    
};
