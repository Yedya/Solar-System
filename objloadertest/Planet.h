#ifndef PLANET_H
#define PLANET_H

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <Windows.h>
#include <iostream>
using namespace std;
using namespace glm;

class Planet
{
private:
	float angle; // angle
	float inc; // increment
	vec3 scaler; // scales each object class
	vec3 axis; // axis which object resides
	vec3 trans; // translation
	vec4 color; // color

public: 
	Planet(); // default constructor 
	Planet(float, float, vec3, vec3, vec3,vec4);

	// setter & getter method declarations
	void setAngle(float a);
	float getAngle() const;

	void setInc(float b);
	float getInc() const;
	

	void setScale(vec3 s);
	vec3 getScale() const;

	void setAxis(vec3 r);
	vec3 getAxis() const;

	void setTranslate(vec3 t);
	vec3 getTranslate() const;

	void incAngle(float a);

	void setColor(vec4 c);
	vec4 getColor()const;

};

#endif //PLANET_H