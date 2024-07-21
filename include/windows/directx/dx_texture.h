#pragma once
#include "global.h"
#include "defines.h"

#include <d3d11.h>

struct TextureSurface{
  i32 imageWidth;
  i32 imageHeight;
  i32 imageChannels;
  i32 imageDesiredChannels = 4;
  i32 imagePitch;
};

class DirectTexture{
  private:
    TextureSurface m_surface;
    char* m_pPath;
    u8* m_pImageData;
  public:
  ID3D11ShaderResourceView* m_pResourceView;
    DirectTexture(const DirectTexture& other) = delete;
    DirectTexture() = default;
    ~DirectTexture(){}
    void newResourceViewFromFile(ID3D11Device& device, const char* pPath);
};

ID3D11Texture2D* v(ID3D11Device& device);
