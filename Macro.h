#pragma once

// Matthew: Resolution ku 1366 x 768 ui :(
//#define SCREEN_WIDTH 1920
//#define SCREEN_HEIGHT 1080
#define SCREEN_WIDTH 1366
#define SCREEN_HEIGHT 768

#define ASSET_CONF "res/Assets.conf"

#define TOTAL_LANES 5
#define ENEMY_SPAWN_X data->window.getSize().x + 100
#define BOTTOM_UI_HEIGHT 180
#define LANE_HEIGHT ((data->window.getSize().y - BOTTOM_UI_HEIGHT) / TOTAL_LANES)