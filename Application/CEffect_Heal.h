#pragma once

class CEffect_Heal
{
public:
	CEffect_Heal();
	~CEffect_Heal();

	void Init();
	void UpDate(Math::Vector2 scrollPos);
	void Draw();

	bool GetbAlive() { return m_bAlive; }
	Math::Vector2 GetPos() { return m_pos; }

	void SetTexture(KdTexture* apTexture);
	void EmitHeal(Math::Vector2 pos, Math::Vector2 move);

private:
	KdTexture* m_pTexture;			// 画像(テクスチャ)
	Math::Vector2	 m_pos;			// 座標
	Math::Vector2	 m_moveVal;		// 移動量
	Math::Matrix	 m_mat;			// 行列
	bool			 m_bAlive;		// 生存フラグ
	float			 m_size;		// サイズ
	Math::Color		 m_color;		// 色
	int				 m_lifeSpan;	// 有効期間(活動限界)
};
