#include "Transform.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using glm::mat4;
using glm::vec3;
Transform::Transform()
{

}

Transform::~Transform()
{

}

void Transform::Update()
{
	if (m_Active == true)
	{
		mat4 translate = glm::translate(translate, m_Position);
		mat4 scale = glm::scale(scale, m_Scale);

		mat4 rotationX = glm::rotate(rotationX, m_Rotation.x, vec3(1.0f, 0.0f, 0.0f));
		mat4 rotationY = glm::rotate(rotationY, m_Rotation.y, vec3(0.0f, 1.0f, 0.0f));
		mat4 rotationZ = glm::rotate(rotationZ, m_Rotation.z, vec3(0.0f, 0.0f, 1.0f));
		mat4 rotation = rotationX*rotationY*rotationZ;
		m_Model = translate*rotation*scale;
	}
	
}

vec3 Transform::getPosition()
{
	return m_Position;
}

void Transform::setPosition(vec3 m_Position)
{

}

vec3 Transform::getScale()
{
	return m_Scale;
}

void Transform::setScale(vec3 m_Scale)
{
	
}

vec3 Transform::getRotation()
{
	return m_Rotation;

}

void Transform::setRotation(vec3 m_Rotation)
{
}

mat4 Transform::getModelMatrix()
{
	return m_Model;
}