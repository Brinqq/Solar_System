struct ShaderInput{
  float3 pos : Position;
  float2 inTexCoord: TexCoord;
};

struct ShaderOutput{
  float2 outTexCoord :TexCoord;
  float4 outPos : SV_POSITION;
};

ShaderOutput main(ShaderInput input){
  ShaderOutput output;
  output.outPos = float4(input.pos, 1.0);
  output.outTexCoord = input.inTexCoord;
  return output;
}
