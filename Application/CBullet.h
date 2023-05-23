#pragma once

class Scene;

class CBullet
{
public:
	CBullet();
	~CBullet();

	void Init();
	void Updata();
	void Draw();
	
	const Math::Vector2 CBullet::GetPos();		//À•Wæ“¾
	const Math::Vector2 CBullet::GetMove();		//ˆÚ“®—Êæ“¾
	const bool IsAlive();

	void SetTexture(KdTexture* apTexture);
	void SetAlive();			//ƒtƒ‰ƒOó‘Ôİ’è
	
	void Shot(const Math::Vector2 aShotPos,float deg);
	
	void SetScrollPos(Math::Vector2 scrPos);

private:
	KdTexture*		m_pTexture;		//‰æ‘œ
	Math::Vector2	m_pos;
	Math::Vector2	m_moveVal;
	Math::Matrix	m_mat;
	bool			m_bAlive;
	float			m_deg;
	Math::Vector2	m_scrollPos;

};