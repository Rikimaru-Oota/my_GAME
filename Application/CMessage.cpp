#include"CMessage.h"

CMessage::CMessage()
	:m_pTexture(nullptr)
	, m_mat()
	, m_pos(0, 0)
	, m_bAlive(false)
	, m_msg(0)
	, m_scrollPos(0,0)
{
}

CMessage::~CMessage()
{
}

void CMessage::Init()
{
	m_pos = { 0,0 };
	m_bAlive = false;
	m_scrollPos = { 0,0 };
}

void CMessage::Update()
{
	if (!m_bAlive) return;
	m_mat = DirectX::XMMatrixTranslation(m_pos.x - m_scrollPos.x, m_pos.y - m_scrollPos.y, 0);
}

void CMessage::Draw()
{
	if (!m_bAlive) return;
	SHADER.m_spriteShader.SetMatrix(m_mat);
	Math::Rectangle scrRect = { 0,0 ,503,199 }; // テクスチャ座標
	Math::Color color = { 1,1,1,1 }; // 色（RGBAの順番で　0.0～1.0）
	SHADER.m_spriteShader.DrawTex(m_pTexture, 0,0, 503, 199, &scrRect, &color, Math::Vector2(0.5f, 0.5f));

}

void CMessage::SetTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;
	m_pTexture = apTexture;
}

void CMessage::SetAlive()
{
	m_bAlive = false;
}

void CMessage::SetMessage(Math::Vector2 pos, int number)
{
	m_pos = pos;
	m_msg = number;
	m_bAlive = true;
}

void CMessage::SetScrollPos(Math::Vector2 scrPos)
{
	m_scrollPos = scrPos;
}
