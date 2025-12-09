#include "Bar.h"
#include "../../Manager/ResourceManager.h"
#include "../../Utility/AsoUtility.h"
#include "../Collider/ColliderModel.h"
#include "../Collider/ColliderBase.h"

Bar::Bar(void)
{
	//speed_ = 180.0f;
}

void Bar::Update(void)
{
	TimeState(timeState_);

	transform_.quaRotLocal = Quaternion::Mult(
		transform_.quaRot,
		Quaternion::Euler(0, AsoUtility::Deg2RadF(speed_), 0));

	transform_.Update();

	// ★★★ ここでコライダーを更新する（超重要） ★★★
	for (auto& col : ownColliders_)
	{
		col.second->Update();   // ColliderModel なら内部で MV1RefreshCollInfo などを行う
	}

	time_++;

}



void Bar::Release(void)
{
}

void Bar::TimeState(TIME_STATE timeState)
{
	timeState_ = timeState;
	switch (timeState_)
	{
	case Bar::TIME_STATE::START:
		UpdateStart();
		break;
	case Bar::TIME_STATE::HALF:
		UpdateHalf();
		break;
	case Bar::TIME_STATE::FINAL:
		UpdateFinal();
		break;
	}
}

void Bar::InitLoad(void)
{
	transform_.SetModel(resMng_.LoadModelDuplicate(
		ResourceManager::SRC::BarDown));
}

void Bar::InitTransform(void)
{
	static float SIZE = 0.1f;
	transform_.scl = { SIZE,SIZE,SIZE };
	transform_.quaRot = Quaternion::Identity();
	transform_.quaRotLocal = Quaternion::Identity();

	transform_.pos = { 0.0f,-80.0f,0.0f };

	transform_.Update();

}

void Bar::InitCollider(void)
{
	transform_.Update();
	// DxLib側の衝突情報セットアップ
	MV1SetupCollInfo(transform_.modelId);
	// モデルのコライダ
	ColliderModel* colModel =
		new ColliderModel(ColliderBase::TAG::STAGE, &transform_);
	ownColliders_.emplace(static_cast<int>(COLLIDER_TYPE::MODEL), colModel);
}

void Bar::InitAnimation(void)
{
}

void Bar::InitPost(void)
{
	time_ = 0;
	TimeState(TIME_STATE::START);
}

void Bar::UpdateStart(void)
{
	const float rotSpeed = AsoUtility::Deg2RadF(50.0f);
	speed_ -= rotSpeed;

	if (time_ > 1000) { timeState_ = TIME_STATE::HALF; time_ = 0; }
}

void Bar::UpdateHalf(void)
{
	const float rotSpeed = AsoUtility::Deg2RadF(200.0f);
	speed_ -= rotSpeed;

	if (time_ > 900) { timeState_ = TIME_STATE::FINAL; time_ = 0;}

}

void Bar::UpdateFinal(void)
{
	const float rotSpeed = AsoUtility::Deg2RadF(30.0f);
	speed_ -= rotSpeed;

	if (time_ > 1500) { timeState_ = TIME_STATE::START; time_ = 0;}
}
