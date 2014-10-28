#ifndef GameObject_h
#define GameObject_h

#include <GL/glew.h>
#include<SDL_opengl.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include "Component.h"
#include <vector>

class GameObject{
public:
	GameObject();
	~GameObject();
	void init();
	void update();
	void render();
	void destroy();
	const std::string& getName();
	void setName(const std::string& name);
	void addComponent(Component* component);
protected:
private:
	std::string m_Name;
	std::vector<Component*> m_Components;
};

#endif#
