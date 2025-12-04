//#pragma once
//#include "../framework.h"
//#include "../Common/Vector2.h"
//class Player;
//class EnemyManager;
//class BlastManager;
//class PlayerShot;
//class System;
//class WallManager;
//class Stage;
//
//
//class Colision
//{
//public:
//
//	Colision();
//	~Colision();
//	void Init(Player* player, EnemyManager* enemy, BlastManager* blast, PlayerShot* pShot, System* system, WallManager* wallMange, Stage* stage);
//	void InitMulti(Player* player, Player* player2, EnemyManager* enemy, BlastManager* blast, PlayerShot* pShot, PlayerShot* pShot2, System* system, WallManager* wallMange, Stage* stage);
//	void Update(void);
//	void Draw(void);
//	void Release(void);
//	Vector2 World2MapPos();
//	// ステージブロックとプレイヤーの衝突
//	void CollisionWall(Player* player);
//	//ステージブロックとプレイヤー弾の当たり判定
//	void CollisionWallShot(PlayerShot* pShot);
//	//ステージブロックをエネミー弾の当たり判定
//	void CollisionWallEShot(void);
//	//マルチプレイ用対プレイヤー当たり判定
//	bool CollisionPlayer(Player* player, PlayerShot* pShot);
//	//弾同士の当たり判定
//	void CollisionBullet(void);
//	//エネミーとプレイヤー弾の当たり判定
//	void CollisionEnemyBullet(void);
//
//private:
//
//	float cDistance;				//プレイヤーと敵の中心の距離
//	float total;					//プレイヤーと敵の半径の合計
//	int winNum_;
//	VECTOR bulletVel_;
//
//	//プレイヤー
//	Player* player_;
//	Player* player2_;
//	//エネミー
//	EnemyManager* enemy_;
//	//爆発
//	BlastManager* blast_;
//	//プレイヤー弾
//	PlayerShot* pShot_;
//	PlayerShot* pShot2_;
//	//システム
//	System* system_;
//	//壁
//	WallManager* wallMange_;
//	//ステージ
//	Stage* stage_;
//
//	// 地面との衝突用線分
//	VECTOR lineTopPosZUp_;
//	VECTOR lineDownPosZUp_;
//
//	VECTOR lineTopPosZDown_;
//	VECTOR lineDownPosZDown_;
//
//	VECTOR lineTopPosXC_;
//	VECTOR lineDownPosXC_;
//	
//
//};