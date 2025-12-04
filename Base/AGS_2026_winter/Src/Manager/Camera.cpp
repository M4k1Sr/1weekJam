#include "Camera.h"
#include "../Application.h"

Camera::Camera()
{

	cameraPos_ = { 0,0,0 };

}

Camera::~Camera()
{
}

void Camera::Init(void)
{
	cameraPos_ = INIT_CAMERA_POS;				//カメラ位置

}

void Camera::Update()
{

	//cameraPos_.z = player_->GetPos().z;		//カメラのプレイヤー追尾
	SetAngle();

}

void Camera::Draw(void)
{

	//カメラの設定
	//SetDrawScreenの後、描画処理の前にカメラを設定すること
	SetCameraPositionAndAngle(cameraPos_, 85  * DX_PI_F / 180.0f, 0.0f, 0.0f);

}

void Camera::Release(void)
{
}

VECTOR Camera::GetCameraPos(void)
{
	return cameraPos_;
}

//VECTOR Camera::Rei(float y)
//{
//
//
//	//// マウス位置を取得
//	//Vector2 pos = mouse_->GetMousePos();
//
//	//// 画面座標 → 正規化
//	//float ndcX = (2.0f * pos.x / Application::SCREEN_SIZE_X) - 1.0f;
//	//float ndcY = 1.0f - (2.0f * pos.y / Application::SCREEN_SIZE_Y);
//
//	//// FOVとアスペクト
//	//float fov = DX_PI_F / 4.0f;
//	//float aspect = Application::SCREEN_SIZE_X / Application::SCREEN_SIZE_Y;
//
//	//// スクリーン上のレイ
//	//float nearZ = 1.0f;
//	//float nearX = tanf(fov / 2.0f) * aspect * ndcX * nearZ;
//	//float nearY = tanf(fov / 2.0f) * ndcY * nearZ;
//
//	//// カメラ座標系
//	//VECTOR camForward = VGet(0, -1, 0);  // 真下向き
//	//VECTOR camRight = VGet(1, 0, 0);
//	//VECTOR camUp = VGet(0, 0, 1);
//
//	//// レイ方向
//	//VECTOR rayDir = VNorm(VAdd(VAdd(VScale(camRight, nearX), VScale(camUp, nearY)), camForward));
//
//
//
//	//// 指定されたY座標で交差する点を計算
//	//float t = (y - cameraPos_.y) / rayDir.y;
//	//VECTOR hitPos = VAdd(cameraPos_, VScale(rayDir, t));
//
//	//return hitPos;
//
//	
//
//}

void Camera::SetAngle(void)
{

	// プレイヤー位置
	/*VECTOR playerPos = player_->GetPos();

	VECTOR hitPos = Rei(playerPos.y);*/

	//// XZ平面だけでベクトルを作る
	//float dx = hitPos.x - playerPos.x;
	//float dz = hitPos.z - playerPos.z;

	//// 角度計算
	//float targetAngleY = atan2f(-dx, -dz);

	//// なめらか補間
	//float currentAngleY = player_->GetPlayerAngle();
	//float diff = targetAngleY - currentAngleY;

	//if (diff > DX_PI_F) diff -= DX_PI_F * 2.0f;
	//if (diff < -DX_PI_F) diff += DX_PI_F * 2.0f;

	//float smoothSpeed = 0.1f;
	//currentAngleY += diff * smoothSpeed;

	//VECTOR toTarget = VSub(hitPos, playerPos);
	//toTarget.y = 0;  // XZ平面に制限
	//VECTOR faceDir = VNorm(toTarget);
	//float angle = atan2f(-faceDir.x, -faceDir.z);

	//// プレイヤーにセット
	//player_->SetPlayerAngle(angle);

}

//MATRIX Camera::GetCameraRotationMatrix()
//{
//	//MATRIX rotationMatrix;
//	//float angleY = player_->GetPlayerAngle();  // プレイヤーのY軸回転角度を取得
//
//	//// Y軸回転行列を手動で計算
//	//rotationMatrix.m[0][0] = cosf(angleY);  // cos(θ)
//	//rotationMatrix.m[0][1] = 0.0f;
//	//rotationMatrix.m[0][2] = sinf(angleY);  // sin(θ)
//	//rotationMatrix.m[0][3] = 0.0f;
//
//	//rotationMatrix.m[1][0] = 0.0f;
//	//rotationMatrix.m[1][1] = 1.0f;
//	//rotationMatrix.m[1][2] = 0.0f;
//	//rotationMatrix.m[1][3] = 0.0f;
//
//	//rotationMatrix.m[2][0] = -sinf(angleY);  // -sin(θ)
//	//rotationMatrix.m[2][1] = 0.0f;
//	//rotationMatrix.m[2][2] = cosf(angleY);   // cos(θ)
//	//rotationMatrix.m[2][3] = 0.0f;
//
//	//rotationMatrix.m[3][0] = 0.0f;
//	//rotationMatrix.m[3][1] = 0.0f;
//	//rotationMatrix.m[3][2] = 0.0f;
//	//rotationMatrix.m[3][3] = 1.0f;
//
//	//// レイの方向を回転行列で変換
//	//VECTOR rayDir = VGet(0, -1, 0);  // 初期のレイ方向
//	//rayDir = VTransform(rayDir, rotationMatrix);  // 回転行列をレイの方向に適用
//
//
//}



