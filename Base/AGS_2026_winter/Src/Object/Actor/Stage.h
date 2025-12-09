#pragma once
#include "ActorBase.h"
#include "../../framework.h"
#include "../Common/Transform.h"

class Stage : public ActorBase
{
public:

	// 衝突判定種別
	enum class COLLIDER_TYPE
	{
		MODEL = 0,
		MAX,
	};


	Stage(void);
	void Update(void)override;
	void Release(void)override;

private:

	////ステージ
	//Transform mainStage_;

	// 除外フレーム名称
	const std::vector<std::string> EXCLUDE_FRAME_NAMES = {
	"Mush", "Grass",
	};


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


};

