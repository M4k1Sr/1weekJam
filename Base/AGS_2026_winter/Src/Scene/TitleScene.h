#pragma once
#include "SceneBase.h"

class TitleScene : public SceneBase
{
public:

	// コンストラクタ
	TitleScene(void);

	// デストラクタ
	~TitleScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:

	int titleImg_;
	int backImg_;
	int pushImg_;

	int count = 0;

	bool pushAlive_;
};

