#pragma once
#include "solid.h"
class Cuboid : public Solid
{
private:
	float height;											// Dimensi�n en el eje y
	float length;											// Dimensi�n en el eje x
	float width;											// Dimensi�n en el eje z
public:
	Cuboid() : Solid(), height(1.0f), length(2.0f), width(0.5f) {}
	/* Metodos de acceso */
	inline float getHeight() const { return this->height; }
	inline void setHeight(const float& heightToSet) { this->height = heightToSet; }
	inline float getLength() const { return this->length; }
	inline void setLength(const float& lengthToSet) { this->length = lengthToSet; }
	inline float getWidth() const { return this->width; }
	inline void setWidth(const float& widthToSet) { this->width = widthToSet; }

	void render();
};

