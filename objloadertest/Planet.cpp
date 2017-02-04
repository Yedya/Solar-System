#include "Planet.h"
//#include "objloadertest.cpp"

Planet::Planet() // Default constructors initialize  planets attributes
{
	angle = 0.0f;
	inc = 0.0f;
	scaler = vec3(0.0f, 0.0f, 0.0f);
	axis = vec3(0.0f, 0.0f, 0.0f);
	trans = vec3(0.0f, 0.0f, 0.0f);
	color = vec4(0.0f,0.0f,0.0f,0.0f);
}

Planet::Planet(float ang, float inc_Amount, vec3 scale_, vec3 rot_, vec3 trans_,vec4 color_) // Pass in instansiated objects values via objectloader.cpp
{
	angle = ang;
	inc = inc_Amount;
	scaler = scale_;
	axis = rot_;
	color = color_;
	trans = trans_;
}

// Setters & Getters

void Planet:: setAngle(float a)
{
	angle = a;
}
float Planet:: getAngle() const
{
	return angle;
}


void Planet:: setInc(float b)
{
	inc = b;
}
float Planet:: getInc() const
{
	return inc;
}


void Planet:: setScale(vec3 r)
{
	scaler = r;
}
vec3 Planet:: getScale() const
{
	return scaler;
}


void Planet:: setAxis(vec3 r)
{
	axis = r;
}
vec3 Planet:: getAxis() const
{
	return axis;
}


void Planet:: setTranslate(vec3 t) 
{
	trans = t;
}
vec3 Planet:: getTranslate() const
{
	return trans;
}


void Planet::setColor(vec4 c)
{
	color = c;
}
vec4 Planet::getColor() const
{

	return color;
}