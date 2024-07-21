#pragma once
#include "global.h"
#include "defines.h"
#include "d3d_err.h"
#include "dx_buffer.h"
#include "dx_shader.h"
#include "dx_renderouput.h"
#include "dx_cbuffer.h"
#include "mesh.h"
#include "constantbuffer.h"
#include "renderdefines.h"

class Window;
class ID3D11Device;
class ID3D11DeviceContext;
struct DirectRenderStateObject;

class Direct3D{
  private:
    HWND m_windowHandle;
    RenderOutput m_mainRenderOutput;
    DXDebug m_debug;
    std::unordered_map<u32, DirectRenderStateObject*> m_renderObjects;
    const float bgColor[4] = {0.0f, 0.1f, 0.1f, 1.0f};
    void draw(u32 indices);
    void bindRenderObject(const DirectRenderStateObject& renderObject);
    DirectCBuffer initCbufferObject(const ConstantBufferDest cbd, const u32 byteSizePacked);
    ID3D11SamplerState* m_samplerState;
  public:
  void test(DirectX::XMMATRIX mat);
    ID3D11Device* m_pDevice;
    ID3D11DeviceContext* m_pContext;
    Direct3D() = delete;
    ~Direct3D() = default;
    Direct3D(const Window& window);
    void testing();
    void testUpdate();
    u32 newRenderObject(Mesh& mesh);
    void switchRasterizerState(RendererRasterizerState rss);
    inline  HWND getHwnd()const{return m_windowHandle;}
    inline ID3D11Device** getDevice(){return &m_pDevice;}
    inline ID3D11DeviceContext ** getContext(){return &m_pContext;}
    inline ID3D11Device* getDeviceObj()const{return m_pDevice;}
    void p(){printf("m");}
};
