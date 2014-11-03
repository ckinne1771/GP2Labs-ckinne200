#ifndef Transform_h
#define Transform_h

#include "Component.h"
#include <GL/glew.h>
#include<SDL_opengl.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <glm/glm.hpp>
using glm::mat4;
using glm::vec3;

class Transform : public Component
{
public:
	Transform();
	~Transform();
	void Update();
	vec3& getPosition();
	void setPosition(float x, float y, float z);
	vec3& getScale();
	void setScale(float x, float y, float z);
	vec3& getRotation();
	void setRotation(float x, float y, float z);
	mat4& getModelMatrix();
protected:
private:
	vec3 m_Position;
	vec3 m_Scale;
	vec3 m_Rotation;
	mat4 m_Model;
	
};

#endif