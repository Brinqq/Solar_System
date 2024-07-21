#include "camera.h"

#include <DirectXMath.h>

Camera::Camera(){
  initProjectionMatrix(1920,1080);
  updateViewMatrix();
}

Camera::~Camera(){

}

void Camera::updateViewMatrix(){
  cameraPos = DirectX::XMVectorSet(pos.x,pos.y,pos.z,0.0f);
  rotationMatrix = DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll);
  DirectX::XMVECTOR cameraTarget = DirectX::XMVector3TransformCoord(forwardVector, rotationMatrix);
  cameraTarget = DirectX::XMVectorAdd(cameraTarget, cameraPos);
  viewMatrix =  DirectX::XMMatrixLookAtLH(
    cameraPos,
    cameraTarget,
    DirectX::XMVector3TransformCoord(upVector, rotationMatrix));
    

}

void Camera::initProjectionMatrix(float windowH, float windowW){
  aspectRatio = windowW/windowH;
  projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(fov, aspectRatio, nearZ, farZ);
}

void Camera::setCameraPos(f32 x, f32 y, f32 z, f32 direction){
  pos.x += x * direction;
  pos.y += y * direction;
  pos.z += z * direction;
  updateViewMatrix();
}

const u32 roll = 0.0f;
f32 cameraX = 0.0f;
f32 cameraZ = -1.0f;
f32 cameraY = 0.0f;
f32 positionModifier = 0.4;



const DirectX::XMVECTOR defaultUpPos = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
const DirectX::XMVECTOR defaultForwardPos = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);


DirectX::XMMATRIX viewMatrix;
DirectX::XMVECTOR cameraPos = {0.0f, 0.0f, 0.0f};
DirectX::XMMATRIX rotationMatrix;

f32 yaw = 0.0; 
f32 pitch = 0.0;

void updateCameraZ(f32 x){cameraZ += positionModifier * x;}
void updateCameraX(f32 x){cameraX += positionModifier * x;}
void updateCameraY(f32 x){cameraY += positionModifier * x;}


DirectX::XMMATRIX testCam(){
  cameraPos = DirectX::XMVectorSet(cameraX, cameraY, cameraZ, 0.0f);
  rotationMatrix = DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll);
  DirectX::XMVECTOR cameraTarget = DirectX::XMVector3TransformCoord(defaultForwardPos, rotationMatrix);
  cameraTarget = DirectX::XMVectorAdd(cameraTarget, cameraPos);
  viewMatrix =  DirectX::XMMatrixLookAtLH(
    cameraPos,
    cameraTarget,
    DirectX::XMVector3TransformCoord(defaultUpPos, rotationMatrix));
    
    return viewMatrix;
}
