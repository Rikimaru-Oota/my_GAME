#pragma once

class CItem_Health
{
public:
	CItem_Health();
	~CItem_Health();

	bool GetAlive() { return m_bAlive; }
	Math::Vector2 GetPos() { return m_pos; }

	void Init();
	void Update();
	void Draw();
	void SetTexture(KdTexture* apTexture);
	void SetHealth(Math::Vector2 Pos);	// アイテムセット
	void SetAlive();				//生成フラグ変更
	void SetScrollPos(Math::Vector2 scrPos);

private:

	KdTexture* m_pTexture;			//画像(テクスチャ)
	Math::Matrix m_mat;			//行列
	Math::Vector2 m_pos;		//座標
	bool m_bAlive;				//生成フラグ
	Math::Vector2	 m_scrollPos;	//スクロール量取得用
};

