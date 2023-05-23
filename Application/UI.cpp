#include "UI.h"
#include "Scene.h"
#include"Utility.h"

CUI::CUI()
	:m_pbackTexture(nullptr)
	,m_prframeTexture(nullptr)
	,m_plframeTexture(nullptr)
	,m_pHPTexture(nullptr)
	,m_pHPbarTexture(nullptr)
	,m_pHideTexture(nullptr)
	,m_pHidebarTexture(nullptr)
	,m_prweaponTexture(nullptr)
	,m_plweaponTexture(nullptr)
	,m_pIconKatanaTexture(nullptr)
	,m_pIconShurikenTexture(nullptr)
	,m_pIconBombTexture(nullptr)
	,m_pIconMinoTexture(nullptr)
	,m_pStackBombTexture(nullptr)
	,m_pStackKeyTexture(nullptr)
	,m_backmat()
	, m_rframemat()
	, m_lframemat()
	, m_hpmat()
	,m_hpbarmat()
	,m_hidemat()
	,m_hidebarmat()
	,m_stackbombIconmat()
	,m_stackkeyIconmat()
	,hidebarcolor(0,1,0,1)
	,m_hp(0)
	,rightweapontype()
	,leftweapontype()
	,m_bombstacks()
	,m_keystacks()
	,m_hidecount()
	,m_pOwner(nullptr)
{
}

CUI::~CUI()
{
}

void CUI::Init()
{
}

void CUI::Updata()
{
	//プレイヤークラス取得
	CPlayer* player=m_pOwner->GetPlayer(); //プレイヤークラスの取得
	rightweapontype = player->GetR();
	leftweapontype = player->GetL();
	m_hp = player->GetHp();
	m_bombstacks = player->GetBombPossession();
	m_keystacks = player->GetKeyPossession();
	m_hidecount = player->GetHideCnt();

	switch (rightweapontype)
	{
	case eShuriken:
		m_prweaponTexture = m_pIconShurikenTexture;
		break;
	case eSword:
		m_prweaponTexture = m_pIconKatanaTexture;
		break;
	case eBomb:
		m_prweaponTexture = m_pIconBombTexture;
		break;
	case eHidden:
			m_prweaponTexture = m_pIconMinoTexture;
			break;
	default:
		break;
	}

	switch (leftweapontype)
	{
	case eShuriken:
		m_plweaponTexture = m_pIconShurikenTexture;
		break;
	case eSword:
		m_plweaponTexture = m_pIconKatanaTexture;
		break;
	case eBomb:
		m_plweaponTexture = m_pIconBombTexture;
		break;
	case eHidden:
		m_plweaponTexture = m_pIconMinoTexture;
	default:
		break;
	}

	m_backmat = DirectX::XMMatrixTranslation(0, -280, 0);
	m_rframemat = DirectX::XMMatrixTranslation(100, -283, 0);
	m_lframemat = DirectX::XMMatrixTranslation(-40, -283, 0);
}

void CUI::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_backmat);
	SHADER.m_spriteShader.DrawTex(m_pbackTexture, Math::Rectangle(0, 0, 600, 140), 1.0f);

	SHADER.m_spriteShader.SetMatrix(m_rframemat);
	SHADER.m_spriteShader.DrawTex(m_prweaponTexture, Math::Rectangle(0, 0, 100, 100), 1.0f);

	SHADER.m_spriteShader.SetMatrix(m_lframemat);
	SHADER.m_spriteShader.DrawTex(m_plweaponTexture, Math::Rectangle(0, 0, 100, 100), 1.0f);

	SHADER.m_spriteShader.SetMatrix(m_rframemat);
	SHADER.m_spriteShader.DrawTex(m_prframeTexture, Math::Rectangle(0, 0, 100, 100), 1.0f);

	SHADER.m_spriteShader.SetMatrix(m_lframemat);
	SHADER.m_spriteShader.DrawTex(m_plframeTexture, Math::Rectangle(0, 0, 100, 100), 1.0f);
	
	for (int i = 0; i < m_bombstacks; i++)
	{
		SHADER.m_spriteShader.SetMatrix(m_stackbombIconmat);
		Math::Rectangle scrRect = { 0,0,64,64 }; // テクスチャ座標
		Math::Color color = { 1,1,1,1 }; // 色（RGBAの順番で　0.0～1.0）
		SHADER.m_spriteShader.DrawTex(m_pStackBombTexture, 250-i*15, -255, 64, 64, &scrRect, &color, Math::Vector2(0.5f, 0.5f));
	}

	for (int i = 0; i < m_keystacks; i++)
	{
		SHADER.m_spriteShader.SetMatrix(m_stackkeyIconmat);
		Math::Rectangle scrRect = { 0,0,32,32 }; // テクスチャ座標
		Math::Color color = { 1,1,1,1 }; // 色（RGBAの順番で　0.0～1.0）
		SHADER.m_spriteShader.DrawTex(m_pStackKeyTexture, 250 - i * 30, -310, 32, 32, &scrRect, &color, Math::Vector2(0.5f, 0.5f));
	}

	if(rightweapontype==eHidden||leftweapontype==eHidden)
	{
		if (rightweapontype == eHidden)
		{
			if (!(m_hidecount == 0))
			{
				SHADER.m_spriteShader.SetMatrix(m_hidebarmat);
				Math::Rectangle barscrRect = { 0,0,110,28 }; // テクスチャ座標
				Math::Color barcolor = { 1,1,1,1 }; // 色（RGBAの順番で　0.0～1.0）
				SHADER.m_spriteShader.DrawTex(m_pHidebarTexture, 100, -290, 78, 20, &barscrRect, &barcolor, Math::Vector2(0.5f, 0.5f));

				SHADER.m_spriteShader.SetMatrix(m_hidemat);
				Math::Rectangle scrRect = { 0,0,18,18 }; // テクスチャ座標
				if (m_hidecount <= 200)
					hidebarcolor = { 0,1,0,1 }; // 色（RGBAの順番で　0.0～1.0）
				if (m_hidecount >= 180)
					hidebarcolor = { 1,1,0,1 }; // 色（RGBAの順番で　0.0～1.0）
				if (m_hidecount >= 230)
					hidebarcolor = { 1,0,0,1 }; // 色（RGBAの順番で　0.0～1.0）
				float hideMax = 300;
				SHADER.m_spriteShader.DrawTex(m_pHideTexture, 100 - ((70 * ((hideMax - (hideMax - m_hidecount)) / hideMax)) / 2), -290, 70 - (70 * ((hideMax - (hideMax - m_hidecount)) / hideMax)), 12, &scrRect, &hidebarcolor, Math::Vector2(0.5f, 0.5f));//300は隠れ蓑のチャージMAX時
			}
		}
		if (leftweapontype == eHidden)
		{
			if (!(m_hidecount==0))
			{
				SHADER.m_spriteShader.SetMatrix(m_hidebarmat);
				Math::Rectangle barscrRect = { 0,0,110,28 }; // テクスチャ座標
				Math::Color barcolor = { 1,1,1,1 }; // 色（RGBAの順番で　0.0～1.0）
				SHADER.m_spriteShader.DrawTex(m_pHidebarTexture, -40, -290, 78, 20, &barscrRect, &barcolor, Math::Vector2(0.5f, 0.5f));

				SHADER.m_spriteShader.SetMatrix(m_hidemat);
				Math::Rectangle scrRect = { 0,0,18,18 }; // テクスチャ座標
				if (m_hidecount <= 200)
					hidebarcolor = { 0,1,0,1 }; // 色（RGBAの順番で　0.0～1.0）
				if (m_hidecount >= 180)
					hidebarcolor = { 1,1,0,1 }; // 色（RGBAの順番で　0.0～1.0）
				if (m_hidecount >= 230)
					hidebarcolor = { 1,0,0,1 }; // 色（RGBAの順番で　0.0～1.0）
				float hideMax = 300;
				SHADER.m_spriteShader.DrawTex(m_pHideTexture, -40 - ((70 * ((hideMax - (hideMax - m_hidecount)) / hideMax)) / 2), -290, 70 - (70 * ((hideMax - (hideMax - m_hidecount)) / hideMax)), 12, &scrRect, &hidebarcolor, Math::Vector2(0.5f, 0.5f));//300は隠れ蓑のチャージMAX時
			}
		}
	}

	m_hpbarmat = DirectX::XMMatrixTranslation(-200, -250, 0);//ここは座標
	SHADER.m_spriteShader.SetMatrix(m_hpbarmat);
	SHADER.m_spriteShader.DrawTex(m_pHPbarTexture, Math::Rectangle(0, 0, 110, 28), 1.0f);

	m_hpmat = DirectX::XMMatrixTranslation(-225-((HP::PLAYER-m_hp*2)/2), -250, 0);//ここは座標
	SHADER.m_spriteShader.SetMatrix(m_hpmat);
	SHADER.m_spriteShader.DrawTex(m_pHPTexture, Math::Rectangle(0, 0, m_hp*2, 18), 1.0f);

	


}

void CUI::SetOwner(Scene* apOwner)
{
	if (apOwner == nullptr) return;

	m_pOwner = apOwner;
}

void CUI::SetbackTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;

	m_pbackTexture = apTexture;
}

void CUI::SetrframeTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;

	m_prframeTexture = apTexture;
}

void CUI::SetlframeTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;

	m_plframeTexture = apTexture;
}

void CUI::SetHPTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;

	m_pHPTexture = apTexture;
}

void CUI::SetHPBarTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;

	m_pHPbarTexture = apTexture;
}

void CUI::SetHideTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;

	m_pHideTexture = apTexture;
}

void CUI::SetHideBarTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;

	m_pHidebarTexture = apTexture;
}

void CUI::SetIconKatanaTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;

	m_pIconKatanaTexture = apTexture;
}

void CUI::SetIconShurikenTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;

	m_pIconShurikenTexture = apTexture;
}

void CUI::SetIconBombTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;

	m_pIconBombTexture = apTexture;
}

void CUI::SetIconMinoTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;

	m_pIconMinoTexture = apTexture;
}

void CUI::SetStackBombTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;

	m_pStackBombTexture = apTexture;
}

void CUI::SetStackKeyTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;

	m_pStackKeyTexture = apTexture;
}
