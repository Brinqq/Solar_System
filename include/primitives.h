#pragma once
#include "defines.h"

template<typename T>
struct Vector3{
  T x, y, z;
};

struct Vector3f{
  f32 x, y, z;
};


struct ColorRGB{
  float r, g, b;
};


struct VertexT{
  f32 x,y,z, u, v;
};

struct Vertex{
  f32 x,y,z;
};

struct Indice{
  u16 x,y,z;
};
