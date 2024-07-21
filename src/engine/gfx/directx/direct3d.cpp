#include "direct3d.h"
#include "window.h"

//tmp
#include "dx_texture.h"
#include "primitives.h"
#include "dx_renderouput.h"
#include "d3d_err.h"

#include <DirectXMath.h>
#include <d3d11.h>

struct DirectRenderStateObject {
  DirectBufferObject ibo;
  DirectBufferObject vbo;
  std::vector<DirectCBuffer> cBuffers;
  DirectShaderObject shader;
  DirectTexture texture;
  u8 needsTexture;
};

struct RasterizerStates{
  ID3D11RasterizerState* m_default;
  ID3D11RasterizerState* m_wireFrame;
};

ID3D11RasterizerState* wireFrameState;
RasterizerStates rasterizerStates;
RendererRasterizerState rrs;
RendererRasterizerState crrs;

static u32 renderObjectCount = 0;

void initRasterizerStates(ID3D11Device& device, RasterizerStates& rs){
  D3D11_RASTERIZER_DESC ds;
  ds.CullMode = D3D11_CULL_NONE;
  ds.FillMode = D3D11_FILL_WIREFRAME;
  ds.FrontCounterClockwise = FALSE;
  ds.DepthBias = 0;
  ds.SlopeScaledDepthBias = 0;
  ds.DepthBiasClamp = 0.0f;
  ds.DepthClipEnable = TRUE;
  ds.ScissorEnable = FALSE;
  ds.MultisampleEnable = FALSE;
  ds.AntialiasedLineEnable = FALSE;
  DXCALL(device.CreateRasterizerState(&ds, &rs.m_wireFrame))
  ds.CullMode = D3D11_CULL_BACK;
  ds.FillMode =  D3D11_FILL_SOLID;
  DXCALL(device.CreateRasterizerState(&ds, &rs.m_default))
}

ID3D11SamplerState* sa;
void initSampler(ID3D11Device& device, ID3D11SamplerState* sampler){
  D3D11_SAMPLER_DESC sad = {};
  sad.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
  sad.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
  sad.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
  sad.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
  DXCALL(device.CreateSamplerState(&sad, &sa))
}

Direct3D::Direct3D(const Window& window){
  m_windowHandle = window.getHwnd();
  m_mainRenderOutput.newRenderTarget(*this, m_windowHandle);
  m_debug = DXDebug(m_pDevice);
  m_debug.init();
  m_pContext->RSSetViewports(1, &m_mainRenderOutput.m_viewPort);
  m_pContext->OMSetRenderTargets(1u, &m_mainRenderOutput.m_pRenderTarget, m_mainRenderOutput.m_pDepthStencilView);
  // m_pContext->OMSetRenderTargets(1u, &m_mainRenderOutput.m_pRenderTarget, nullptr);
  m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
  initRasterizerStates(*this->m_pDevice, rasterizerStates);
  initSampler(*m_pDevice, m_samplerState);
}

void Direct3D::testUpdate(){
    m_pContext->ClearRenderTargetView(m_mainRenderOutput.getRenderTarget(), bgColor);
    m_pContext->ClearDepthStencilView(m_mainRenderOutput.m_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0u);
    for(auto value: m_renderObjects){
      bindRenderObject(*value.second);
      draw(value.second->ibo.m_indiceCount);
    };

    if(crrs != rrs){
      if(rrs == RS_WIREFRAME){
          m_pContext->RSSetState(rasterizerStates.m_wireFrame);
        }else{
          m_pContext->RSSetState(rasterizerStates.m_default);
      }
      crrs = rrs;
    }

    m_mainRenderOutput.getSwapChain()->Present(1, 0);
}

ColorCBuffer col = {0.20f, 0.00f, 0.30f};



void Direct3D::draw(u32 indices){
  DXINFO(m_pContext->DrawIndexed(indices,0,0));
}

ID3D11Buffer* testBuffer;
void Direct3D::bindRenderObject(const DirectRenderStateObject& renderObject){
    m_pContext->IASetVertexBuffers(0, 1, &renderObject.vbo.m_pBuffer, &renderObject.vbo.m_stride, &renderObject.vbo.m_offset);
    m_pContext->IASetIndexBuffer(renderObject.ibo.m_pBuffer, DXGI_FORMAT_R16_UINT, renderObject.ibo.m_offset);
    m_pContext->VSSetShader(renderObject.shader.m_pVertexShader, nullptr, 0);
    m_pContext->PSSetShader(renderObject.shader.m_pPixelShader, nullptr, 0);
    m_pContext->IASetInputLayout(renderObject.shader.m_pInputLayout);

    if(renderObject.needsTexture == 1){
      DXINFO(m_pContext->PSSetShaderResources(0, 1, &renderObject.texture.m_pResourceView))
      DXINFO(m_pContext->PSSetSamplers(0, 1, &sa))
    }

    for(DirectCBuffer cb : renderObject.cBuffers){
      if(cb.m_shaderDest == CONSTANT_BUFFER_PS){
        m_pContext->PSSetConstantBuffers(0, 1, &cb.m_pBuffer);
        continue;
      }

      m_pContext->VSSetConstantBuffers(0, 1, &cb.m_pBuffer);
    }

}

void Direct3D::test(DirectX::XMMATRIX mat){
  D3D11_MAPPED_SUBRESOURCE sr;
  ZeroMemory(&sr, sizeof(D3D11_MAPPED_SUBRESOURCE));
  m_pContext->Map(m_renderObjects[0]->cBuffers[1].m_pBuffer, 0 , D3D11_MAP_WRITE_DISCARD,0, &sr);
  memcpy(sr.pData, &mat, sizeof(DirectX::XMMATRIX));
  m_pContext->Unmap(m_renderObjects[0]->cBuffers[1].m_pBuffer, 0);
  
}

DirectCBuffer n(ID3D11Device* device, void* data, const u32 byteSize, const ConstantBufferDest cbd){
  DirectCBuffer cBuffer = {nullptr, cbd};
  ID3D11Buffer* pBuffer = (ID3D11Buffer*)malloc(sizeof(ID3D11Buffer));
  D3D11_BUFFER_DESC bd;
  D3D11_SUBRESOURCE_DATA sd;
  bd.Usage = D3D11_USAGE_DYNAMIC;
  bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
  bd.MiscFlags = 0;
  bd.ByteWidth = byteSize;
  bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
  bd.StructureByteStride = 0;
  sd.pSysMem = data;
  DXCALL(device->CreateBuffer(&bd, &sd, &pBuffer))
  cBuffer.m_pBuffer = pBuffer;
  return cBuffer; 
}

u32 Direct3D::newRenderObject(Mesh& mesh){
  DirectRenderStateObject* renderObject = new DirectRenderStateObject;
  if(mesh.requiresTexture){
    renderObject->vbo.initAsVertexBufferWithTexture(*this, *mesh.m_verticesT);
    renderObject->texture.newResourceViewFromFile(*m_pDevice, "C:/main/dev/projects/solar-system/resources/textures/test.jpg");
    renderObject->needsTexture = 1;
  }else{
    renderObject->vbo.initAsVertexBuffer(*this, *mesh.m_vertices);
}
  renderObject->ibo.initAsIndexBuffer(*this, *mesh.m_indices);
  renderObject->shader.initShaders(*this, mesh.m_vsPath, mesh.m_psPath);
  renderObject->shader.bindInputLayoutToShader(*this, mesh.m_shaderInputs);
  // renderObject->cBuffers.emplace_back(newCBuffer(this->m_pDevice, &col, 16, CONSTANT_BUFFER_PS));
  for(ConstantBuffer& cb : mesh.m_constantBuffers){
    renderObject->cBuffers.emplace_back(newCBuffer(this->m_pDevice, cb));
  }
  u32 id = renderObjectCount;
  m_renderObjects.insert({id, renderObject});
  renderObjectCount++;
  return id;
}


void Direct3D::switchRasterizerState(RendererRasterizerState rss){
  rrs = rss;
}
