#pragma once
#include "../framework.h"


class Camera
{
public:

	// カメラの初期位置
	static constexpr VECTOR INIT_CAMERA_POS = { 0.0f, 9000.0f, -1000.0f };

	Camera();
	~Camera();
	void Init(void);
	void Update();
	void Draw(void);
	void Release(void);
	VECTOR GetCameraPos(void);
	void SetAngle(void);
	

private:

	VECTOR cameraPos_;				//カメラ位置
	VECTOR targetPos_;				//角度

	

};