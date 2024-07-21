#include "planets.h"
#include "primitives.h"

#define M_PI 3.14159265359
#include <vector>
#include <cmath>

void generateSphere(float radius, int sectorCount, int stackCount, std::vector<Vertex>& vertices, std::vector<Indice>& triangles) {
    float x, y, z, xy;  // vertex position
    float sectorStep = 2 * M_PI / sectorCount;
    float stackStep = M_PI / stackCount;
    float sectorAngle, stackAngle;

    // generate vertices
    for (int i = 0; i <= stackCount; ++i) {
        stackAngle = M_PI / 2 - i * stackStep;  // from pi/2 to -pi/2
        xy = radius * cosf(stackAngle);        // r * cos(u)
        z = radius * sinf(stackAngle);         // r * sin(u)

        for (int j = 0; j <= sectorCount; ++j) {
            sectorAngle = j * sectorStep;  // from 0 to 2pi

            // vertex position (x, y, z)
            x = xy * cosf(sectorAngle);    // r * cos(u) * cos(v)
            y = xy * sinf(sectorAngle);    // r * cos(u) * sin(v)
            vertices.push_back({x, y, z});
        }
    }

    // generate triangles
    for (u16 i = 0; i < stackCount; ++i) {
        u16 k1 = i * (sectorCount + 1);     // beginning of current stack
        u16 k2 = k1 + sectorCount + 1;      // beginning of next stack

        for (u16 j = 0; j < sectorCount; ++j, ++k1, ++k2) {
            // 2 triangles per sector excluding first and last stacks
            if (i != 0) {
                triangles.push_back({k1, k2, u16(k1 + 1)}); // First triangle
            }

            if (i != (stackCount - 1)) {
                triangles.push_back({u16(k1 + 1), k2, u16(k2 + 1)}); // Second triangle
            }
        }
    }
}

