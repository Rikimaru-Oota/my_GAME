#include "CEnemySword.h"
#include"Utility.h"

CEnemySword::CEnemySword()
	:m_pTexture(nullptr)
	, m_pos(0, 0)
	, m_move(0, 0)
	, m_mat()
	, m_transMat()
	, m_scaleMat()
	, m_rotMat()
	, m_size(1.0f, 1.0f)
	, m_bSlash(false)
	, m_slashCnt(0)
	, m_slashAnime(0)
	, m_deg(0.0f)
	, m_scrollPos(0.0f,0.0f)
{
}

CEnemySword::~CEnemySword()
{
}

//初期化
void CEnemySword::Init()
{
	m_pos = { 0,0 };		//座標
	m_move = { 0,0 };		//移動量
	m_bSlash = false;		//攻撃フラグ
	m_deg = 0;				//発生方向
	m_scrollPos = { 0,0 };	//スクロール量取得用
	m_slashAnime = 6;		//斬撃アニメーション
}

//更新処理
void CEnemySword::Updata()
{
	if (!m_bSlash)return;	// フラグがたっていなければreturn

	//発生時間
	const int CNT_MAX = m_slashAnime * 2;
	if (m_slashCnt >= CNT_MAX)
	{
		m_bSlash = false;
		m_slashCnt = 0;
		m_move = { 64,64 };
	}
	m_slashCnt++;

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
void CEnemySword::Draw()
{
	if (!m_bSlash) return;
	SHADER.m_spriteShader.SetMatrix(m_mat);
	Math::Rectangle scrRect = { (m_slashCnt / m_slashAnime) * 64, 0, 64, 64 }; // テクスチャ座標
	Math::Color color = { 1,1,1,1 }; // 色（RGBAの順番で　0.0～1.0）
	SHADER.m_spriteShader.DrawTex(m_pTexture, 0, 0, 64, 64, &scrRect, &color, Math::Vector2(0.5f, 0.5f));
}
//テクスチャ設定
void CEnemySword::SetTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;

	m_pTexture = apTexture;
}
//座標取得
const Math::Vector2 CEnemySword::GetPos()
{
	return m_pos;
}
//移動量取得
const Math::Vector2 CEnemySword::GetMove()
{
	return m_move;
}

//攻撃処理(発生キャラ座標、角度、サイズ、発生距離）
void CEnemySword::Slash(Math::Vector2 Pos, float deg, Math::Vector2 size, float dist)
{
	m_bSlash = true;
	m_pos = Pos;
	m_deg = deg;
	m_size = size;
	m_move.x = cos(DirectX::XMConvertToRadians(m_deg)) * dist;	// cos
	m_move.y = sin(DirectX::XMConvertToRadians(m_deg)) * dist;	// sin
	m_pos += m_move;	// 移動量をセット

	// 画像反転処理
	if (Pos.x > m_pos.x) m_size.y *=-1;
}

//フラグ状態取得
const bool CEnemySword::bGetSlash()
{
	return m_bSlash;
}
//スクロール量取得
void CEnemySword::SetScrollPos(Math::Vector2 scrPos)
{
	m_scrollPos = scrPos;
}
