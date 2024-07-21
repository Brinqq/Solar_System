#pragma once
#include <windows.h>
#include "defines.h"

#include <d3d11.h>

class IDXGISwapChain;
class ID3D11RenderTargetView;
class Direct3D;
class D3D11_VIEWPORT;

class RenderOutput{
  private:
    ID3D11DepthStencilState* m_pDepthStencilState;
    ID3D11Texture2D* m_pDepthStencilTexture;
  public:
    ID3D11DepthStencilView* m_pDepthStencilView;
    IDXGISwapChain* m_pSwapChain;
    D3D11_VIEWPORT m_viewPort;
    ID3D11RenderTargetView* m_pRenderTarget;
    void newRenderTarget(Direct3D& direct3d, const HWND& outputWindowHandle); 
    void changeViewPortHxW(u32 h, u32 w);
    inline IDXGISwapChain* getSwapChain(){return m_pSwapChain;}
    inline ID3D11RenderTargetView* getRenderTarget(){return m_pRenderTarget;}
    inline const D3D11_VIEWPORT& getViewPort()const{return m_viewPort;}
};




