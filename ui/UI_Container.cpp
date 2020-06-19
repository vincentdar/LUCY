#include "UI_Container.h"

namespace UI 
{
	Container::Container()
	{}

	Container::Container(sf::Vector2f position, sf::Vector2f size, UI_Origin origin)
	{
		base_shape.setSize(size);
		base_shape.setPosition(position);

		setOrigin(origin);
	}

	Container::~Container()
	{
		for (auto i = components.begin(); i != components.end();) {
			delete i->second;
			i = components.erase(i);
		}

		components.clear();
	}

	void Container::init()
	{
	}

	UI_Type Container::getType()
	{
		return CONTAINER;
	}

	void Container::setOrigin(UI_Origin origin)
	{
		this->origin = origin;
	}

	void Container::setOrigin(sf::Vector2f origin)
	{
		this->origin = CUSTOM;
		base_shape.setOrigin(origin);
	}

	void Container::addComponent(std::string key, UI::Base * new_component, sf::Vector2f position)
	{
		if (components.find(key) != components.end()) {
			printf("Component with the same key exists!\n");
			return;
		}

		components[key] = new_component;

		setComponentPosition(key, position);
	}

	void Container::removeComponent(const std::string& key)
	{
		if (components.find(key) == components.end()) {
			printf("Component doesn't exist!\n");
			return;
		}

		components.erase(key);
	}

	void Container::setComponentPosition(const std::string& key, sf::Vector2f position)
	{
		if (components.find(key) == components.end()) {
			printf("Component doesn't exist!\n");
			return;
		}

		sf::Vector2f absolutePos =
		{
			base_shape.getGlobalBounds().left + position.x,
			base_shape.getGlobalBounds().top + position.y
		};

		components[key]->setPosition(absolutePos);
	}

	void Container::draw(sf::RenderTarget & target)
	{
		target.draw(base_shape);
		for (auto const& component : components) {
			component.second->draw(target);
		}

		//std::cout << getComponent("Button")->getPosition().x << " " << getComponent("Button")->getPosition().y << std::endl;
	}

	void Container::update(sf::RenderWindow& window)
	{
		for (auto& component : components) {
			component.second->update(window);
		}
	}

	void Container::handleInput(sf::Event & event, sf::RenderWindow& window)
	{
		for (auto& component : components) {
			component.second->handleInput(event, window);
		}
	}
}
