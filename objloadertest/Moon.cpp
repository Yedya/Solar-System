#include "Moon.h"



Moon::Moon()
{
	// Initialize variables in default constructor
	angle = 0.0f;
	inc_Amount = 0.0f;
	scaler = vec3(0.0f, 0.0f, 0.0f);
	axis = vec3(0.0f, 0.0f, 0.0f);
	trans = vec3(0.0f, 0.0f, 0.0f);
	color = vec4(0.0f,0.0f,0.0f,0.0f);
}


Moon::Moon(float ang,float ang_Inc,vec3 scale,vec3 axis_1,vec3 trans_1,vec4 color_1)
{
	angle = ang;
	inc_Amount = ang_Inc;
	scaler = scale;
	axis = axis_1;
	trans = trans_1;
	color = color_1;
}


float Moon::getAngle() const
{

	return angle;
}
void Moon:: setAngle(float a)
{
	angle = a;
}

float Moon::getInct() const
{
	return inc_Amount;

}
void Moon::setInc(float Ia)
{

	inc_Amount = Ia;
}

vec3 Moon::getScale() const
{
	return scaler;
}
void Moon::setScale(vec3 sS)
{
	scaler = sS;
}

vec3 Moon::getAxis() const
{
	return axis;
}
void Moon::setAxis(vec3 A)
{
	axis = A;
}

vec3 Moon::getTrans() const
{
	return trans;	
}
void Moon::setTrans(vec3 T)
{
	trans = T;
}

vec4 Moon::getColor() const
{
	return color;
}
void Moon::setColor(vec4 cL) 
{
	color = cL;
}

