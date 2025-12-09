#include "CharactorBase.h"
#include "../../Common/AnimationController.h"
#include "../../../Utility/AsoUtility.h"
#include "../../../Manager/SceneManager.h"
#include "../../../Application.h"
#include "../../Collider/ColliderLine.h"
#include "../../Collider/ColliderBase.h"
#include "../../Collider/ColliderModel.h"
#include "../../Collider/ColliderCapsule.h"

CharactorBase::CharactorBase(void)
	:
	ActorBase()
{
}
CharactorBase::~CharactorBase(void)
{
}

void CharactorBase::Update(void)
{
	// 移動前座標を更新
	prevPos_ = transform_.pos;

	// 各キャラクターごとの更新処理
	UpdateProcess();
	// 移動方向に応じた遅延回転
	DelayRotate();
	// 重力による移動量
	CalcGravityPow();
	// 衝突判定前準備
	CollisionReserve();
	// 衝突判定
	Collision();
	// モデル制御更新
	transform_.Update();
	// アニメーション再生
	anim_->Update();
	// 各キャラクターごとの更新後処理
	UpdateProcessPost();


}

void CharactorBase::CollisionCapsule(void)
{
	int capsuleType = static_cast<int>(COLLIDER_TYPE::CAPSULE);

	if (ownColliders_.count(capsuleType) == 0) return;

	ColliderCapsule* colliderCapsule =
		dynamic_cast<ColliderCapsule*>(ownColliders_.at(capsuleType).get());
	if (colliderCapsule == nullptr) return;

	for (const auto& hitCol : hitColliders_)
	{
		if (hitCol->GetShape() != ColliderBase::SHAPE::MODEL) continue;

		const ColliderModel* colliderModel =
			dynamic_cast<const ColliderModel*>(hitCol);
		if (colliderModel == nullptr) continue;

		auto hits = MV1CollCheck_Capsule(
			colliderModel->GetFollow()->modelId, -1,
			colliderCapsule->GetPosTop(), colliderCapsule->GetPosDown(),
			colliderCapsule->GetRadius());

		for (int i = 0; i < hits.HitNum; i++)
		{
			auto hit = hits.Dim[i];

			for (int tryCnt = 0; tryCnt < CNT_TRY_COLLISION; tryCnt++)
			{
				int pHit = HitCheck_Capsule_Triangle(
					colliderCapsule->GetPosTop(), colliderCapsule->GetPosDown(),
					colliderCapsule->GetRadius(),
					hit.Position[0], hit.Position[1], hit.Position[2]);

				if (pHit)
				{
					// 衝突法線に Y を足して斜め上方向に
					VECTOR pushDir = hit.Normal;
					pushDir.y += 1.0f;   // 1.0 くらいで十分
					pushDir = VNorm(pushDir);

					// 位置の押し戻しは少しだけ
					transform_.pos = VAdd(transform_.pos,
						VScale(pushDir, COLLISION_BACK_DIS * 2.0f));

					// 速度に吹っ飛びを加える
					const float PUSH_FORCE = 150.0f; // 大きすぎない
					velocity_ = VAdd(velocity_, VScale(pushDir, PUSH_FORCE));


					continue;

				}
				break;
			}
		}

		MV1CollResultPolyDimTerminate(hits);
	}
}

void CharactorBase::DelayRotate(void)
{
	// 移動方向から回転に変換する
	Quaternion goalRot = Quaternion::LookRotation(moveDir_);
	// 回転の補間
	transform_.quaRot =
		Quaternion::Slerp(transform_.quaRot, goalRot, 0.2f);
}

void CharactorBase::CalcGravityPow(void)
{
	// 重力方向
	VECTOR dirGravity = AsoUtility::DIR_D;

	// 重力の強さ
	float gravityPow = Application::GetInstance().GetGravityPow() * scnMng_.GetDeltaTime();

	// 重力
	VECTOR gravity = VScale(dirGravity, gravityPow);

	jumpPow_ = VAdd(jumpPow_, gravity);

	// 重力速度の制限
	if (jumpPow_.y < MAX_FALL_SPEED)
	{
		jumpPow_.y = MAX_FALL_SPEED;
	}

}

void CharactorBase::Collision(void)
{
	// 移動処理
	transform_.pos = VAdd(transform_.pos, movePow_);
	// 衝突(カプセル)
	CollisionCapsule();
	// ジャンプ量を加算
	transform_.pos = VAdd(transform_.pos, jumpPow_);
	// 衝突(重力)
	CollisionGravity();
}

void CharactorBase::CollisionGravity(void)
{
	// 線分コライダ
	int lineType = static_cast<int>(COLLIDER_TYPE::LINE);

	// 線分コライダが無ければ処理を抜ける
	if (ownColliders_.count(lineType) == 0) return;

	// 線分コライダ情報
	ColliderLine* colliderLine_ =
		dynamic_cast<ColliderLine*>(ownColliders_.at(lineType).get());


	if (colliderLine_ == nullptr) return;

	// 線分の始点と終点を取得
	VECTOR s = colliderLine_->GetPosStart();
	VECTOR e = colliderLine_->GetPosEnd();

	// 登録されている衝突物を全てチェック
	for (const auto& hitCol : hitColliders_)
	{
		// ステージ以外は処理を飛ばす
		if (hitCol->GetTag() != ColliderBase::TAG::STAGE) continue;

		// 派生クラスへキャスト
		const ColliderModel* colliderModel =
			dynamic_cast<const ColliderModel*>(hitCol);

		if (colliderModel == nullptr) continue;

		// ステージモデル(地面)との衝突
		auto hit = MV1CollCheck_Line(
			colliderModel->GetFollow()->modelId, -1, s, e);

		//除外フレームに追加


		if (hit.HitFlag > 0)
		{
			// 衝突地点から、少し上に移動
			transform_.pos =
				VAdd(hit.HitPosition, VScale(AsoUtility::DIR_U, 2.0f));
			// ジャンプリセット
			jumpPow_ = AsoUtility::VECTOR_ZERO;

			//ジャンプの入力受付時間をリセット
			stepJump_ = 0.0f;

			// ジャンプ判定
			isJump_ = false;
		}
	}

}

