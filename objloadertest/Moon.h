#ifndef MOON_H
#define MOON_H

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <Windows.h>
#include <iostream>
using namespace std;
using namespace glm;



class Moon
{


private:
	float angle; // angle
	float inc_Amount; // increment
	vec3 scaler; // scales each object class
	vec3 axis; // axis which object resides
	vec3 trans; // translation
	vec4 color; // color


public:

	Moon();
	Moon(float,float,vec3,vec3,vec3,vec4);


	float getAngle() const;
	void setAngle(float a);

	float getInct() const;
	void setInc(float Ia);

	vec3 getScale() const;
	void setScale(vec3 sS);

	vec3 getAxis() const;
	void setAxis(vec3 A);

	vec3 getTrans() const;
	void setTrans (vec3 T);


	vec4 getColor() const;
	void setColor(vec4 cL);


};


#endif 
