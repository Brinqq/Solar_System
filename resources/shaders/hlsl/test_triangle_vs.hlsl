
cbuffer TransformCBuffer{
  Matrix transform;
}


struct VS_OUTPUT{
  float4 outPosition : SV_POSITION;
};

VS_OUTPUT main(float3 pos : Position){
  VS_OUTPUT ret;
  ret.outPosition = mul(float4(pos.x, pos.y, pos.z, 1.0f), transform);
  return ret;
}
