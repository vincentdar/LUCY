#pragma once

#include <SFML/Graphics.hpp>
#include <chrono>

#include "Utils.h"

class Camera
{
private:
	sf::View			view;
	sf::RenderTarget*	target;

	// Implementasi hanya translate saja
	bool				translate = false;
	sf::Vector2f		translateTarget;
	sf::Vector2f		directionOfTranslation;
	std::time_t			offset;

	// Start time
	std::chrono::time_point
		<std::chrono::high_resolution_clock>	start, previous;

public:
	Camera(sf::View& view) {
		this->view = view;
		translate = false;
	}

	Camera() { translate = false; }

	Camera(sf::Vector2f center, sf::Vector2f rect) {
		set(center, rect);
		translate = false;
	}

	void setRenderTarget(sf::RenderTarget* target) {
		this->target = target;
	}

	void set(sf::Vector2f center, sf::Vector2f rect) {
		view.setCenter(center);
		view.setSize(rect);
	}

	void translateCameraToPosition(sf::Vector2f target, std::time_t offset) {
		// Camera diset state utk gerak di update.
		translate = true;
		translateTarget = target;
		this->offset = offset;

		start = std::chrono::high_resolution_clock::now();

		directionOfTranslation = translateTarget - view.getCenter();
		// Normalize
		UTILS.normalizeVector2f(directionOfTranslation);
	}

	void update() {
		if (!translate) {
			return;
		}

		std::chrono::duration<double> elapsed = std::chrono::high_resolution_clock::now() - start;
		if (elapsed.count() >= offset) {
			// Move camera to location
			view.move(directionOfTranslation);
			start = std::chrono::high_resolution_clock::now();

			target->setView(view);

			std::cout << view.getCenter().x << " " << view.getCenter().y << std::endl;

			if (view.getCenter() == translateTarget) {
				translate = false;
			}
		}
	}
};