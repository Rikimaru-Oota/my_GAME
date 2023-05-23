#include "CSword.h"

CSword::CSword()
	:m_pTexture(nullptr)
	,m_pos(0,0)
	,m_move(0,0)
	,m_mat()
	,m_transMat()
	,m_scaleMat()
	,m_rotMat()
	,m_size(1.0f,1.0f)
	,m_bSlash(false)
	,m_slashCnt(0)
	,m_slashAnime(0)
	,m_deg(0)
	,m_scrollPos(0,0)
{
}

CSword::~CSword()
{
}

//初期化
void CSword::Init()
{
	m_pos = { 0,0 };		//座標
	m_move = { 64,64 };		//移動量
	m_bSlash = false;		//攻撃フラグ
	m_slashCnt = 0;			//攻撃発生時間
	m_scrollPos = { 0,0 };	//スクロール量取得用
	m_slashAnime = 6;
	m_deg = 0;
}

//更新処理
void CSword::Updata(Math::Vector2 playerPos)
{
	if (!m_bSlash)return;

	m_pos = playerPos;

	//発生時間
	const int CNT_MAX = m_slashAnime * 2;
	if (m_slashCnt >= CNT_MAX)
	{
		m_bSlash = false;
		m_slashCnt = 0;
	}
	m_slashCnt++;

	//座標確定
	m_pos += m_move;
	
	// 画像反転処理
	if (playerPos.x > m_pos.x) m_size.y = -1;
	else m_size.y = 1;

	//拡縮行列
	m_scaleMat = DirectX::XMMatrixScaling(m_size.x, m_size.y, 1);
	//回転行列
	m_rotMat = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(m_deg));
	//移動行列
	m_transMat = DirectX::XMMatrixTranslation(m_pos.x - m_scrollPos.x, m_pos.y - m_scrollPos.y, 0.0f);
	//行列合成
	m_mat = m_scaleMat * m_rotMat * m_transMat;
}

//描画処理
void CSword::Draw()
{
	if (!m_bSlash) return;
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_pTexture, Math::Rectangle((m_slashCnt/m_slashAnime)* 64 , 0, 64, 64), 1.0f);
}

//テクスチャ設定
void CSword::SetTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;

	m_pTexture = apTexture;
}

//座標取得
const Math::Vector2 CSword::GetPos()
{
	return m_pos;
}

//移動量取得
const Math::Vector2 CSword::GetMove()
{
	return m_move;
}

//攻撃処理
void CSword::Slash(Math::Vector2 Pos, const float deg)
{
	m_bSlash = true;
	m_pos = Pos;
	m_deg = deg;
	const float dist = 64;	// プレイヤーとの距離
	m_move.x = cos(DirectX::XMConvertToRadians(m_deg)) * dist;
	m_move.y = sin(DirectX::XMConvertToRadians(m_deg)) * dist;
}

//フラグ状態取得
const bool CSword::bGetSlash()
{
	return m_bSlash;
}

// スクロール量取得用
void CSword::SetScrollPos(Math::Vector2 scrPos)
{
	m_scrollPos = scrPos;
}
