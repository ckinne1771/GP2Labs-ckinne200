#include "GameObject.h"

GameObject::GameObject()
{
	//m_Name = "GameObject";
	
}

GameObject::~GameObject()
{

}

void GameObject::init(){
	for (auto iter = m_Components.begin(); iter != m_Components.end(); iter++)
	{
		(*iter)->init();
	}
}

void GameObject::update(){
	for (auto iter = m_Components.begin(); iter != m_Components.end(); iter++)
	{
		(*iter)->update();
	}
}

void GameObject::render(){
	for (auto iter = m_Components.begin(); iter != m_Components.end(); iter++)
	{
		(*iter)->render();
	}
}

void GameObject::destroy(){
	auto iter = m_Components.begin();
	while (iter != m_Components.end())
	{
		(*iter)->destroy();
		if ((*iter))
		{
			delete(*iter);
			(*iter) = NULL;
			iter = m_Components.erase(iter);
		}
		else
		{
			iter++;
		}
	}
	m_Components.clear();
}

const std::string& GameObject::getName()
{
	return m_Name;
}

void GameObject::setName(const std::string& m_Name)
{

}



