#include "dx_texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "d3d_err.h"

#include <d3d11.h>
                         
//TODO:: optimize as soon as possible
void DirectTexture::newResourceViewFromFile(ID3D11Device& device, const char* pPath){
  ID3D11Texture2D* pTexture = nullptr;
  m_pImageData = stbi_load(pPath, &m_surface.imageWidth, &m_surface.imageHeight, &m_surface.imageChannels, m_surface.imageDesiredChannels);
  assert(m_pImageData);
  m_surface.imagePitch = m_surface.imageWidth * 4;
  D3D11_TEXTURE2D_DESC td = {};
  D3D11_SUBRESOURCE_DATA sd = {};
  td.Width = m_surface.imageWidth;
  td.Height = m_surface.imageHeight;
  td.MipLevels = 1;
  td.ArraySize = 1;
  td.SampleDesc.Count = 1;
  td.SampleDesc.Quality = 0;
  td.CPUAccessFlags = 0;
  td.Usage =  D3D11_USAGE_IMMUTABLE;
  td.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
  td.BindFlags = D3D11_BIND_SHADER_RESOURCE;
  sd.pSysMem = m_pImageData;
  sd.SysMemPitch = m_surface.imagePitch; 
  DXCALL(device.CreateTexture2D(&td, &sd, &pTexture))
  D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
  srvDesc.Format = td.Format;
  srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
  srvDesc.Texture2D.MostDetailedMip = 0;
  srvDesc.Texture2D.MipLevels = 1;
  DXCALL(device.CreateShaderResourceView(pTexture, NULL, &m_pResourceView))
  pTexture->Release();
}

