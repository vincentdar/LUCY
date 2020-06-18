#pragma once
#include "UI_Base.h"

namespace UI 
{
	class Alert 
		: public Base
	{
	private:
		sf::Font*		font;
		sf::Color		color;

		sf::Text		content;
		sf::Text		title;

		std::string		contentStr;
		std::string		titleStr;

		bool			isShown = false;

		enum AlertMode {
			CLICK, TIMED
		}				alert;

		float			hideTimer;

	public:
		Alert() : Base() { alert = CLICK; contentStr = ""; titleStr = ""; }
		
		void setContent(const std::string& content);
		void setTitle(const std::string& title);
		std::string getContent() { return contentStr; }
		std::string getTitle() { return titleStr; }

		void init() override;
		void update(sf::RenderWindow& window) override;
		void draw(sf::RenderTarget& target) override;
		void handleInput(sf::Event& event, sf::RenderWindow& window) override;

		UI_Type getType() { return ALERT; }

		void setFont(sf::Font* font);
		void setFillColor(sf::Color color);

		void setContentCharacterSize(int s) { 
			content.setCharacterSize(s); 
		}
		void setTitleCharacterSize(int s) {
			title.setCharacterSize(s); 
		}

		void show();
		void hide();

		void setHideTimer(float seconds) {
			hideTimer = seconds;
			alert = TIMED;
			timer.restart();
		}

	};

}