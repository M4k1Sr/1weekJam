#pragma once
#include "../Application.h"

class SceneBase
{

public:

	static constexpr float COMMA_TIME = 0.3f;  // ドットが増える間隔（秒）
	static constexpr int COMMA_MAX_NUM = 5;    // 最大ドット数（.....まで）
	static constexpr int LOAD_FONT_SIZE = 28;
	static constexpr int LOADING_STRING_POS_X = Application::SCREEN_SIZE_X - 200;  // = 824
	static constexpr int LOADING_STRING_POS_Y = Application::SCREEN_SIZE_Y - LOAD_FONT_SIZE - 15;  // Y座標

	

	// コンストラクタ
	SceneBase(void);

	// デストラクタ
	virtual ~SceneBase(void) = 0;

	// 初期化処理
	virtual void Init(void) = 0;

	// 更新ステップ
	virtual void Update(void) = 0;

	// 描画処理
	virtual void Draw(void) = 0;

	// 解放処理
	virtual void Release(void) = 0;

	void DrawNowLoading(void);

private:

	int loadFont_;
	bool isCommonInitialized_=false;

};
