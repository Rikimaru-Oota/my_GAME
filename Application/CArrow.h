#pragma once

class CArrow
{
public:
	CArrow();
	~CArrow();

	void Init();			// 初期化
	void Update();			// 更新
	void Draw();			// 描画

	const bool IsAlive() { return m_bAlive; }	// 生存確認
	Math::Vector2 GetPos() { return m_pos; }	// 座標取得
	Math::Vector2 GetMove() { return m_moveVal; }	// 移動量取得

	void SetTexture(KdTexture* apTexture);
	void SetAlive();			//フラグ状態設定
	void SetScrollPos(Math::Vector2 scrPos);	//スクロール量取得

	void Shot(const Math::Vector2 aScrPos,const Math::Vector2 aDestPos);
	void BossShot(const Math::Vector2 aScrPos,const Math::Vector2 aDestPos, int i);

private:
	KdTexture*		m_pTexture;		//画像
	Math::Vector2	m_pos;			//座標
	Math::Vector2	m_moveVal;		//移動量
	Math::Matrix	m_mat;			//合成行列
	bool			m_bAlive;		//生存フラグ
	float			m_deg;			//角度

	Math::Vector2	m_scrollPos;
};

