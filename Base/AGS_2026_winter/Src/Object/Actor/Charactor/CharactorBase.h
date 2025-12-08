#pragma once
#include "../ActorBase.h"
#include "../../../framework.h"

class CharactorBase : public ActorBase
{
public:

	// 衝突時の押し戻し試行回数
	static constexpr int CNT_TRY_COLLISION = 20;
	// 衝突時の押し戻し量
	static constexpr float COLLISION_BACK_DIS = 1.0f;


	// 衝突判定種別
	enum class COLLIDER_TYPE
	{
		LINE,
		CAPSULE,
		MAX,
	};

	// コンストラクタ
	CharactorBase(void);
	// デストラクタ
	virtual ~CharactorBase(void) override;

	// 更新
	virtual void Update(void) override;

	void CollisionCapsule(void);



protected:

	VECTOR moveDir_; //移動方向
	// ジャンプ量
	VECTOR jumpPow_;
	// 移動前の座標
	VECTOR prevPos_;
	//移動速度
	VECTOR movePow_;
	// ジャンプ判定
	bool isJump_;
	//ジャンプの入力受付時間
	float stepJump_;


	// 更新系
	virtual void UpdateProcess(void) = 0;
	virtual void UpdateProcessPost(void) = 0;
	// 移動方向に応じた遅延回転
	void DelayRotate(void);
	// 重力計算
	void CalcGravityPow(void);
	// 衝突判定
	virtual void CollisionReserve(void) {};
	void Collision(void);
	void CollisionGravity(void);


};


