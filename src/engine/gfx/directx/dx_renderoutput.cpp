#include "dx_renderouput.h"
#include "direct3d.h"
#include "d3d_err.h"
#include "defines.h"

#include <d3d11.h>


void RenderOutput::newRenderTarget(Direct3D& direct3d, const HWND& outputWindowHandle){
  m_viewPort.Width = 1920;
  m_viewPort.Height = 1080;
  m_viewPort.MinDepth = 0;
  m_viewPort.MaxDepth = 1;
  m_viewPort.TopLeftX = 0;
  m_viewPort.TopLeftY = 0;
  u32 deviceLayer = 0;
  #ifdef MODE_DEBUG
    deviceLayer = D3D11_CREATE_DEVICE_DEBUG;
  #endif
  DXGI_SWAP_CHAIN_DESC sd;
  sd.BufferDesc.Width = 0;
  sd.BufferDesc.Height = 0;
  sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
  sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
  sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
  sd.BufferDesc.RefreshRate.Numerator = 0;
  sd.BufferDesc.RefreshRate.Denominator = 1;
  sd.SampleDesc.Count = 1;
  sd.SampleDesc.Quality = 0;
  sd.Windowed = true; 
  sd.BufferCount = 1;
  sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
  sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
  sd.Flags = 0;
  sd.OutputWindow = direct3d.getHwnd(); 
  D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, deviceLayer, nullptr, 0, D3D11_SDK_VERSION, &sd, &m_pSwapChain, direct3d.getDevice(), nullptr, direct3d.getContext());

  ID3D11Resource* a = nullptr;
  DXCALL(m_pSwapChain->GetBuffer(0,_uuidof(a),reinterpret_cast<void**>(&a)))
  DXCALL(direct3d.getDeviceObj()->CreateRenderTargetView(a,nullptr,&m_pRenderTarget))
  a->Release();
  
  D3D11_DEPTH_STENCIL_DESC ds = {};
  ds.DepthEnable = true;
  ds.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
  ds.DepthFunc = D3D11_COMPARISON_LESS;
  DXCALL(direct3d.m_pDevice->CreateDepthStencilState(&ds, &m_pDepthStencilState))
  direct3d.m_pContext->OMSetDepthStencilState(m_pDepthStencilState, 1u);
  
  D3D11_TEXTURE2D_DESC dst = {};
  dst.Width = 1920;
  dst.Height = 1061;
  dst.MipLevels = 1u;
  dst.ArraySize = 1u;
  dst.Format =DXGI_FORMAT_D32_FLOAT;
  dst.SampleDesc.Count = 1u;
  dst.SampleDesc.Quality = 0u;
  dst.Usage = D3D11_USAGE_DEFAULT;
  dst.BindFlags = D3D11_BIND_DEPTH_STENCIL;
  DXCALL(direct3d.m_pDevice->CreateTexture2D(&dst, nullptr, &m_pDepthStencilTexture))

  D3D11_DEPTH_STENCIL_VIEW_DESC dsv = {};
  dsv.Format =DXGI_FORMAT_D32_FLOAT;
  dsv.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
  dsv.Texture2D.MipSlice = 0u;
  direct3d.m_pDevice->CreateDepthStencilView(m_pDepthStencilTexture, &dsv ,&m_pDepthStencilView);


} 


void RenderOutput::changeViewPortHxW(u32 h, u32 w){
  
}
