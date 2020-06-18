#pragma once

#include "UI_Base.h"
#include "UI_Button.h"
#include "UI_Card.h"
#include "UI_Textfield.h"

#include <unordered_map>

namespace UI
{
	class Container
		: public Base
	{
	private:
		//std::vector<UI::Base*>	components;
		std::unordered_map<std::string, UI::Base*> components;

	public:
		Container();
		Container(sf::Vector2f position, sf::Vector2f size, UI_Origin origin);
		~Container();

		// Override functions
		void init() override;
		UI_Type getType() override;
		void draw(sf::RenderTarget& target) override;
		void update(sf::RenderWindow& window) override;
		void handleInput(sf::Event& event, sf::RenderWindow& window) override;

		void setOrigin(UI_Origin origin);
		void setOrigin(sf::Vector2f origin);

		void addComponent(std::string key, 
							UI::Base* new_component, 
							sf::Vector2f position = { 0, 0 });
	
		void removeComponent(const std::string& key);

		template<class T>
		T* getComponent(const std::string& key) {
			T* cast = dynamic_cast<T*>(components[key]);

			if (dynamic_cast<T*>(components[key]) == nullptr) {
				std::cout << "Incompatible pointer casting of " << key << ".\n";
			}

			return cast;
		}

		//Button* getComponent(const std::string& key);

		// Set position relatif thd base_shape position.
		void setComponentPosition(const std::string& key, sf::Vector2f position);

		
	};
}