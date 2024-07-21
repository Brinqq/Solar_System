#include "dx_shader.h"
#include "d3d_err.h"
#include "direct3d.h"
#include "mesh.h"

#include <array>
#include <d3dcompiler.h>


void DirectShaderObject::initShaders(const Direct3D& direct3d, const wchar_t* vsPath, const wchar_t* psPath){
  DXCALL(D3DReadFileToBlob(vsPath, &m_pVsBlob))
  DXCALL(D3DReadFileToBlob(psPath, &m_pPsBlob))
  DXCALL(direct3d.getDeviceObj()->CreateVertexShader(m_pVsBlob->GetBufferPointer(), m_pVsBlob->GetBufferSize(), nullptr, &m_pVertexShader))
  DXCALL(direct3d.getDeviceObj()->CreatePixelShader(m_pPsBlob->GetBufferPointer(), m_pPsBlob->GetBufferSize(), nullptr, &m_pPixelShader))
}


DirectShaderObject::~DirectShaderObject(){
  if(m_pPsBlob != nullptr){m_pPsBlob->Release();};
  if(m_pVsBlob != nullptr){m_pVsBlob->Release();};
  if(m_pVertexShader != nullptr){m_pVertexShader->Release();};
  if(m_pPixelShader != nullptr){m_pPsBlob->Release();};
}

void DirectShaderObject::inputLayerTest(){
  // m_inputData.m_index = 0;
//   char tmp[] = "Position";
//   m_inputData.m_pSemanticName = tmp;
//   m_ied = { m_inputData.m_pSemanticName, m_inputData.m_index, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0};
}


void DirectShaderObject::bindInputLayoutToShader(const Direct3D& direct3d, const std::vector<ShaderInputLayout>& dataInputs){
  int numElements = dataInputs.size();
  D3D11_INPUT_ELEMENT_DESC* ied = new D3D11_INPUT_ELEMENT_DESC[numElements];
  u16 index = 0;
  for(ShaderInputLayout value: dataInputs){
    if(value.m_format == DATA_FORMAT_FLOAT3D){
      ied[index] = {value.semanticName, value.semanticeIndex, DXGI_FORMAT_R32G32B32_FLOAT, index, value.byteOffset, D3D11_INPUT_PER_VERTEX_DATA, 0};
    }
    if(value.m_format == DATA_FORMAT_FLOAT2D){
      ied[index] = {value.semanticName, value.semanticeIndex, DXGI_FORMAT_R32G32_FLOAT, 0, value.byteOffset, D3D11_INPUT_PER_VERTEX_DATA, 0};
    }
    index++;
  } 
  DXCALL(direct3d.m_pDevice->CreateInputLayout(ied, index, m_pVsBlob->GetBufferPointer(), m_pVsBlob->GetBufferSize(), &m_pInputLayout))
  delete[] ied;
}

void DirectShaderObject::bindInputDataToShader(const Direct3D& direct3d){
  D3D11_INPUT_ELEMENT_DESC ied[] = { "Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0};
  direct3d.m_pDevice->CreateInputLayout(ied, (u32)std::size(ied), m_pVsBlob->GetBufferPointer(), m_pVsBlob->GetBufferSize(), &m_pInputLayout);
}

