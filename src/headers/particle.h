#pragma once
#include <raylib.h>

struct Particle {
  Vector2 pos;
  Vector2 vel;
  Color color;
};

void attraction(Particle &p, float attractionFactor, int xBorder, int yBorder);
