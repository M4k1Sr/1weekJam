#include "Player.h"
#include "../../../Manager/ResourceManager.h"
#include "../../../Utility/AsoUtility.h"
#include "../../Common/AnimationController.h"
#include "../../../Manager/InputManager.h"
#include "../../../Manager/SceneManager.h"
#include "../ActorBase.h"
#include "../../Collider/ColliderLine.h"
#include "../../Collider/ColliderBase.h"
#include "../../Collider/ColliderCapsule.h"
#include "../../../Manager/Camera.h"

Player::Player(void)
{
	movePow_ = AsoUtility::VECTOR_ZERO;
}

Player::~Player(void)
{
}

void Player::InitLoad(void)
{
	transform_.SetModel(resMng_.LoadModelDuplicate(
		ResourceManager::SRC::PLAYER));

	
}

void Player::InitTransform(void)
{
	static float SIZE = 2.5f;
	transform_.scl = { SIZE,SIZE,SIZE };
	transform_.quaRot = Quaternion::Identity();
	transform_.quaRotLocal = Quaternion::Mult(transform_.quaRot,
		Quaternion::Euler(0, AsoUtility::Deg2RadF(180), 0));

	transform_.pos = { 0.0f,0.0f,0.0f };
	
}

void Player::InitCollider(void)
{
	// 主に地面との衝突で仕様する線分コライダ
	ColliderLine* colLine = new ColliderLine(
		ColliderBase::TAG::PLAYER, &transform_,
		COL_LINE_START_LOCAL_POS, COL_LINE_END_LOCAL_POS);
	ownColliders_.emplace(static_cast<int>(COLLIDER_TYPE::LINE), colLine);

	// 主に壁や木などの衝突で仕様するカプセルコライダ
	ColliderCapsule* colCapsule = new ColliderCapsule(
		ColliderBase::TAG::PLAYER, &transform_,
		COL_CAPSULE_TOP_LOCAL_POS, COL_CAPSULE_DOWN_LOCAL_POS,
		COL_CAPSULE_RADIUS);
	ownColliders_.emplace(static_cast<int>(COLLIDER_TYPE::CAPSULE), colCapsule);

}

void Player::InitAnimation(void)
{
	anim_ = new AnimationController(transform_.modelId);
	anim_->Add((int)STATE::IDLE, 30.0f, "Data/Model/Player/Jaz/JazIdle.mv1");
	anim_->Add((int)STATE::RUN, 30.0f, "Data/Model/Player/Jaz/jazWalk.mv1");
	anim_->Add((int)STATE::FAST_RUN, 30.0f, "Data/Model/Player/Jaz/FastRun.mv1");
	anim_->Add((int)STATE::JUMP, 60.0f, "Data/Model/Player/Jaz/jazJump.mv1");
	anim_->Add((int)STATE::DANCE, 60.0f, "Data/Model/Player/Jaz/Dance.mv1");

	anim_->Play((int)STATE::IDLE);

}

void Player::InitPost(void)
{
	transform_.Update();
	isDead_ = false;
}

void Player::ProcessMove(void)
{
	auto& ins = InputManager::GetInstance();

	// カメラの角度を取得
	/*VECTOR camAngles =
		SceneManager::GetInstance().GetCamera()->GetAngles();*/

	VECTOR dir = AsoUtility::VECTOR_ZERO;

	// ゲームパッドが接続されている数で処理を分ける
	if (GetJoypadNum() == 0)
	{
		// キーボード操作
		if (ins.IsNew(KEY_INPUT_W)) { dir = AsoUtility::DIR_F; }
		if (ins.IsNew(KEY_INPUT_A)) { dir = AsoUtility::DIR_L; }
		if (ins.IsNew(KEY_INPUT_S)) { dir = AsoUtility::DIR_B; }
		if (ins.IsNew(KEY_INPUT_D)) { dir = AsoUtility::DIR_R; }
	}
	else
	{
		// ゲームパッド操作
		// 接続されているゲームパッド１の情報を取得
		InputManager::JOYPAD_IN_STATE padState =
			ins.GetJPadInputState(InputManager::JOYPAD_NO::PAD1);
		// アナログキーの入力値から方向を取得
		dir = ins.GetDirectionXZAKey(padState.AKeyLX, padState.AKeyLY);

	}

	// WASDでカメラを移動させる

	if (!AsoUtility::EqualsVZero(dir))
	{
		//// XYZの回転行列
		//// XZ平面移動にする場合は、XZの回転を考慮しないようにする
		//MATRIX mat = MGetIdent();
		////mat = MMult(mat, MGetRotX(camAngles.x));
		//mat = MMult(mat, MGetRotY(camAngles.y));
		////mat = MMult(mat, MGetRotZ(camAngles.z));

		//// 回転行列を使用して、ベクトルを回転させる
		//moveDir_ = VTransform(dir, mat);

		// Y軸のみのカメラ角度を取得
		Quaternion cameraRot = scnMng_.GetCamera()->GetQuaRotY();
		// 移動方向をカメラに合わせる
		moveDir_ = Quaternion::PosAxis(cameraRot, dir);


		//if (CheckHitKey(KEY_INPUT_LSHIFT) 
		//	|| ins.GetJPadInputState(InputManager::JOYPAD_NO::PAD1).ButtonsNew[4])
		//{
		//	movePow_ = VScale(moveDir_, SPEED_DASH);
		//	if (!isJump_)
		//	{
		//		anim_->Play((int)STATE::FAST_RUN);
		//	}
		//}
		//else
		{
			movePow_ = VScale(moveDir_, SPEED_MOVE);
			if (!isJump_)
			{
				anim_->Play((int)STATE::RUN);
			}
		}

	}
	else
	{
		movePow_ = VScale(dir, SPEED_MOVE);
		// ジャンプ中はアニメーションを変えない
		if (!isJump_)
		{
			anim_->Play((int)STATE::IDLE);
		}
	}
}

void Player::ProcessJump(void)
{
	auto& ins = InputManager::GetInstance();

	// 持続ジャンプ処理
	bool isHitKeyNew =
		ins.IsNew(KEY_INPUT_BACKSLASH) ||
		ins.IsPadBtnNew(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN);

	if (isHitKeyNew)
	{
		stepJump_ += scnMng_.GetDeltaTime();

		// ★ここが今回の if の条件
		if (isJump_ && stepJump_ < TIME_JUMP_INPUT)
		{
			float jumpSpeed = POW_JUMP_KEEP * scnMng_.GetDeltaTime();
			jumpPow_ = VAdd(jumpPow_, VScale(AsoUtility::DIR_U, jumpSpeed));
		}
	}
	else
	{
		// ボタン離したら保持終了
		stepJump_ = TIME_JUMP_INPUT;
	}

	// 初期ジャンプ処理
	bool isHitKey =
		ins.IsTrgDown(KEY_INPUT_BACKSLASH) ||
		ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN);

	if (isHitKey && !isJump_)
	{
		float jumpSpeed = POW_JUMP * scnMng_.GetDeltaTime();
		jumpPow_ = VScale(AsoUtility::DIR_U, jumpSpeed);

		isJump_ = true;
		stepJump_ = 0.0f;

		anim_->Play(static_cast<int>(STATE::JUMP), false);
	}
	
}



void Player::UpdateProcess(void)
{
	// 移動操作
	ProcessMove();
	// ジャンプ処理
	ProcessJump();

	if (transform_.pos.y < -3000.0f)
	{
		SetDead(true);
	}
	else
	{
		SetDead(false);
	}
}

void Player::UpdateProcessPost(void)
{
	auto& ins = InputManager::GetInstance();
	bool isHitKey = ins.IsTrgDown(KEY_INPUT_BACKSLASH)
		|| ins.IsPadBtnTrgDown(
			InputManager::JOYPAD_NO::PAD1,
			InputManager::JOYPAD_BTN::DOWN);
	// ジャンプ
	if (isHitKey && !isJump_)
	{
		// ジャンプ量の計算
		float jumpSpeed = POW_JUMP/* * scnMng_.GetDeltaTime()*/;
		jumpPow_ = VScale(AsoUtility::DIR_U, jumpSpeed);
		isJump_ = true;
		// アニメーション再生
		anim_->Play((int)STATE::JUMP, false);
	}

}

void Player::CollisionReserve()
{
	const bool isJump = (anim_->GetPlayType() == static_cast<int>(STATE::JUMP));

	// LINE コライダーの調整
	auto itLine = ownColliders_.find(static_cast<int>(COLLIDER_TYPE::LINE));
	if (itLine != ownColliders_.end()) {
		auto* colLine = dynamic_cast<ColliderLine*>(itLine->second.get());
		if (colLine) {
			if (isJump) {
				colLine->SetLocalPosStart(COL_LINE_JUMP_START_LOCAL_POS);
				colLine->SetLocalPosEnd(COL_LINE_JUMP_END_LOCAL_POS);
			}
			else {
				colLine->SetLocalPosStart(COL_LINE_START_LOCAL_POS);
				colLine->SetLocalPosEnd(COL_LINE_END_LOCAL_POS);
			}
		}
	}

	// CAPSULE コライダーの調整または生成
	auto itCap = ownColliders_.find(static_cast<int>(COLLIDER_TYPE::CAPSULE));
	if (itCap != ownColliders_.end()) {
		// 既存のカプセルがある → 位置だけ差し替える
		auto* colCap = dynamic_cast<ColliderCapsule*>(itCap->second.get());
		if (colCap) {
			if (isJump) {
				colCap->SetLocalPosTop(COL_CAPSULE_TOP_JUMP_LOCAL_POS);
				colCap->SetLocalPosDown(COL_CAPSULE_DOWN_JUMP_LOCAL_POS);
			}
			else {
				colCap->SetLocalPosTop(COL_CAPSULE_TOP_LOCAL_POS);
				colCap->SetLocalPosDown(COL_CAPSULE_DOWN_LOCAL_POS);
			}
			colCap->SetRadius(COL_CAPSULE_RADIUS);
		}
	}
	else {
		// なければ生成して挿入
		if (isJump) {
			ownColliders_.emplace(
				static_cast<int>(COLLIDER_TYPE::CAPSULE),
				std::make_unique<ColliderCapsule>(
					ColliderBase::TAG::PLAYER, &transform_,
					COL_CAPSULE_TOP_JUMP_LOCAL_POS,
					COL_CAPSULE_DOWN_JUMP_LOCAL_POS,
					COL_CAPSULE_RADIUS
				)
			);
		}
		else {
			ownColliders_.emplace(
				static_cast<int>(COLLIDER_TYPE::CAPSULE),
				std::make_unique<ColliderCapsule>(
					ColliderBase::TAG::PLAYER, &transform_,
					COL_CAPSULE_TOP_LOCAL_POS,
					COL_CAPSULE_DOWN_LOCAL_POS,
					COL_CAPSULE_RADIUS
				)
			);
		}
	}
}

