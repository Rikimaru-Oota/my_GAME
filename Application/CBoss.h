#pragma once
#include"CEnemySword.h"

class Scene;

enum eattackType
{
	Homing,
	Slash,
	Shot,
	Rush
};

enum BossDirection	//向いている方向
{
	BUp,
	BDown,
	BLeft,
	BRight
};


class CBoss
{
public:
	CBoss();			// コンストラクタ
	~CBoss();			// デストラクタ

	// boss
	void Init();		// 初期化
	void Update();		// 更新
	void Draw();		// 描画

	// セット
	void SetBoss(Math::Vector2 pos);
	void SetTexture(KdTexture* apTexture);	// テクスチャ受け取り
	void SetPosX(float posX);	// X座標セット
	void SetPosY(float posY);	// Y座標セット
	void SetMoveX(float moveX);	// X移動量セット
	void SetMoveY(float moveY);	// Y移動量セット
	void SetAlive();			// 生存フラグ設定
	void SetDamage(int dmg);	// ダメージ処理
	void bSetSlashHit(bool aHit);	// 斬撃ヒットフラグセット
	void bSetBlastHit(bool aHit);	// 爆風ヒットフラグセット
	void SetShotFlg(bool flg);	// 発射フラグ設定
	void SetAtkFlg();	// 
	void bSetButtleStart();		// 戦闘開始フラグセット

	void SetSlash(bool slash);
	void SetScrollPos(Math::Vector2 scrPos);	//スクロール量取得
	void SetPlayerPos(Math::Vector2 pos);		// プレイヤーの座標取得

	void SetOwner(Scene* apOwner);

	// ゲッター
	Math::Vector2 GetPos() { return { m_pos.x - 40 , m_pos.y }; }
	Math::Vector2 GetMove() { return m_moveVal; }
	float GetPosX() { return m_pos.x; }
	float GetPosY() { return m_pos.y; }
	float	GetDeg() { return m_deg; }
	bool	GetSlash() { return m_bSlash; }
	bool	bGetShot() { return m_shotFlg; }
	const bool IsAlive() { return m_bAlive; }
	int		GetHp() { return m_hp; }
	const bool bGetSlashHit() { return m_bSlashHit; }	// 斬撃ヒットフラグ取得
	const bool bGetBlastHit() { return m_bBlastHit; }	// 爆風ヒットフラグ取得
	const int iGetAttakeType() { return attackType; }	// 攻撃方法取得
	const int GetShotCnt() { return m_shotCnt; }	// 発射カウント取得
	bool Getm_bRush() { return m_bRush; }			// 突進フラグ
	bool GetPlayerHit() { return playerHitFlg; }	// プレイヤーに当たったか
	const int GetDirection() { return m_direction; }// 方向
	int	GetAtkCnt() { return m_atkCnt; }
	int	GetAttakeType() { return attackType; }
	int bGetBattleStart() { return m_battleStartFlg; }
	bool bGetAtk() { return m_bAtk; }

private:

	eattackType attackType;		// 攻撃行動
	BossDirection	m_direction;	// ボスの向き
	KdTexture* m_pTexture;		// 画像(テクスチャ)
	Math::Vector2	m_pos;		// 座標
	Math::Vector2	m_moveVal;	// 移動量
	Math::Matrix	m_transMat;	// 移動行列
	Math::Matrix	m_scaleMat;	// 拡大行列
	Math::Matrix	m_mat;		// 合成行列
	Math::Vector2	m_size;		//拡大サイズ
	bool			m_bAlive;	// 生存フラグ
	int				m_hp;		// 体力量
	int				m_dmg;		// 体力減少量
	float			m_deg;		// 角度
	bool			m_bSlashHit;		// 斬撃ヒットフラグ
	bool			m_bBlastHit;		// 爆風ヒットフラグ
	bool			m_bSlash;		// 斬撃フラグ
	int				m_slashCnt;		//カウント
	bool			m_shotFlg;	// 発射フラグ
	int				m_shotCnt;	// 発射カウント



		//======突進(Rush)用変数======
	int				m_moveCnt;			// ランダム行動カウント
	const int		MOVE_CNT_MAX = 40;	// ランダム行動時間
	int				m_rushCnt;			// 突進攻撃カウント
	const int		RUSH_CNT_MAX = 100;	// 突進カウント
	bool			m_bRush;			// 突進フラグ
	bool			m_bAtk;				// 攻撃フラグ
	int				m_atkCnt;			// 攻撃カウント
	int				m_atkRnd;			// ランダムで攻撃変更

	bool			playerHitFlg;		// プレイヤーと触れたか

	bool			m_battleStartFlg;			// 戦闘開始フラグ

	int	 m_aCnt;				//アニメーションカウント
	int	 m_aAttackCnt;			//攻撃アニメーションのカウント
	int				m_aTimer;	//アニメーションを何fに1枚動かす
	int				m_aflame;	//アニメーション枚数

	Math::Vector2	 m_scrollPos;	//スクロール量取得用
	Math::Vector2	 m_playerPos;	//プレイヤーの座標取得用

	Math::Rectangle scrRect; //テクスチャ座標


	int m_bossSizeDirection;	//　反転処理用のDirectionを求める変数

	void Attake();	
	void BossMoveHoming(float sp);	// ボスの行動１：追跡
	void BossMoveSlash();	// ボスの行動２：斬撃
	void BossMoveShot();	// ボスの行動３：発射
	void BossMoveRush();	// ボスの行動４：突進

	void atkTypeRnd();
	void atkSleep(int cnt);

	void Animation();
	int AnimationCalc(int cnt, const int xtex);

	CEnemySword	m_enemySwordList;

	Scene* m_pOwner;	// オーナー取得用
};
