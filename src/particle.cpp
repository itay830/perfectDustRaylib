#include <iostream>
#include <math.h>
#include "headers/particle.h"

void attraction(Particle &p, float attractionFactor, int xBorder, int yBorder)
{
	Vector2 mousePos = GetMousePosition();
	float dist = std::sqrt((p.pos.x - mousePos.x) * (p.pos.x - mousePos.x) + (p.pos.y - mousePos.y) * (p.pos.y - mousePos.y));
	if (dist < 0.5)
	{
		dist = 0.5;
	}
	Vector2 acc = Vector2{
		(p.pos.x - mousePos.x) / (dist * dist) * attractionFactor,
		(p.pos.y - mousePos.y) / (dist * dist) * attractionFactor};
	p.vel.x -= acc.x;
	p.vel.y -= acc.y;
	p.pos.x += p.vel.x;
	p.pos.y += p.vel.y;
	if (p.pos.x > xBorder || p.pos.x < 0)
	{
		p.vel.x *= -1;
	}
	if (p.pos.y < 0 || p.pos.y > yBorder)
	{
		p.vel.y *= -1;
	}

	float t = dist / std::sqrt(xBorder * xBorder + yBorder * yBorder);
	p.color = Color{
		(30 * (1 - t) * (1 - t) * t * 255),
		(16 * (1 - t) * t * t * 255),
		(40 * (1 - t) * (1 - t) * t * 255),
		255};
}
