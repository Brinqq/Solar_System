#pragma once
#include "global.h"
#include "defines.h"


#include <d3d11.h>

class ID3D11PixelShader;
class ID3D11VertexShader;
class Direct3D;
struct ShaderInputLayout;


struct DirectInputDesc{
  char* m_pSemanticName;
  u32 m_index;
  u32 m_offset = 0;
};



class DirectShaderObject{
  private:
    ID3DBlob* m_pPsBlob = nullptr;
    ID3DBlob* m_pVsBlob = nullptr;
    DirectInputDesc m_inputData;
    D3D11_INPUT_ELEMENT_DESC m_ied;
    
  public:
    ID3D11InputLayout* m_pInputLayout = nullptr;
    ID3D11PixelShader* m_pPixelShader = nullptr;
    ID3D11VertexShader* m_pVertexShader = nullptr;
    DirectShaderObject() = default;
    void initShaders(const Direct3D& direcet3d, const wchar_t* vsPath, const wchar_t* psPath);
    void inputLayerTest();
    void bindInputDataToShader(const Direct3D& direct3d);
    void bindInputLayoutToShader(const Direct3D& direct3d, const std::vector<ShaderInputLayout>& dataInputs);
    ~DirectShaderObject();
  
};
