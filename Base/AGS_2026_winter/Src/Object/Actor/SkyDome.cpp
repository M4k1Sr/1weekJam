#include "SkyDome.h"
#include "../../Manager/ResourceManager.h"
#include "../../Utility/AsoUtility.h"

SkyDome::SkyDome(void)
{
	speed_ = 180.0f;
}

void SkyDome::Update(void)
{
	const float rotSpeed = AsoUtility::Deg2RadF(15.5f);
	speed_-= rotSpeed;

	skyDome_.quaRotLocal = Quaternion::Mult(skyDome_.quaRot,
		Quaternion::Euler(0, AsoUtility::Deg2RadF(speed_), AsoUtility::Deg2RadF(0)));
	skyDome_.Update();
}

void SkyDome::Draw(void)
{
	SetUseLighting(FALSE);
	MV1DrawModel(skyDome_.modelId);
	SetUseLighting(TRUE);

}

void SkyDome::Release(void)
{
}

void SkyDome::InitLoad(void)
{
	skyDome_.SetModel(resMng_.LoadModelDuplicate(
		ResourceManager::SRC::SKY_DOME));
}

void SkyDome::InitTransform(void)
{
	skyDome_.scl = { 100.0f,100.0f,100.0f };
	skyDome_.quaRot = Quaternion::Identity();
	skyDome_.quaRotLocal = Quaternion::Mult(skyDome_.quaRot,
		Quaternion::Euler(0, AsoUtility::Deg2RadF(180), 0));

	skyDome_.pos = { 0.0f,0.0f,0.0f };
}

void SkyDome::InitCollider(void)
{
}

void SkyDome::InitAnimation(void)
{
}

void SkyDome::InitPost(void)
{
	
	// Zバッファ無効(突き抜け対策)
	MV1SetUseZBuffer(skyDome_.modelId, false);
	MV1SetWriteZBuffer(skyDome_.modelId, false);
	skyDome_.Update();
}
