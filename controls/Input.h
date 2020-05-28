#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>

// Singleton class input
// Class ini menyimpan data semua input yg diterima,
//  dan bisa diberi label untuk akses lebih mudah.

// Last edit: Matthew Sutanto, 28/05/2020 => First

namespace LUCY {

	enum InputMode {
		INPUT_KEYPRESSED = 0,
		INPUT_KEYDOWN,
		INPUT_KEYRELEASED,

		INPUT_BUTTONDOWN,
		INPUT_BUTTONRELEASED
	};

	class Input {
	private:
		std::unordered_map <std::string, sf::Keyboard::Key>	mapping_keys;
		std::unordered_map <std::string, sf::Mouse::Button>	mapping_buttons;

		static Input* instance;

	public:
		static Input* get() {
			if (instance == nullptr) {
				instance = new Input();
			}
			return instance;
		}

		void registerKey(const std::string& name, sf::Keyboard::Key key)
		{
			// Check apakah sudah ada
			auto index = mapping_keys.find(name);
			if (index != mapping_keys.end()) {
				printf("ERROR::INPUT: Key cannot be added. Key with the same name exists!");
				return;
			}

			mapping_keys[name] = key;
		}

		void changeRegisteredKey(const std::string& name, sf::Keyboard::Key key) {
			// Check apakah sudah ada
			auto index = mapping_keys.find(name);
			if (index == mapping_keys.end()) {
				printf("ERROR::INPUT: Key doesn't exist.");
				return;
			}

			index->second = key;
		}

		void removeRegisteredKey(const std::string& name, sf::Keyboard::Key key) {
			// Check apakah sudah ada
			auto index = mapping_keys.find(name);
			if (index == mapping_keys.end()) {
				printf("ERROR::INPUT: Key cannot be removed. Key doesn't exist!");
				return;
			}

			mapping_keys.erase(name);
		}

		void registerMouseButton(const std::string& name, sf::Mouse::Button btn) {
			auto index = mapping_buttons.find(name);
			if (index != mapping_buttons.end()) {
				printf("ERROR::INPUT: Button cannot be added. Button already exists!");
				return;
			}

			mapping_buttons[name] = btn;
		}

		void changeRegisteredButton(const std::string& name, sf::Mouse::Button key) {
			// Check apakah sudah ada
			auto index = mapping_buttons.find(name);
			if (index == mapping_buttons.end()) {
				printf("ERROR::INPUT: Button cannot be removed. Button doesn't exist!");
				return;
			}

			index->second = key;
		}

		void removeRegisteredButton(const std::string& name, sf::Mouse::Button key) {
			// Check apakah sudah ada
			auto index = mapping_buttons.find(name);
			if (index == mapping_buttons.end()) {
				printf("ERROR::INPUT: Button doesn't exist.");
				return;
			}

			mapping_buttons.erase(name);
		}

		bool getKey(const std::string& name, InputMode mode, sf::Event& event, sf::RenderWindow* window = nullptr) {

			auto index = mapping_keys.find(name);
			if (index == mapping_keys.end()) {
				printf("ERROR::INPUT: Key doesn't exist.");
				return false;
			}

			if (mode == InputMode::INPUT_KEYPRESSED) {
				return (event.type == sf::Event::KeyPressed && event.key.code == mapping_keys[name]);
			}
			else if (mode == InputMode::INPUT_KEYRELEASED) {
				return (event.type == sf::Event::KeyReleased && event.key.code == mapping_keys[name]);
			}
			else if (mode == InputMode::INPUT_KEYDOWN) {
				return sf::Keyboard::isKeyPressed(mapping_keys[name]);
			}
		}

		bool getButton(const std::string& name, InputMode mode, sf::Event& event) {

			auto index = mapping_buttons.find(name);
			if (index == mapping_buttons.end()) {
				printf("ERROR::INPUT: Button doesn't exist.");
				return false;
			}

			if (mode == InputMode::INPUT_BUTTONDOWN) {
				return (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == mapping_buttons[name]);
			}
			else if (mode == InputMode::INPUT_BUTTONRELEASED) {
				return (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == mapping_buttons[name]);
			}
		}
	};

	Input* Input::instance = nullptr;

}