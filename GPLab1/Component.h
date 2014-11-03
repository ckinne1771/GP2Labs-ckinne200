#ifndef Component_h
#define Component_h
#include <GL/glew.h>
#include <SDL_opengl.h>
#include <iostream>
#include <fstream>
#include <string>

class GameObject; 

class Component
{
public:
	Component();
	virtual ~Component();
	virtual void init();
	virtual void render();
	virtual void update();
	virtual void destroy();
	const std::string& getType();
	void toggleActive();
	bool isActive();
	void setParent(GameObject * object);
protected:
	std::string m_Type;
	bool m_Active;
	GameObject * m_Parent;
private:
};


#endif