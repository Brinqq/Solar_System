#include "global.h"
#include "d3d_err.h"
#include "d3dref.h"
#include "window.h"
#include "error.h"
#include "primitives.h"

#include <d3dcommon.h>
#include <windows.h>
#include <d3dcompiler.h>
#include <d3d11.h>
#include <DirectXMath.h>


// float angle = 20.0f;
// struct ConstantBuffer{
//   DirectX::XMMATRIX transform;
// };
//
//
// struct Triangle{
//
//   const std::vector<Vertex> square = {
//   {-0.5f, -0.5f, -0.5f},  // Vertex 0
//   {0.5f, -0.5f, -0.5f},   // Vertex 1
//   {0.5f, 0.5f, -0.5f},    // Vertex 2
//   {-0.5f, 0.5f, -0.5f},   // Vertex 3
//   {-0.5f, -0.5f, 0.5f},   // Vertex 4
//   {0.5f, -0.5f, 0.5f},    // Vertex 5
//   {0.5f, 0.5f, 0.5f},     // Vertex 6
//   {-0.5f, 0.5f, 0.5f}     // Vertex 7
// };
//
//
// std::vector<Indice> indicesVec = {
//   {0, 2, 1}, {0, 3, 2},
//   {1, 6, 5}, {1, 2, 6},
//   {5, 7, 4}, {5, 6, 7},
//   {4, 3, 0}, {4, 7, 3},
//   {3, 6, 2}, {3, 7, 6},
//   {4, 1, 5}, {4, 0, 1}
//   };
//
//   const float vertices[24] = {
//     -0.5f, -0.5f, -0.5f,  // Vertex 0
//     0.5f, -0.5f, -0.5f,   // Vertex 1
//     0.5f, 0.5f, -0.5f,    // Vertex 2
//     -0.5f, 0.5f, -0.5f,   // Vertex 3
//     -0.5f, -0.5f, 0.5f,   // Vertex 4
//     0.5f, -0.5f, 0.5f,    // Vertex 5
//     0.5f, 0.5f, 0.5f,     // Vertex 6
//     -0.5f, 0.5f, 0.5f     // Vertex 7
// };
//
//   const unsigned short indices[36] = {
//     0, 2, 1, 0, 3, 2,
//     1, 6, 5, 1, 2, 6,
//     5, 7, 4, 5, 6, 7,
//     4, 3, 0, 4, 7, 3,
//     3, 6, 2, 3, 7, 6,
//     4, 1, 5, 4, 0, 1
//   };
//
//   ID3D11Buffer* pVertexBuffer;
//   ID3D11Buffer* pConstantBuffer = nullptr;
//   ID3D11Buffer* pIndexBuffer;
//   ID3D11VertexShader* pVertexShader;
//   ID3D11PixelShader* pPixelShader;
//   ID3D11InputLayout* pInputLayout;
//
// };
//
//
// ID3D11Device* pDevice = nullptr;
// ID3D11DeviceContext* pContext = nullptr;
// IDXGISwapChain* pSwapChain = nullptr;
// ID3D11RenderTargetView* pRenderTarget = nullptr;
// Window* pWindowInstance;
// DXError* pErrors;
// Triangle tri;
// D3D11_VIEWPORT vp;
// DXDebug debug(pDevice);
//
//
// const float bgColor[4] = {0.0f, 0.1f, 0.1f, 1.0f};
//
// void initInputData(){
// }
//
// void initOM(){
//   vp.Width = 1920;
//   vp.Height = 1080;
//   vp.MinDepth = 0;
//   vp.MaxDepth = 1;
//   vp.TopLeftX = 0;
//   vp.TopLeftY = 0;
//   pContext->RSSetViewports(1, &vp);
//   pContext->OMSetRenderTargets(1u,&pRenderTarget,nullptr);
// }
//
// void createShaders(){
// const D3D11_INPUT_ELEMENT_DESC ied[] = {
// {"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}, 
//   };
//   ID3DBlob* pBlob;
//   DXCALL(D3DReadFileToBlob(L"bin/shaders/test_triangle_ps.cso", &pBlob))
// DXCALL(pDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &tri.pPixelShader))
//   pBlob->Release();
//   DXCALL(D3DReadFileToBlob(L"bin/shaders/test_triangle_vs.cso", &pBlob))
//   DXCALL(pDevice->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &tri.pVertexShader))
//   pContext->PSSetShader(tri.pPixelShader, nullptr, 0);
//   pContext->VSSetShader(tri.pVertexShader, nullptr, 0);
//   DXCALL(pDevice->CreateInputLayout(ied,(unsigned int)std::size(ied), pBlob->GetBufferPointer(),pBlob->GetBufferSize(), &tri.pInputLayout))
// }
//
// void createIndexArray(){
//   D3D11_BUFFER_DESC bd;
//   D3D11_SUBRESOURCE_DATA sd;
//   bd.ByteWidth = sizeof(Indice)*tri.indicesVec.size();
//   bd.Usage = D3D11_USAGE_DEFAULT;
//   bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
//   bd.CPUAccessFlags = 0;
//   bd.MiscFlags = 0;
//   bd.StructureByteStride = sizeof(unsigned short);
//   sd.pSysMem = &tri.indicesVec[0];
//   DXCALL(pDevice->CreateBuffer(&bd, &sd, &tri.pIndexBuffer))
//   pContext->IASetIndexBuffer(tri.pIndexBuffer,DXGI_FORMAT_R16_UINT,0);
// }
//
// void createConstantBuffer(){
//   if(angle > 10){angle = 0.01;};
//   angle += 0.01;
//   const ConstantBuffer cBuffer = {
//     {
//       DirectX::XMMatrixTranspose(
//           DirectX::XMMatrixRotationZ(angle)*
//           DirectX::XMMatrixRotationX(angle)*
//           DirectX::XMMatrixScaling(3.0f/4.0f,1.0f,1.0f)*
//           DirectX::XMMatrixTranslation(0, 0, 3.0f)*
//           DirectX::XMMatrixPerspectiveLH(1.0, 3.0 / 4.0, 1.0f, 10.0f)
//       )
//     }
//   };
//
//   D3D11_BUFFER_DESC bd;
//   D3D11_SUBRESOURCE_DATA sd;
//   bd.BindFlags =D3D11_BIND_CONSTANT_BUFFER;
//   bd.Usage = D3D11_USAGE_DYNAMIC;
//   bd.MiscFlags = 0;
//   bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
//   bd.StructureByteStride = 0;
//   bd.ByteWidth = sizeof(cBuffer);
//   sd.pSysMem = &cBuffer;
//   DXCALL(pDevice->CreateBuffer(&bd, &sd, &tri.pConstantBuffer))
//   pContext->VSSetConstantBuffers(0,1,&tri.pConstantBuffer);
// }
//
//
// void createVertexArray(){
//   D3D11_BUFFER_DESC bd = {};
//   D3D11_SUBRESOURCE_DATA sd = {};
//   bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
//   bd.Usage = D3D11_USAGE_DEFAULT;
//   bd.CPUAccessFlags = 0;
//   bd.MiscFlags = 0;
//   bd.ByteWidth = sizeof(Vertex)*tri.square.size();
//   bd.StructureByteStride = sizeof(Vertex);
//   sd.pSysMem = &tri.square[0];
//   unsigned int stride = sizeof(float)*3;
//   unsigned int offset = 0;
//   DXCALL(pDevice->CreateBuffer(&bd,&sd,&tri.pVertexBuffer))
//   pContext->IASetVertexBuffers(0, 1, &tri.pVertexBuffer, &stride, &offset);
// }
//
// void initRenderTarget(){
//   ID3D11Resource* a = nullptr;
//   DXCALL(pSwapChain->GetBuffer(0,_uuidof(a),reinterpret_cast<void**>(&a)))
//   DXCALL(pDevice->CreateRenderTargetView(a,nullptr,&pRenderTarget))
//   a->Release();
// }
//
//
//
// void initSwapChainAndDevice(){
//   DXGI_SWAP_CHAIN_DESC sd;
//   sd.BufferDesc.Height = 0;
//   sd.BufferDesc.Width = 0;
//   sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
//   sd.BufferDesc.RefreshRate.Numerator = 0;
//   sd.BufferDesc.RefreshRate.Denominator = 0;
//   sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
//   sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
//   sd.SampleDesc.Count = 1;
//   sd.SampleDesc.Quality = 0;
//   sd.BufferCount = 1;
//   sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
//   sd.OutputWindow = pWindowInstance->getHwnd();
//   sd.Windowed = true;
//   sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
//   sd.Flags = 0;
//   DXCALL(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, D3D11_CREATE_DEVICE_DEBUG, nullptr, 0, D3D11_SDK_VERSION, &sd, &pSwapChain, &pDevice, nullptr, &pContext));
// }
//
// void initTriangle(){
//   pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
//   initOM();
//   createVertexArray();
//   createIndexArray();
//   createShaders();
//   pContext->IASetInputLayout(tri.pInputLayout);
//   initInputData();
// }
//
//
//  void d3dTest(Window* pWindow){
//   pWindowInstance = pWindow;
//   initSwapChainAndDevice();
//   setDeviceDXErrors(*pDevice);
//   initRenderTarget();
//   initTriangle();
// }
//
//
//
// void d3dUpdate(){
//   createConstantBuffer();
//   pContext->ClearRenderTargetView(pRenderTarget, bgColor);
//   pContext->DrawIndexed(sizeof(Indice)*tri.indicesVec.size(),0 ,0);
//   pSwapChain->Present(1, 0u);
//   tri.pConstantBuffer->Release();
// }
//
// void cleanup(){
//   free(pErrors);
// }
//
//
//
//
