Texture2D tex;


SamplerState samplerState : SAMPLER : register(s0);

float4 main(float2 inTexCoord : TexCoord):SV_TARGET{
  //return float4(0.0, 0.0, 0.2, 1.0);
  return tex.Sample(samplerState, inTexCoord);
}
