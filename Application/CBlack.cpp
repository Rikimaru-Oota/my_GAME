#include "CBlack.h"

CBlack::CBlack()
	:m_pos(0, 0)
	, m_move(0, 0)
	, m_size(1)
	, m_color(1, 1, 1, 1)
	, m_lifeSpan(0)
	, m_mat()
	, m_transcnt(0.0f)
	, m_pTexture(nullptr)
{
}

CBlack::~CBlack()
{
}

// 初期化
void CBlack::Init()
{
	m_pos = { 0,0 };
	m_move = { 0,0 };
	m_size = 1;
	m_color = { 1,1,1,1 };
	m_lifeSpan = 0;
	m_transcnt = 0.0f;
}

// 更新
void CBlack::Update()
{
	//有効期間
	m_lifeSpan--;
	if (m_lifeSpan < 0)
	{
		m_lifeSpan = 0;
	}

	//座標更新
	m_pos += m_move;

	//行列作成
	Math::Matrix scaleMat, transMat;
	//拡縮行列
	scaleMat = DirectX::XMMatrixScaling(m_size, m_size, 1);
	//移動行列
	transMat = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, 0);
	//行列合成
	m_mat = scaleMat * transMat;
}

// 描画
void CBlack::Draw()
{
	if (m_lifeSpan <= 0) return;

	//行列セット
	SHADER.m_spriteShader.SetMatrix(m_mat); //作った行列をセットする 

	// 色をを細かく指定	
	Math::Rectangle scrRect = { 0,0,1280,720 }; // テクスチャ座標
	Math::Color m_color = { 0,0,0,m_transcnt };
	//                            テクスチャ、X、Y、幅、高さ、テクスチャ座標、色、基準点座標
	SHADER.m_spriteShader.DrawTex(m_pTexture, 0, 0, 1280, 720,
		&scrRect, &m_color, Math::Vector2(0.5f, 0.5f));
}

// テクスチャ設定
void CBlack::SetTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)	return;
	m_pTexture = apTexture;
}

void CBlack::EmitBlack()
{
	m_transcnt +=0.02;
	m_pos = {0, 0};
	m_move = { 0,0 };
	m_size = 200;
	m_color = { 1.0,1.0,1.0,m_transcnt};
	m_lifeSpan = 100;
}
