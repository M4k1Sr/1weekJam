#pragma once
#include "SceneBase.h"
class Camera;
class Grid;

class GameScene : public SceneBase
{
public:

	// コンストラクタ
	GameScene(void);

	// デストラクタ
	~GameScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:

	Camera* camera_;
	Grid* grid_;

};

