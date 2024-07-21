#pragma once
#include "global.h"
#include "defines.h"

struct Vertex;
struct Indice;

void generateSphere(float radius, int sectorCount, int stackCount, std::vector<Vertex>& vertices, std::vector<Indice>& triangles);
