#pragma once
#include "ActorBase.h"
#include "../../framework.h"
#include "../Common/Transform.h"

class Bar : public ActorBase
{
public:

	// 時制種別
	enum class TIME_STATE
	{
		START,
		HALF,
		FINAL,
	};
	
	// 衝突判定種別
	enum class COLLIDER_TYPE
	{
		MODEL = 0,
		MAX,
	};

	Bar(void);
	void Update(void)override;
	void Release(void)override;

	void TimeState(TIME_STATE timeState);

private:

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

	TIME_STATE timeState_;
	
	Transform up_;

	float speed_; //回転スぴード

	int time_;// 経過カウンタ

	void UpdateStart(void);
	void UpdateHalf(void);
	void UpdateFinal(void);
};

