#pragma once
#include "ActorBase.h"
#include "../../framework.h"
#include "../Common/Transform.h"

class SkyDome : public ActorBase
{
public:

	SkyDome(void);
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

private:

	//ステージ
	Transform skyDome_;

	// リソースロード
	void InitLoad(void)override;

	// 大きさ、回転、座標の初期化
	void InitTransform(void)override;

	// 衝突判定の初期化
	void InitCollider(void)override;

	// アニメーションの初期化
	void InitAnimation(void)override;

	// 初期化後の個別処理
	void InitPost(void)override;

	float speed_; //回転スぴード

};

