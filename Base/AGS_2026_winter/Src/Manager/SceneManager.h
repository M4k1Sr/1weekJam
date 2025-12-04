#pragma once
#include "../framework.h"
class SceneBase;
class Fader;
class Camera;
class System;

class SceneManager
{

public:

	//ステージ
	static inline STAGE selectedStage_ = STAGE::STAGE1;
	//プレイモード
	static inline PLAY_MODE playMode_ = PLAY_MODE::SOLO;

	// シーン管理用
	enum class SCENE_ID
	{
		NONE,
		TITLE,
		MODESELECT,
		SOLO,
		MULTI,
		MISSION,
		STAGESELECT,
		GAME_MENU,
		GAME,
		CLEAR,
		GAMEOVER,
		RESULT
	};
	
	// インスタンスの生成
	static void CreateInstance(void);

	// インスタンスの取得
	static SceneManager& GetInstance(void);

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);
	void Init3D(void);

	// 状態遷移
	void ChangeScene(SCENE_ID nextId);

	// シーンIDの取得
	SCENE_ID GetSceneID(void);

	// デルタタイムの取得
	float GetDeltaTime(void) const;

	static STAGE GetNextStage(STAGE current);

	float GetTotalTime(void) const;

	System* GetSystem(void) const;

	

private:

	// 静的インスタンス
	static SceneManager* instance_;

	SCENE_ID sceneId_;
	SCENE_ID waitSceneId_;

	// フェード
	Fader* fader_;

	//カメラ
	Camera* camera_;

	// 各種シーン
	SceneBase* scene_;

	//タイマー
	System* system_;

	// シーン遷移中判定
	bool isSceneChanging_;

	// デルタタイム
	std::chrono::system_clock::time_point preTime_;
	float deltaTime_;
	
	// デフォルトコンストラクタをprivateにして、
	// 外部から生成できない様にする
	SceneManager(void);
	// コピーコンストラクタも同様
	SceneManager(const SceneManager&);
	// デストラクタも同様
	~SceneManager(void);

	// デルタタイムをリセットする
	void ResetDeltaTime(void);

	// シーン遷移
	void DoChangeScene(SCENE_ID sceneId);

	// フェード
	void Fade(void);

	bool isLoading_ = false;        // ローディング状態か
	float loadingTime_ = 0.0f;      // ローディング経過時間
	constexpr static float LOADING_WAIT = 1.0f;  // ローディング演出時間

	

};