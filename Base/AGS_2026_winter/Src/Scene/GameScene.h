#pragma once
#include "SceneBase.h"
class Camera;
class ActorBase;
class Grid;

class GameScene : public SceneBase
{
public:

	// タイムリミット
	const float LIMIT_TIME = 1.0f;

	// コンストラクタ
	GameScene(void);

	// デストラクタ
	~GameScene(void);

	void Init(void) override;
	void Update() override;
	void Draw(void) override;
	void Release(void) override;

	// タイムリミット関連
	void StartMission(float limitSeconds = 31.0f);
	float GetRemainingTime() const;

private:

	Camera* camera_;
	Grid* grid_;
	ActorBase* stage_;
	ActorBase* player_;
	ActorBase* bar_;
	ActorBase* barUp_;

	// タイムリミット
	float timeLimit_;
	float elapsedTime_;
	bool isTimeLimitActive_;

	void OnTimeUp();  // 時間切れ処理
};

