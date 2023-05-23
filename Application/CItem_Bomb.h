#pragma once

class CItem_Bomb
{
public:
	CItem_Bomb();
	~CItem_Bomb();

	void Init();
	void Update();
	void Draw();
	void SetTexture_t(KdTexture* apTexture);
	void SetTexture_f(KdTexture* apTexture);
	void SetBomb(Math::Vector2 Pos);		//座標セット、フラグたて
	void SetAlive();				//生成フラグ変更
	void bSetbombHit();				//爆弾アイテムヒットフラグセット
	void SetScrollPos(Math::Vector2 scrPos);

	bool GetAlive() { return m_bAlive; }
	Math::Vector2 GetPos() { return m_pos; }

private:
	KdTexture* m_pTexture_t;			//画像(true)
	KdTexture* m_pTexture_f;			//画像(false)
	Math::Matrix m_mat;			//行列
	Math::Vector2 m_pos;		//座標
	bool m_bAlive;				//生成フラグ
	bool m_bBombHit;			//爆弾アイテムヒットフラグ

	Math::Vector2	 m_scrollPos;	//スクロール量取得用

};

