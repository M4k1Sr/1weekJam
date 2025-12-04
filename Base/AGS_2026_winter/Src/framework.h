#pragma once

#include <DxLib.h>
#include <assert.h>
#include <memory>
#include <map>
#include <string>
#include <vector>
#include <chrono>
#include<functional>
#include <list>
#include <fstream>
#include <sstream>
#include <math.h>
#include<unordered_map>
#include <array>
#include <algorithm>

enum class STAGE
{
	STAGE1,
	STAGE2,
	STAGE3,
	STAGE4,
	STAGE5,
	STAGE_M1,
	MAX_STAGE
};

enum class PLAY_MODE
{
	SOLO,
	MULTI,
	MAX
};

enum class SOUND_TYPE
{
	SHOT_FIRE,		// 弾発射音
	SHOT_WALL_HIT,	// 弾ヒット音
	SHOT_EXPLOSION,	// 弾爆発音
	SHOT_REFLECT,	// 弾反射音
	MISSION,	// ミッション音
	ENTER,		// 決定音
	CURSOR,	// カーソル移動音
	PLAYER_MOVE, // プレイヤー移動音
	PLAYER_MOVE2,//プレイヤーの移動音２P
	WARNING_C,	//コントローラーを接続してください
	CLEAR,
	GAMEOVER,
	MAX
};