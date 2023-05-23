#include"CDarken.h"

CDarken::CDarken()
	:m_pos(0, 0)
	, m_move(0, 0)
	, m_size(1)
	, m_color(1, 1, 1, 1)
	, m_lifeSpan(0)
	, m_mat()
	, m_pTexture(nullptr)
{
}

CDarken::~CDarken()
{
}

// 初期化
void CDarken::Init()
{
	m_pos = { 0,0 };
	m_move = { 0,0 };
	m_size = 1;
	m_color = { 1,1,1,1 };
	m_lifeSpan = 0;
}

// 更新
void CDarken::Update()
{
	//有効期間
	m_lifeSpan--;
	if (m_lifeSpan < 0)
	{
		m_lifeSpan = 0;
	}

	//座標更新
	m_pos += m_move;

	//サイズ変更
	m_size *= 0.95;	

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
void CDarken::Draw()
{
	if (m_lifeSpan <= 0) return;

	//行列セット
	SHADER.m_spriteShader.SetMatrix(m_mat); //作った行列をセットする 

	// 色をを細かく指定	
	Math::Rectangle scrRect = { 0,0,32 * 2,32 * 2 }; // テクスチャ座標
	//                            テクスチャ、X、Y、幅、高さ、テクスチャ座標、色、基準点座標
	SHADER.m_spriteShader.DrawTex(m_pTexture, 0, 0, 32, 32,
		&scrRect, &m_color, Math::Vector2(0.5f, 0.5f));
}

// テクスチャ設定
void CDarken::SetTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)	return;
	m_pTexture = apTexture;
}

void CDarken::EmitDark()
{
	m_pos = {0, 0};
	m_move = { 0,0 };
	m_size = 200;
	m_color = { 1.0,1.0,1.0,1.0 };
	m_lifeSpan = 100;
}
