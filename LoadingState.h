#pragma once

#include "IState.h"
#include "Game.h"
#include "GameState.h"

namespace LUCY
{
	template<class Destination>
	class LoadingState : public IState
	{
	private:
		GameDataRef		data;
		float			time;

		sf::Clock		clock;
		float			prevTime = 0;

		sf::Text		loadingText;
		int				dotCount = 0;

	public:
		LoadingState(GameDataRef data, float time)
			: data(data), time(time) {}

		void VInit() {
			data->window.setView(data->window.getDefaultView());
			loadingText.setFont(*data->assets.GetFontPtr("Press_Start"));
			loadingText.setString("LOADING");
			loadingText.setFillColor(sf::Color::White);
			loadingText.setPosition(800, 600);
			loadingText.setCharacterSize(40);
		}

		void VDraw(float dt) {
			data->window.clear();

			data->window.draw(loadingText);

			data->window.display();
		}

		void VHandleInput() {
			sf::Event event;
			while (data->window.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					data->window.close();
				}
			}
		}

		void VUpdate(float dt) {
			if (clock.getElapsedTime().asSeconds() >= time) {
				VExit();
			}

			std::string add = "";
			for (int i = 0; i < dotCount; i++) {
				add += ".";
			}

			loadingText.setString("LOADING" + add);

			if (clock.getElapsedTime().asSeconds() - prevTime >= 0.2) {
				if (dotCount >= 3) {
					dotCount = 0;
				}
				else {
					dotCount++;
				}
				prevTime = clock.getElapsedTime().asSeconds();
			}

			printf("%f\n", clock.getElapsedTime().asSeconds() - prevTime);
		}

		void VResume() {}
		void VPause() {}

		void VExit() {
			data->machine.AddState(StateRef(new Destination(data)), true);
		}
	};
}