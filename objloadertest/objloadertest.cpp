#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Windows.h>
#include <string>
#include "aitmesh.h"
#include "Planet.h"
#include "Moon.h"
using namespace std;
using namespace glm;

const int windowWidth = 1024; 
const int windowHeight = 768;

GLuint VBO;
int NUMVERTS = 0;

// Transform uniforms location
GLuint gModelToWorldTransformLoc;
GLuint gWorldToViewToProjectionTransformLoc;

// Lighting uniforms location
GLuint gAmbientLightIntensityLoc;
GLuint gDirectionalLightIntensityLoc;
GLuint gDirectionalLightDirectionLoc;

// Materials uniform location
GLuint gKaLoc;
GLuint gKdLoc;
GLuint gColorLoc; // GLuint for color


 // original angle float, increment of angle float, scale, rotation & translation vec3s + colors vec4s
Planet sun(0.0f, 0.01f, vec3(2.0f,2.0f,2.0f), vec3(0.0f,0.0f,0.0f), vec3(0.0f,1.0f,0.0f),vec4(1.0f,1.0f,0.0f,0.0f));
Planet Mercury (0.0f, 0.080f, vec3(0.6f,0.6f,0.6f), vec3(0.0f,10.0f,0.0f), vec3(4.0f,1.0f,0.0f),vec4(0.5f, 0.35f, 0.05f,0.0f));  // brown

Planet Venus (0.0f, 0.070f, vec3(0.9f,0.9f,0.9f), vec3(0.0f,10.0f,0.0f), vec3(5.8f,1.0f,0.0f),vec4(1.0f,0.35f,0.05f,0.0f)); // orangey
Planet Earth (0.0f, 0.065f, vec3(0.8f,0.8f,0.8f), vec3(0.0f,10.0f,0.0f), vec3(7.8f,1.0f,0.0f),vec4(0.0f,0.0f,1.0f,0.0f));  // blue

Planet Mars (0.0f, 0.062f, vec3(0.8f,0.8f,0.8f), vec3(0.0f,10.0f,0.0f), vec3(9.8f,1.0f,0.0f),vec4(0.5f, 0.35f, 0.05f,0.0f)); 
Planet Jupiter(0.0f, 0.050f, vec3(1.0f,1.0f,1.0f), vec3(0.0f,10.0f,0.0f), vec3(11.8f,1.0f,0.0f),vec4(1.0f,0.45f,0.05f,0.0f)); 

Planet Saturn (0.0f, 0.035f, vec3(0.9f,0.9f,0.9f), vec3(00.0f,10.0f,0.0f), vec3(16.6f,1.0f,0.0f),vec4(1.0f,0.35f,0.05f,0.0f));
Planet Saturn_Ring (0.0f, 0.035f, vec3(1.2f,0.50f,1.8f), vec3(1.0f,1.0f,1.0f), vec3(16.6f,1.0f,0.0f),vec4(1.0f,0.35f,3.35f,1.0f)); // Ring

Planet Uranus (0.0f, 0.030f, vec3(1.9f,1.9f,1.9f), vec3(0.0f,10.0f,0.0f), vec3(21.9f,1.0f,0.0f),vec4(0.5f,0.0f,1.0f,0.0f)); 
Planet Neptune (0.0f, 0.010f, vec3(0.9f,0.9f,0.9f), vec3(0.0f,10.0f,0.0f), vec3(25.8f,1.0f,0.0f),vec4(0.0f,0.0f,1.0f,0.0f)); 

//Moons
Moon Moon_Earth(0.0f, 0.090f, vec3(0.2f,0.2f,0.2f), vec3(0.0f,5.0f,0.0f), vec3(1.0f,0.0f,0.0f),vec4(1.0f,1.0f,1.50f,0.0f));  // blue
Moon Moon_Mars(0.0f, -0.120f, vec3(0.1f,0.1f,0.1f), vec3(0.0f,5.0f,0.0f), vec3(1.0f,0.0f,0.0f),vec4(4.0f,3.0f,0.50f,0.0f));  // blue
Moon Moon_Saturn_1(0.0f, 0.120f, vec3(0.1f,0.1f,0.1f), vec3(0.0f,5.0f,0.0f), vec3(1.0f,0.0f,0.0f),vec4(4.0f,3.0f,0.50f,0.0f));  // blue
Moon Moon_Saturn_2(0.0f, 0.120f, vec3(0.1f,0.1f,0.1f), vec3(1.0f,5.0f,0.0f), vec3(1.0f,0.0f,0.0f),vec4(4.0f,3.0f,0.50f,0.0f));  // blue
Moon Moon_Saturn_3(0.0f, 0.020f, vec3(0.1f,0.1f,0.1f), vec3(1.0f,4.0f,0.0f), vec3(2.0f,0.0f,0.0f),vec4(4.0f,3.0f,0.50f,0.0f));  
Moon moon_5 (0.0f, 0.050f, vec3(0.1f,0.1f,0.1f), vec3(1.0f,4.0f,0.0f), vec3(2.0f,0.0f,0.0f),vec4(4.0f,3.0f,0.50f,0.0f));  

// Draw each planet 
void calculate_PlanetPos(Planet &a) 
{

	glUniform4f(gColorLoc,a.getColor()[0],a.getColor()[1],a.getColor()[2],a.getColor()[3]); // // pass into vec4Unifrom variable vec4,goes to fragment shader and gets uniform variable

	mat4 modelToWorldTransform = mat4(1.0f); // Model to world transform   matrix

	//Scale
	mat4 scaler = mat4(1.0f);
	scaler = scale(scaler, a.getScale()); // vec3(1.0f,9.0f,1.0f)


	// Angle incremenet per frame
	float ang = a.getAngle(); // angle  // vec3(1.0f,9.0f,1.0f)
	ang+=a.getInc(); // incremenet angle by increment  float
	a.setAngle(ang); // set angle that increment

	mat4 rot = mat4(1.0f);
	rot = rotate (rot,ang,vec3(0.0f,ang,0.0f)); // angle on the y axis increments by specifed value each frame ,0.050f in most objects cases
	// 0.080f, 
	//Translation
	mat4 trans = mat4(1.0f);
	trans = translate(trans, a.getTranslate()); // translate per planet object

	modelToWorldTransform = rot*trans*scaler*rot; // Multiply each matrix for model to world transform
	
	// Update the transforms
	glUniformMatrix4fv(gModelToWorldTransformLoc, 1, GL_FALSE, &modelToWorldTransform[0][0]);
	glDrawArrays(GL_TRIANGLES, 0, NUMVERTS); // render primitives from array data
}

// Draw each moon 
void calculateMoon(Planet &x, Moon &y) // Memory location of planet then moon object, modelToWorldTransform,number of vertices
{


	glUniform4f(gColorLoc,y.getColor()[0],y.getColor()[1],y.getColor()[2],y.getColor()[3]); 
	mat4 modelToWorldTransform = mat4(1.0f);
	
	
	mat4 trans_Planet = mat4(1.0f);
	trans_Planet = translate(trans_Planet, x.getTranslate()); // pass in translate matrix and translate vec of planet
	
	mat4 plan_Rot = mat4(1.0f);
	plan_Rot = rotate(plan_Rot, x.getAngle(), x.getAxis()); // gets planets agnle & rotation

	mat4 scaleMoon = mat4(1.0f);
	scaleMoon = scale(scaleMoon, y.getScale()); // matrix of scale of moon and moon objects scale

	mat4 moonTrans = mat4(1.0f);
	moonTrans = translate(moonTrans, y.getTrans());

	mat4 moonRot = mat4(1.0f);
	moonRot = rotate (moonRot,y.getAngle(),y.getAxis());


	float ang = y.getAngle(); // angle  
	ang+=y.getInct(); // incremenet angle by increment  float
	y.setAngle(ang); // set angle that increment


	


	modelToWorldTransform = plan_Rot * trans_Planet * moonRot * moonTrans * scaleMoon;

	glUniformMatrix4fv(gModelToWorldTransformLoc, 1, GL_FALSE, &modelToWorldTransform[0][0]);
	glDrawArrays(GL_TRIANGLES, 0, NUMVERTS);
}
	 
static void renderSceneCallBack()
{
	// Clear the back buffer and the z-buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Create our world space to view space transformation matrix
	mat4 worldToViewTransform = lookAt
		(
		vec3(0.0f,2.0f,-58.0f), // The position of your camera, in world space
		vec3(0.0f,0.0f,3.0f), // where you want to look at, in world space
		vec3(0.0f,1.0f,0.0f)  // Camera up direction (set to 0,-1,0 to look upside-down)
		); 

    // Create out projection transform
    mat4 projectionTransform = perspective(45.0f, (float)windowWidth / (float)windowHeight, 1.0f, 100.0f);

	// Combine the world space to view space transformation matrix and the projection transformation matrix
	mat4 worldToViewToProjectionTransform = projectionTransform * worldToViewTransform;

    // Update the transforms in the shader program on the GPU
    glUniformMatrix4fv(gWorldToViewToProjectionTransformLoc, 1, GL_FALSE, &worldToViewToProjectionTransform[0][0]);

    glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2); // enable vertex attribute array for lighting
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(aitVertex), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(aitVertex), (const GLvoid*)12);
	glVertexAttribPointer(2,4,GL_FLOAT,GL_FALSE,sizeof(aitVertex),(const GLvoid*)24);


    // Set the material properties
    glUniform1f(gKaLoc, 0.8f); 
    glUniform1f(gKdLoc, 0.8f);





	/// Planets
	calculate_PlanetPos(sun);
	calculate_PlanetPos(Mercury);
	calculate_PlanetPos(Venus);
	calculate_PlanetPos(Earth);
	calculate_PlanetPos(Mars);
	calculate_PlanetPos(Jupiter);
	calculate_PlanetPos(Saturn);
	calculate_PlanetPos(Neptune);
	calculate_PlanetPos(Uranus);
	calculate_PlanetPos(Saturn_Ring);
	
	calculateMoon(Earth,Moon_Earth);
	calculateMoon(Mars,Moon_Mars);
	calculateMoon(Saturn,Moon_Saturn_1);
	calculateMoon(Neptune,Moon_Saturn_2);
	calculateMoon(Neptune,Moon_Saturn_3);
	calculateMoon(Jupiter,moon_5);

    glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2); // cle

    glutSwapBuffers();
}

static void initializeGlutCallbacks()
{
    glutDisplayFunc(renderSceneCallBack);
    glutIdleFunc(renderSceneCallBack);
}

static void createVertexBuffer()
{
	aitMesh mesh;
	if(!mesh.loadFromObj("assets/sphere.obj"))
	{
		cerr<<"Error loading mesh from obj file."<<endl;
		system("pause");
		exit(0);
	}
	vector<aitVertex> verts = mesh.getVertices();
	NUMVERTS = verts.size(); 
 



 	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(aitVertex) * NUMVERTS, &verts[0], GL_STATIC_DRAW);
}

static void initLights()
{


	

	// Setup the ambient light
	vec3 ambientLightIntensity = vec3(0.5f, 1.0f, 0.5f);
	glUniform3fv(gAmbientLightIntensityLoc, 1, &ambientLightIntensity[0]);
	
	// Setup the direactional light
	vec3 directionalLightDirection = vec3(-5.0f, 1.0f, 2.0f);
	normalize(directionalLightDirection);
	glUniform3fv(gDirectionalLightDirectionLoc, 1, &directionalLightDirection[0]);
	vec3 directionalLightIntensity = vec3(0.7f, 2.7f, 2.7f);
	glUniform3fv(gDirectionalLightIntensityLoc, 1, &directionalLightIntensity[0]);
}

static void addShader(GLuint shaderProgram, const char* pShaderText, GLenum shaderType)
{
    GLuint shaderObj = glCreateShader(shaderType);

    if (shaderObj == 0) 
	{
        cerr<<"Error creating shader type "<<shaderType<<endl;
        exit(0);
    }

    const GLchar* p[1];
    p[0] = pShaderText;
    GLint Lengths[1];
    Lengths[0]= strlen(pShaderText);
    glShaderSource(shaderObj, 1, p, Lengths);
    glCompileShader(shaderObj);
    GLint success;
    glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &success);
    if (!success) 
	{
        GLchar InfoLog[1024];
        glGetShaderInfoLog(shaderObj, 1024, NULL, InfoLog);
        cerr<<"Error compiling shader type "<<shaderType<<": "<<InfoLog<<endl;
        exit(1);
    }

    glAttachShader(shaderProgram, shaderObj);
}

const string readFileToString(const char* filename)
{
	ifstream file (filename, ios::in);
	if (file.is_open())
	{
        stringstream continut;
        continut << file.rdbuf();
        continut << '\0';
		return continut.str();
	}
    return "";
}

static void buildShaders()
{
    GLuint shaderProgram = glCreateProgram();

    if (shaderProgram == 0) 
	{
        cerr<<"Error creating shader program\n";
        exit(1);
    }

	string VS = readFileToString("vertexShader.glsl");
	string FS = readFileToString("fragmentShader.glsl");

    addShader(shaderProgram, VS.c_str(), GL_VERTEX_SHADER);
    addShader(shaderProgram, FS.c_str(), GL_FRAGMENT_SHADER);

    GLint success = 0;
    GLchar errorLog[1024] = { 0 };

    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (success == 0) 
	{
		glGetProgramInfoLog(shaderProgram, sizeof(errorLog), NULL, errorLog);
		cerr<<"Error linking shader program: "<<errorLog<<endl;
        exit(1);
	}

    glValidateProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &success);
    if (!success) 
	{
        glGetProgramInfoLog(shaderProgram, sizeof(errorLog), NULL, errorLog);
        cerr<<"Error linking shader program: "<<errorLog<<endl;
        exit(1);
    }

    glUseProgram(shaderProgram);

    gModelToWorldTransformLoc = glGetUniformLocation(shaderProgram, "gModelToWorldTransform");
    assert(gModelToWorldTransformLoc != 0xFFFFFFFF);
    gWorldToViewToProjectionTransformLoc = glGetUniformLocation(shaderProgram, "gWorldToViewToProjectionTransform");
    assert(gWorldToViewToProjectionTransformLoc != 0xFFFFFFFF);
	gAmbientLightIntensityLoc = glGetUniformLocation(shaderProgram, "gAmbientLightIntensity");
	assert(gAmbientLightIntensityLoc != 0xFFFFFFFF);
	gDirectionalLightIntensityLoc = glGetUniformLocation(shaderProgram, "gDirectionalLightIntensity");
	assert(gDirectionalLightIntensityLoc != 0xFFFFFFFF);
	gDirectionalLightDirectionLoc = glGetUniformLocation(shaderProgram, "gDirectionalLightDirection");
	assert(gDirectionalLightDirectionLoc != 0xFFFFFFFF);
    gKaLoc = glGetUniformLocation(shaderProgram, "gKa");
	assert(gDirectionalLightDirectionLoc != 0xFFFFFFFF);
    gKdLoc = glGetUniformLocation(shaderProgram, "gKd");
	assert(gDirectionalLightDirectionLoc != 0xFFFFFFFF);


	gColorLoc = glGetUniformLocation(shaderProgram,"gColor"); // getUniform variable from fragmentShader.glsl 

}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(350, 350);
    glutCreateWindow("Solar System");

    initializeGlutCallbacks();

    // Must be done after glut is initialized!
    GLenum res = glewInit();
    if (res != GLEW_OK) 
    {
		cerr<<"Error: "<<glewGetErrorString(res)<<"\n";
		return 1;
    }

	buildShaders();

	// Enable the z-buffer
	glEnable(GL_DEPTH_TEST);
	// GL_LESS - Passes if the incoming depth value is less than the stored depth value
	glDepthFunc(GL_LESS);

	//Enable backface culling
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW); 

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); 

	// Initialise lights
	initLights();
	 
	// Create a vertex buffer
	createVertexBuffer();

    glutMainLoop();
    
    return 0;
}