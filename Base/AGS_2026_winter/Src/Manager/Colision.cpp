//#include "Colision.h"
//#include "../Object/Player/Player.h"
//#include "../Object/Enemy/EnemyManager.h"
//#include "../Object/Blast/BlastManager.h"
//#include "../Object/Player/PlayerShot.h"
//#include "../Object/UI/System.h"
//#include "../Object/Stage/WallManager.h"
//#include "../Object/Stage/Stage.h"
//#include "../Object/Enemy/Enemy.h"
//#include "../Manager/SceneManager.h"
//#include "../Object/UI/SE.h"
//#include "../Utility/AsoUtility.h"
//
//
//Colision::Colision()
//{
//}
//
//Colision::~Colision()
//{
//}
//
//void Colision::Init(Player* player, EnemyManager* enemy, BlastManager* blast, PlayerShot* pShot, System* system, WallManager* wallMange, Stage* stage)
//{
//
//	player_ = player;
//	enemy_ = enemy;
//	blast_ = blast;
//	pShot_ = pShot;
//	system_ = system;
//	wallMange_ = wallMange;
//	stage_ = stage;
//	
//
//	cDistance = 0.0f;				//プレイヤーと敵の中心の距離
//
//	SE::GetInstance().Load(SOUND_TYPE::SHOT_REFLECT, "Data/SE/Reflect.mp3");
//	SE::GetInstance().Load(SOUND_TYPE::SHOT_WALL_HIT, "Data/SE/LastReflect.mp3");
//	SE::GetInstance().Load(SOUND_TYPE::SHOT_EXPLOSION, "Data/SE/mini_bomb2.mp3");
//	//SE::GetInstance().SetVolume(SOUND_TYPE::SHOT_REFLECT, 255);
//
//}
//
//void Colision::InitMulti(Player* player, Player* player2, EnemyManager* enemy, BlastManager* blast, PlayerShot* pShot, PlayerShot* pShot2, System* system, WallManager* wallMange, Stage* stage)
//{
//	player_ = player;
//	player2_ = player2;
//	enemy_ = enemy;
//	blast_ = blast;
//	pShot_ = pShot;
//	pShot2_ = pShot2;
//	system_ = system;
//	wallMange_ = wallMange;
//	stage_ = stage;
//	SE::GetInstance().Load(SOUND_TYPE::SHOT_REFLECT, "Data/SE/Reflect.mp3");
//	SE::GetInstance().Load(SOUND_TYPE::SHOT_WALL_HIT, "Data/SE/LastReflect.mp3");
//	SE::GetInstance().Load(SOUND_TYPE::SHOT_EXPLOSION, "Data/SE/mini_bomb2.mp3");
//	cDistance = 0.0f;
//}
//
//void Colision::Update(void)
//{
//
//	//プレイヤーと球の衝突判定
//	if (player_->isAlive() && pShot_->GetIsAlive())
//	{
//
//		VECTOR distance;
//		distance.x = player_->GetPos().x - pShot_->GetPos().x;
//		distance.y = player_->GetPos().y - pShot_->GetPos().y;
//		distance.z = player_->GetPos().z - pShot_->GetPos().z;
//
//		float dis = distance.x * distance.x
//			+ distance.y * distance.y + distance.z * distance.z;
//
//		//お互いの中心の当たり判定の距離
//		cDistance = sqrtf(dis);
//
//		//プレイヤーと敵の半径の合計
//		total = Player::PLAYER_RADIUS + PlayerShot::PLAYER_SHOT_RADIUS;
//
//		//斜辺が半径の合計を超えていると衝突
//		if (cDistance <= total)
//		{
//			if (pShot_->GetReflectNum() >= 1)
//			{
//				player_->setIsAlive(false);
//				// 爆発アニメーション開始判定を更新
//				/*blast_->setIsBlast(true);*/
//				// 爆発アニメーションの座標を更新
//				blast_->AddBlast(player_->GetPos());
//				//残機を減らす
//				SE::GetInstance().Play(SOUND_TYPE::SHOT_EXPLOSION);
//				SE::GetInstance().Stop(SOUND_TYPE::PLAYER_MOVE);
//				SE::GetInstance().Stop(SOUND_TYPE::PLAYER_MOVE2);
//				player_->Damage(1);
//				system_->SetWins(1);
//				system_->SetWin2P(1);
//			}
//		}
//	}
//
//	
//
//	//マルチプレイ専用処理
//	if (SceneManager::playMode_ == PLAY_MODE::MULTI)
//	{
//		//プレイヤーと球の衝突判定
//		if (player2_->isAlive() && pShot2_->GetIsAlive())
//		{
//
//			VECTOR distance;
//			distance.x = player2_->GetPos().x - pShot2_->GetPos().x;
//			distance.y = player2_->GetPos().y - pShot2_->GetPos().y;
//			distance.z = player2_->GetPos().z - pShot2_->GetPos().z;
//
//			float dis = distance.x * distance.x
//				+ distance.y * distance.y + distance.z * distance.z;
//
//			//お互いの中心の当たり判定の距離
//			cDistance = sqrtf(dis);
//
//			//プレイヤーと敵の半径の合計
//			total = Player::PLAYER_RADIUS + PlayerShot::PLAYER_SHOT_RADIUS;
//
//			//斜辺が半径の合計を超えていると衝突
//			if (cDistance <= total)
//			{
//				if (pShot2_->GetReflectNum() >= 1)
//				{
//					player2_->setIsAlive(false);
//					// 爆発アニメーション開始判定を更新
//					/*blast_->setIsBlast(true);*/
//					// 爆発アニメーションの座標を更新
//					blast_->AddBlast(player2_->GetPos());
//					player2_->Damage(1);
//					SE::GetInstance().Play(SOUND_TYPE::SHOT_EXPLOSION);
//					SE::GetInstance().Stop(SOUND_TYPE::PLAYER_MOVE);
//					SE::GetInstance().Stop(SOUND_TYPE::PLAYER_MOVE2);
//					system_->SetWins(1);
//					system_->SetWin1P(1);
//				}
//			}
//		}
//
//		
//		// プレイヤー同士の弾の衝突判定
//		if (CollisionPlayer(player_, pShot2_))
//		{
//			system_->SetWin2P(1);
//		}
//		if (CollisionPlayer(player2_, pShot_))
//		{
//			system_->SetWin1P(1);
//		}
//	}
//
//	if (SceneManager::playMode_ == PLAY_MODE::SOLO)
//	{
//
//		for (auto* enemy : enemy_->GetEnemy())
//		{
//			//プレイヤーの弾と敵との衝突判定
//			if (pShot_->GetIsAlive() && enemy->isAlive())
//			{
//				// 球体と球体の衝突判定
//				// ２つの座標間の距離をピタゴラスの定理で算出
//				VECTOR distance;
//				distance.x = pShot_->GetPos().x - enemy->GetPos().x;
//				distance.y = pShot_->GetPos().y - enemy->GetPos().y;
//				distance.z = pShot_->GetPos().z - enemy->GetPos().z;
//				float dis = distance.x * distance.x
//					+ distance.y * distance.y + distance.z * distance.z;
//				// お互いの半径を合計する
//				float radius = PlayerShot::PLAYER_SHOT_RADIUS + Enemy::ENEMY_RADIUS;
//				// 合計した半径の２乗よりも、
//				// ２つの座標間の距離が小さければ球体は衝突している
//				if (radius * radius > dis)
//				{
//					enemy->setIsAlive(false);
//					pShot_->SetAlive(false);
//					//倒したエネミーの数を更新
//					system_->SetCount(1);
//					// 爆発アニメーション開始判定を更新
//					/*blast_->setIsBlast(true);*/
//					// 爆発アニメーションの座標を更新
//					blast_->AddBlast(enemy->GetPos());
//					SE::GetInstance().Play(SOUND_TYPE::SHOT_EXPLOSION);
//				}
//			}
//		}
//
//
//		for (auto* enemy : enemy_->GetEnemy())
//		{
//			//プレイヤーと敵弾との衝突判定
//			if (player_->isAlive() && enemy->isSAlive())
//			{
//				// 球体と球体の衝突判定
//				// ２つの座標間の距離をピタゴラスの定理で算出
//				VECTOR distance;
//				distance.x = player_->GetPos().x - enemy->GetEShotPos().x;
//				distance.y = player_->GetPos().y - enemy->GetEShotPos().y;
//				distance.z = player_->GetPos().z - enemy->GetEShotPos().z;
//				float dis = distance.x * distance.x
//					+ distance.y * distance.y + distance.z * distance.z;
//				// お互いの半径を合計する
//				float radius = PlayerShot::PLAYER_SHOT_RADIUS + Player::PLAYER_RADIUS;
//				// 合計した半径の２乗よりも、
//				// ２つの座標間の距離が小さければ球体は衝突している
//				if (radius * radius > dis)
//				{
//					// エネミーの生存判定を更新
//					enemy->setIsSAlive(false);
//					//倒したエネミーの数を更新
//					player_->setIsAlive(false);
//					// 爆発アニメーション開始判定を更新
//					/*blast_->setIsBlast(true);*/
//					// 爆発アニメーションの座標を更新
//					blast_->AddBlast(player_->GetPos());
//					//残機を減らす
//					player_->Damage(1);
//				}
//			}
//		}
//
//		////敵自身の弾の当たり判定
//		//for (auto* enemy : enemy_->GetEnemy())
//		//{
//		//	//プレイヤーの弾と敵との衝突判定
//		//	if (enemy->isSAlive() && enemy->isAlive())
//		//	{
//		//		// 球体と球体の衝突判定
//		//		// ２つの座標間の距離をピタゴラスの定理で算出
//		//		VECTOR distance;
//		//		distance.x = enemy->GetEShotPos().x - enemy->GetPos().x;
//		//		distance.y = enemy->GetEShotPos().y - enemy->GetPos().y;
//		//		distance.z = enemy->GetEShotPos().z - enemy->GetPos().z;
//		//		float dis = distance.x * distance.x
//		//			+ distance.y * distance.y + distance.z * distance.z;
//		//		// お互いの半径を合計する
//		//		float radius = PlayerShot::PLAYER_SHOT_RADIUS + Enemy::ENEMY_RADIUS;
//		//		// 合計した半径の２乗よりも、
//		//		// ２つの座標間の距離が小さければ球体は衝突している
//		//		if (radius * radius > dis)
//		//		{
//		//			if (enemy->GetReflectNum() >= 1)
//		//			{
//		//				enemy->setIsAlive(false);
//		//				enemy->setIsSAlive(false);
//		//				//倒したエネミーの数を更新
//		//				system_->SetCount(1);
//		//				// 爆発アニメーション開始判定を更新
//		//				/*blast_->setIsBlast(true);*/
//		//				// 爆発アニメーションの座標を更新
//		//				blast_->AddBlast(enemy->GetPos());
//		//			}
//		//		
//		//		}
//		//	}
//		//}
//
//
//		//壁とエネミー弾の衝突判定
//		CollisionWallEShot();
//
//	}
//
//	//ソロプレイ専用処理
//	if (SceneManager::playMode_ == PLAY_MODE::SOLO)
//	{
//		//壁とプレイヤーの衝突判定
//		CollisionWall(player_);
//
//		//壁とプレイヤー弾の衝突判定
//		CollisionWallShot(pShot_);
//
//		CollisionEnemyBullet();
//	}
//
//	//マルチプレイ専用処理
//	if (SceneManager::playMode_ == PLAY_MODE::MULTI)
//	{
//		//壁とプレイヤーの衝突判定
//		CollisionWall(player_);
//
//		//壁とプレイヤー弾の衝突判定
//		CollisionWallShot(pShot_);
//
//		//壁とプレイヤーの衝突判定
//		CollisionWall(player2_);
//
//		//壁とプレイヤー弾の衝突判定
//		CollisionWallShot(pShot2_);
//
//		CollisionBullet();
//	}
//
//
//	
//
//}
//
//void Colision::Draw(void)
//{
//#ifdef _DEBUG
//	// 地面との衝突用線分
//	//DrawSphere3D(lineTopPosZUp_, 20.0f, 10, 0x00ff00, 0x00ff00, true);
//	//DrawSphere3D(lineDownPosZUp_, 20.0f, 10, 0x00ff00, 0x00ff00, true);
//	//DrawLine3D(lineTopPosZUp_, lineDownPosZUp_, 0xff0000);
//
//	//DrawSphere3D(lineTopPosXC_, 20.0f, 10, 0x00ff00, 0x00ff00, true);
//	//DrawSphere3D(lineDownPosXC_, 20.0f, 10, 0x00ff00, 0x00ff00, true);
//	//DrawLine3D(lineTopPosZUp_, lineDownPosZUp_, 0xff0000);
//
//	//DrawSphere3D(lineTopPosZDown_, 20.0f, 10, 0x00ff00, 0x00ff00, true);
//	//DrawSphere3D(lineDownPosZDown_, 20.0f, 10, 0x00ff00, 0x00ff00, true);
//	//DrawLine3D(lineTopPosZUp_, lineDownPosZUp_, 0xff0000);
//
//#endif // _DEBUG
//}
//
//void Colision::Release(void)
//{
//}
//
//Vector2 Colision::World2MapPos()
//{
//	Vector2 ret;
//
//	int mapX = pShot_->GetPos().x / WallManager::SIZE_BLOCK;
//	int mapY = pShot_->GetPos().z / WallManager::SIZE_BLOCK;
//
//	ret.x = mapX+6;
//	ret.y = mapY+5;
//
//	return ret;
//}
//
//void Colision::CollisionWall(Player* player)
//{
//
//	// ステージブロックとプレイヤーの衝突
//	VECTOR playerPos = player->GetPos();
//	playerPos.y += 100;
//
//	{//プレイヤーの縦上側の判定
//
//		// 線分の上座標
//		VECTOR topPos = playerPos;
//		topPos.x = playerPos.x + (Player::COLLISION_LEN_Z);
//		topPos.z = playerPos.z + Player::COLLISION_LEN_Z;
//		lineTopPosZUp_ = topPos;
//		// 線分の下座標
//		VECTOR downPos = playerPos;
//		downPos.x = playerPos.x - Player::COLLISION_LEN_Z;
//		downPos.z = playerPos.z + Player::COLLISION_LEN_Z;
//		lineDownPosZUp_ = downPos;
//
//		// 線分とブロックモデルの衝突判定
//		MV1_COLL_RESULT_POLY result;
//		if (wallMange_->IsCollisionLine(topPos, downPos, &result))
//		{
//			//プレイヤーに衝突座標を渡す
//			player->CollisionWall(result.HitPosition);
//		}
//		//ステージとの判定
//		if (stage_->IsCollisionLine(topPos, downPos, &result))
//		{
//			//プレイヤーに衝突座標を渡す
//			player->CollisionWall(result.HitPosition);
//		}
//
//	}
//
//	{//プレイヤーの縦上下側の判定
//
//	// 線分の上座標
//		VECTOR topPosd = playerPos;
//		topPosd.x = playerPos.x + (Player::COLLISION_LEN_Z);
//		topPosd.z = playerPos.z - Player::COLLISION_LEN_Z;
//		lineTopPosZDown_ = topPosd;
//		// 線分の下座標
//		VECTOR downPosd = playerPos;
//		downPosd.x = playerPos.x - Player::COLLISION_LEN_Z;
//		downPosd.z = playerPos.z - Player::COLLISION_LEN_Z;
//		lineDownPosZDown_ = downPosd;
//
//		// 線分とブロックモデルの衝突判定
//		MV1_COLL_RESULT_POLY result2;
//		if (wallMange_->IsCollisionLine(topPosd, downPosd, &result2))
//		{
//			//プレイヤーに衝突座標を渡す
//			player->CollisionWall(result2.HitPosition);
//		}
//		//ステージとの判定
//		if (stage_->IsCollisionLine(topPosd, downPosd, &result2))
//		{
//			//プレイヤーに衝突座標を渡す
//			player->CollisionWall(result2.HitPosition);
//		}
//
//	}
//
//	{//プレイヤーの縦中央の判定
//
//	// 線分の上座標
//		VECTOR topPosz = playerPos;
//		topPosz.z = playerPos.z + (Player::COLLISION_LEN_Z);
//		lineTopPosXC_ = topPosz;
//		// 線分の下座標
//		VECTOR downPosz = playerPos;
//		downPosz.z = playerPos.z - Player::COLLISION_LEN_Z;
//		lineDownPosXC_ = downPosz;
//		// 線分とブロックモデルの衝突判定
//		MV1_COLL_RESULT_POLY result3;
//		if (wallMange_->IsCollisionLine(topPosz, downPosz, &result3))
//		{
//			//プレイヤーに衝突座標を渡す
//			player->CollisionWall(result3.HitPosition);
//		}
//		//ステージとの判定
//		if (stage_->IsCollisionLine(topPosz, downPosz, &result3))
//		{
//			//プレイヤーに衝突座標を渡す
//			player->CollisionWall(result3.HitPosition);
//		}
//
//	}
//
//
//	//VECTOR prePos = player_->GetPrePos();
//
//	//// 今回のフレームの移動量
//	//VECTOR diff = VSub(playerPos, prePos);
//
//	//// 線分とブロックモデルの衝突判定
//	//playerPos.y += 5.0f;
//	//prePos.y += 5.0f;
//	//MV1_COLL_RESULT_POLY result2;
//	//if (wallMange_->IsCollisionLine(playerPos, prePos, &result2))
//	//{
//	//	// プレイヤーに衝突座標を渡す
//	//	player_->CollisionWall(result2.HitPosition);
//	//}
//
//
//
//}
//
//void Colision::CollisionWallShot(PlayerShot* pShot)
//{
//
//	VECTOR shotPos = pShot->GetPos();
//	shotPos.y += 100;
//
//	{//縦上側の判定
//
//		// 線分の上座標
//		VECTOR topPos = shotPos;
//		topPos.x = shotPos.x + PlayerShot::COLLISION_LEN;
//		topPos.z = shotPos.z + PlayerShot::COLLISION_LEN;
//		// 線分の下座標
//		VECTOR downPos = shotPos;
//		downPos.x = shotPos.x - PlayerShot::COLLISION_LEN;
//		downPos.z = shotPos.z + PlayerShot::COLLISION_LEN;
//		
//
//		// 線分とブロックモデルの衝突判定
//		MV1_COLL_RESULT_POLY result;
//		if (wallMange_->IsCollisionLine(topPos, downPos, &result))
//		{
//			//衝突座標を渡す
//			pShot->Collision(result.HitPosition,result.HitFlag, result.Normal);
//			if (pShot->GetReflectNum() >= pShot->GetReflectNumMax())
//			{
//				// 壁に当たった時のSEを再生
//				SE::GetInstance().Play(SOUND_TYPE::SHOT_WALL_HIT);
//				blast_->AddBlast(pShot->GetPos());
//			}
//			else
//			{
//				// 反射音を再生
//				SE::GetInstance().Play(SOUND_TYPE::SHOT_REFLECT);
//			}
//		}
//		//ステージとの判定
//		if (stage_->IsCollisionLine(topPos, downPos, &result))
//		{
//			//衝突座標を渡す
//			pShot->Collision(result.HitPosition,result.HitFlag, result.Normal);
//			if (pShot->GetReflectNum() >= pShot->GetReflectNumMax())
//			{
//				// 壁に当たった時のSEを再生
//				SE::GetInstance().Play(SOUND_TYPE::SHOT_WALL_HIT);
//				blast_->AddBlast(pShot->GetPos());
//			}
//			else
//			{
//				// 反射音を再生
//				SE::GetInstance().Play(SOUND_TYPE::SHOT_REFLECT);
//			}
//		}
//
//	}
//
//	{//縦上下側の判定
//
//	// 線分の上座標
//		VECTOR topPosd = shotPos;
//		topPosd.x = shotPos.x + PlayerShot::COLLISION_LEN;
//		topPosd.z = shotPos.z - PlayerShot::COLLISION_LEN;
//	
//		// 線分の下座標
//		VECTOR downPosd = shotPos;
//		downPosd.x = shotPos.x - PlayerShot::COLLISION_LEN;
//		downPosd.z = shotPos.z - PlayerShot::COLLISION_LEN;
//	
//
//		// 線分とブロックモデルの衝突判定
//		MV1_COLL_RESULT_POLY result2;
//		if (wallMange_->IsCollisionLine(topPosd, downPosd, &result2))
//		{
//			//衝突座標を渡す
//			pShot->Collision(result2.HitPosition, result2.HitFlag, result2.Normal);
//			if (pShot->GetReflectNum() >= pShot->GetReflectNumMax())
//			{
//				// 壁に当たった時のSEを再生
//				SE::GetInstance().Play(SOUND_TYPE::SHOT_WALL_HIT);
//				blast_->AddBlast(pShot->GetPos());
//			}
//			else
//			{
//				// 反射音を再生
//				SE::GetInstance().Play(SOUND_TYPE::SHOT_REFLECT);
//			}
//		}
//		//ステージとの判定
//		if (stage_->IsCollisionLine(topPosd, downPosd, &result2))
//		{
//			//衝突座標を渡す
//			pShot->Collision(result2.HitPosition, result2.HitFlag, result2.Normal);
//		
//			if (pShot->GetReflectNum() >= pShot->GetReflectNumMax())
//			{
//				// 壁に当たった時のSEを再生
//				SE::GetInstance().Play(SOUND_TYPE::SHOT_WALL_HIT);
//				blast_->AddBlast(pShot->GetPos());
//			}
//			else
//			{
//				// 反射音を再生
//				SE::GetInstance().Play(SOUND_TYPE::SHOT_REFLECT);
//			}
//		}
//
//	}
//
//	// 線分の上座標
//	VECTOR topPosz = shotPos;
//	topPosz.z = shotPos.z + (PlayerShot::COLLISION_LEN);
//
//	// 線分の下座標
//	VECTOR downPosz = shotPos;
//	downPosz.z = shotPos.z - PlayerShot::COLLISION_LEN;
//	// 線分とブロックモデルの衝突判定
//	MV1_COLL_RESULT_POLY result3;
//	if (wallMange_->IsCollisionLine(topPosz, downPosz, &result3))
//	{
//		//衝突座標を渡す
//		pShot->Collision(result3.HitPosition, result3.HitFlag, result3.Normal);
//		// 反射音を再生
//		if (pShot->GetReflectNum() >= pShot->GetReflectNumMax())
//		{
//			// 壁に当たった時のSEを再生
//			SE::GetInstance().Play(SOUND_TYPE::SHOT_WALL_HIT);
//			blast_->AddBlast(pShot->GetPos());
//		}
//		else
//		{
//			// 反射音を再生
//			SE::GetInstance().Play(SOUND_TYPE::SHOT_REFLECT);
//		}
//	}
//	//ステージとの判定
//	if (stage_->IsCollisionLine(topPosz, downPosz, &result3))
//	{
//		//衝突座標を渡す
//		pShot->Collision(result3.HitPosition, result3.HitFlag, result3.Normal);
//	
//		if (pShot->GetReflectNum() >= pShot->GetReflectNumMax())
//		{
//			// 壁に当たった時のSEを再生
//			SE::GetInstance().Play(SOUND_TYPE::SHOT_WALL_HIT);
//			blast_->AddBlast(pShot->GetPos());
//		}
//		else
//		{
//			// 反射音を再生
//			SE::GetInstance().Play(SOUND_TYPE::SHOT_REFLECT);
//		}
//	}
//}
//
//void Colision::CollisionWallEShot(void)
//{
//
//	for (auto* enemy : enemy_->GetEnemy())
//	{
//
//		VECTOR shotPos = enemy->GetEShotPos();
//		shotPos.y += 100;
//
//
//		{//縦上側の判定
//
//			// 線分の上座標
//			VECTOR topPos = shotPos;
//			topPos.x = shotPos.x + PlayerShot::COLLISION_LEN;
//			topPos.z = shotPos.z + PlayerShot::COLLISION_LEN;
//			// 線分の下座標
//			VECTOR downPos = shotPos;
//			downPos.x = shotPos.x - PlayerShot::COLLISION_LEN;
//			downPos.z = shotPos.z + PlayerShot::COLLISION_LEN;
//
//
//			// 線分とブロックモデルの衝突判定
//			MV1_COLL_RESULT_POLY result;
//			if (wallMange_->IsCollisionLine(topPos, downPos, &result))
//			{
//				//衝突座標を渡す
//				enemy->Collision(result.HitPosition, result.HitFlag, result.Normal);
//				// 反射音を再生
//				SE::GetInstance().Play(SOUND_TYPE::SHOT_REFLECT);
//			}
//			//ステージとの判定
//			if (stage_->IsCollisionLine(topPos, downPos, &result))
//			{
//				//衝突座標を渡す
//				enemy->Collision(result.HitPosition, result.HitFlag, result.Normal);
//				// 反射音を再生
//				SE::GetInstance().Play(SOUND_TYPE::SHOT_REFLECT);
//			}
//
//		}
//
//		{//縦上下側の判定
//
//		// 線分の上座標
//			VECTOR topPosd = shotPos;
//			topPosd.x = shotPos.x + PlayerShot::COLLISION_LEN;
//			topPosd.z = shotPos.z - PlayerShot::COLLISION_LEN;
//
//			// 線分の下座標
//			VECTOR downPosd = shotPos;
//			downPosd.x = shotPos.x - PlayerShot::COLLISION_LEN;
//			downPosd.z = shotPos.z - PlayerShot::COLLISION_LEN;
//
//
//			// 線分とブロックモデルの衝突判定
//			MV1_COLL_RESULT_POLY result2;
//			if (wallMange_->IsCollisionLine(topPosd, downPosd, &result2))
//			{
//				//衝突座標を渡す
//				enemy->Collision(result2.HitPosition, result2.HitFlag, result2.Normal);
//				// 反射音を再生
//				SE::GetInstance().Play(SOUND_TYPE::SHOT_REFLECT);
//			}
//			//ステージとの判定
//			if (stage_->IsCollisionLine(topPosd, downPosd, &result2))
//			{
//				//衝突座標を渡す
//				enemy->Collision(result2.HitPosition, result2.HitFlag, result2.Normal);
//				// 反射音を再生
//				SE::GetInstance().Play(SOUND_TYPE::SHOT_REFLECT);
//			}
//
//		}
//
//		// 線分の上座標
//		VECTOR topPosz = shotPos;
//		topPosz.z = shotPos.z + (PlayerShot::COLLISION_LEN);
//
//		// 線分の下座標
//		VECTOR downPosz = shotPos;
//		downPosz.z = shotPos.z - PlayerShot::COLLISION_LEN;
//		// 線分とブロックモデルの衝突判定
//		MV1_COLL_RESULT_POLY result3;
//		if (wallMange_->IsCollisionLine(topPosz, downPosz, &result3))
//		{
//			//衝突座標を渡す
//			enemy->Collision(result3.HitPosition, result3.HitFlag, result3.Normal);
//			// 反射音を再生
//			SE::GetInstance().Play(SOUND_TYPE::SHOT_REFLECT);
//		}
//		//ステージとの判定
//		if (stage_->IsCollisionLine(topPosz, downPosz, &result3))
//		{
//			//衝突座標を渡す
//			enemy->Collision(result3.HitPosition, result3.HitFlag, result3.Normal);
//			// 反射音を再生
//			SE::GetInstance().Play(SOUND_TYPE::SHOT_REFLECT);
//		}
//
//	}
//}
//
//bool Colision::CollisionPlayer(Player* player, PlayerShot* pShot)
//{
//	//プレイヤーと球の衝突判定
//	if (player->isAlive() && pShot->GetIsAlive())
//	{
//
//		VECTOR distance;
//		distance.x = player->GetPos().x - pShot->GetPos().x;
//		distance.y = player->GetPos().y - pShot->GetPos().y;
//		distance.z = player->GetPos().z - pShot->GetPos().z;
//
//		float dis = distance.x * distance.x
//			+ distance.y * distance.y + distance.z * distance.z;
//
//		//お互いの中心の当たり判定の距離
//		cDistance = sqrtf(dis);
//
//		//プレイヤーと敵の半径の合計
//		total = Player::PLAYER_RADIUS + PlayerShot::PLAYER_SHOT_RADIUS;
//
//		//斜辺が半径の合計を超えていると衝突
//		if (cDistance <= total)
//		{
//
//			player->setIsAlive(false);
//			// 爆発アニメーション開始判定を更新
//			///*blast_->setIsBlast(true);*/
//			// 爆発アニメーションの座標を更新
//			blast_->AddBlast(player->GetPos());
//			//残機を減らす
//			player->Damage(1);
//			system_->SetWins(1);
//			SE::GetInstance().Play(SOUND_TYPE::SHOT_EXPLOSION);
//			SE::GetInstance().Stop(SOUND_TYPE::PLAYER_MOVE);
//			SE::GetInstance().Stop(SOUND_TYPE::PLAYER_MOVE2);
//			return true;
//
//		}
//		return false;
//	}
//
//	
//}
//
//void Colision::CollisionBullet(void)
//{
//	if (pShot_->GetIsAlive() && pShot2_->GetIsAlive())
//	{
//		if (AsoUtility::IsHitSpheres(pShot_->GetPos(), PlayerShot::PLAYER_SHOT_RADIUS,
//			pShot2_->GetPos(), PlayerShot::PLAYER_SHOT_RADIUS))
//		{
//			blast_->AddBlast(pShot_->GetPos());
//			pShot_->SetAlive(false);
//			pShot2_->SetAlive(false);
//		}
//	}
//}
//
//void Colision::CollisionEnemyBullet(void)
//{
//	for (auto* enemy : enemy_->GetEnemy())
//	{
//		if (enemy->isSAlive() && pShot_->GetIsAlive())
//		{
//			if(AsoUtility::IsHitSpheres(pShot_->GetPos(), PlayerShot::PLAYER_SHOT_RADIUS,
//				enemy->GetEShotPos(), PlayerShot::PLAYER_SHOT_RADIUS))
//			{
//				blast_->AddBlast(pShot_->GetPos());
//				pShot_->SetAlive(false);
//				enemy->setIsSAlive(false);
//			}
//		}
//	}
//}



