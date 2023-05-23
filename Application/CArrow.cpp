#include"CArrow.h"
#include"Utility.h"

CArrow::CArrow()
	:m_pTexture(nullptr)
	, m_pos(0, 0)
	, m_moveVal(0, 0)
	, m_mat()
	, m_bAlive(false)
	, m_deg()
	, m_scrollPos(0,0)
{
}

CArrow::~CArrow()
{
}

// 初期化
void CArrow::Init()
{
	m_pos = { 0,0 };
	m_moveVal = { 0,0 };
	m_bAlive = false;
	m_deg = 0;
}

// 更新
void CArrow::Update()
{
	if (!m_bAlive) return;

	//座標確定
	m_pos += m_moveVal;

	//行列作成
	Math::Matrix scaleMat, RotMat,transMat;
	//拡縮行列
	scaleMat = DirectX::XMMatrixScaling(1, 1, 1);
	//回転行列
	RotMat = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(m_deg));
	//移動行列
	transMat = DirectX::XMMatrixTranslation(m_pos.x - m_scrollPos.x, m_pos.y - m_scrollPos.y, 0.0f);
	//行列合成
	m_mat = scaleMat * RotMat * transMat;
}

// 描画
void CArrow::Draw()
{
	if (!m_bAlive) return;

	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_pTexture, Math::Rectangle(32, 0, 32, 32), 1.0f);
}

// テクスチャ設定：
void CArrow::SetTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;

	m_pTexture = apTexture;
}

// フラグ変更
void CArrow::SetAlive()
{
	m_bAlive = false;
}

void CArrow::SetScrollPos(Math::Vector2 scrPos)
{
	m_scrollPos = scrPos;
}

// 発射処理関数
void CArrow::Shot(const Math::Vector2 aScrPos, const Math::Vector2 aDestPos)
{
	if (m_bAlive) return;

	m_pos = aScrPos;	// 発射座標

	m_deg = Utility::GetAngleDeg(aScrPos, aDestPos);
	m_moveVal.x = cos(DirectX::XMConvertToRadians(m_deg)) * SPEED::ARROW;
	m_moveVal.y = sin(DirectX::XMConvertToRadians(m_deg)) * SPEED::ARROW;

	m_bAlive = true;
}

void CArrow::BossShot(const Math::Vector2 aScrPos, const Math::Vector2 aDestPos, int i)
{
	if (m_bAlive) return;
	m_pos = aScrPos;	// 発射座標
	m_deg = Utility::GetAngleDeg(aScrPos, aDestPos);
	m_moveVal.x = cos(DirectX::XMConvertToRadians(m_deg + i * 20 - 20)) * SPEED::ARROW;
	m_moveVal.y = sin(DirectX::XMConvertToRadians(m_deg + i * 20 - 20)) * SPEED::ARROW;
	m_bAlive = true;
}