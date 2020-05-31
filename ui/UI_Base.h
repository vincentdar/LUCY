#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

namespace LUCY {

	class UI_Base
	{
	private:
		static unsigned int gui_generate_id;

	protected:
		unsigned int id;

	public:
		UI_Base() {
			// Ketika object BaseUI dibuat, maka gui_generate_id akan mengenerate id baru,
			//  dimana id tsb akan dimiliki scr unik oleh tiap gui component.
			gui_generate_id++;
			id = gui_generate_id;
		}
	};

}