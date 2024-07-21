#pragma once
#include "global.h"
#include "defines.h"
#include "primitives.h"

#include "DirectXMath.h"

class Camera{
    const DirectX::XMVECTOR upVector = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
    const DirectX::XMVECTOR forwardVector = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
    Vector3f pos = {0.0,0.0,0.0};
    DirectX::XMVECTOR cameraPos = {0.0f, 0.0f, 0.0f, 0.0f};
    DirectX::XMMATRIX rotationMatrix;
    DirectX::XMVECTOR positionVector;
    DirectX::XMFLOAT3 rotationVector;
    const f32 roll = 0.0f;
    f32 yaw = 0.0; 
    f32 pitch = 0.0;
    const f32 nearZ = 0.5f;
    const f32 farZ = 100.0f;
    f32 fov = 90.0f;
    f32 aspectRatio;
    void updateViewMatrix();
    void initProjectionMatrix(float windowH, float windowW);
      // DirectX::XMMatrixPerspectiveLH(1.0f, 3.0/4.0, 0.5f, 20.0f)
  public:
    DirectX::XMMATRIX viewMatrix;
    DirectX::XMMATRIX projectionMatrix;
    Camera();
    ~Camera();
    void test(float x, float y);
    void updateRotation(f32 yaw, f32 pitch);
    void windowSizeCallBack(float windowH, float windowW){aspectRatio = windowH/windowW;};
    void setCameraPos(f32 x, f32 y, f32 z, f32 direction);
};

DirectX::XMMATRIX testCam();
void updateCameraZ(f32 x);
void updateCameraX(f32 x);
void updateCameraY(f32 x);
