#pragma once
//敵クラス：弓兵

class CArcher
{
public:
	CArcher();
	~CArcher();

	void Init();			// 初期化
	void Update();			// 更新
	void Draw();			// 描画
	
	const bool IsAlive() { return m_bAlive; }	// 生存確認
	Math::Vector2 GetPos() { return m_pos; }	// 座標取得
	Math::Vector2 GetMove() { return m_moveVal; }	// 移動量取得
	const bool GetbVisibility() { return m_VisibilityFlg; }		// 視野フラグ取得
	const int GetShotCnt() { return m_shotCnt; }	// 発射カウント取得
	const bool bGetSlashHit() { return m_bSlashHit; }	// 斬撃ヒットフラグ取得
	const bool bGetBlastHit() { return m_bBlastHit; }	// 爆風ヒットフラグ取得

	void SetArchaer(Math::Vector2 pos);		// 弓兵設置
	void SetTexture(KdTexture* apTexture);	// テクスチャ受け取り
	void SetPosX(float posX);	// X座標セット
	void SetPosY(float posY);	// Y座標セット
	void SetMoveX(float moveX);	// X移動量セット
	void SetMoveY(float moveY);	// Y移動量セット
	void SetAlive();	// 生存フラグ設定
	void SetDamage(int dmg);	// ダメージ加算
	void SetShotFlg(bool flg);	// 発射フラグ設定
	void bSetSlashHit(bool aHit);	// 斬撃ヒットフラグセット
	void bSetBlastHit(bool aHit);	// 爆風ヒットフラグセット

	void SetScrollPos(Math::Vector2 scrPos);	//スクロール量取得
	void SetPlayerPos(Math::Vector2 pos);		// プレイヤーの座標取得
	void bSetHidden(bool flg);					// 隠れ身状態取得

private:

	KdTexture* m_pTexture;		// 画像(テクスチャ)
	Math::Vector2	m_pos;		// 座標
	Math::Vector2	m_moveVal;	// 移動量
	Math::Matrix	m_mat;		// 合成行列
	Math::Matrix	m_transMat;	// 移動行列
	Math::Matrix	m_scaleMat;	// 拡大行列
	bool			m_bAlive;	// 生存フラグ
	int				m_hp;		// 体力量
	int				m_dmg;		// 体力減少量
	float			m_deg;		// 角度
	float			m_dist;		// 距離
	bool			m_VisibilityFlg;	// 視野フラグ
	bool			m_bSlashHit;		// 斬撃ヒットフラグ
	bool			m_bBlastHit;		// 爆風ヒットフラグ
	
	int				m_moveCnt;			// ランダム行動カウント
	const int		MOVE_CNT_MAX = 40;	// ランダム行動時間
	bool			m_shotFlg;	// 発射フラグ
	int				m_shotCnt;	// 発射カウント


	Math::Vector2	 m_scrollPos;	//スクロール量取得用
	Math::Vector2	 m_playerPos;	//プレイヤーの座標取得用
	bool			 m_bHidden;		//隠れ身フラグ取得用

	void Attack();		// 攻撃関数
	void Walk();		// 見回り関数
};

