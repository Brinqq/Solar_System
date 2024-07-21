cbuffer colorBuf{
  float r;
  float g;
  float b;
}

float4 main() : SV_TARGET {
  return float4(r, g, b, 1.0f);
}
