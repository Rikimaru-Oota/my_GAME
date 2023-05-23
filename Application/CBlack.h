#pragma once

class CBlack
{
public:
	CBlack();
	~CBlack();

	void Init();	//初期化
	void Update();	//更新
	void Draw();	//描画
	void SetTexture(KdTexture* apTexture);	//テクスチャ設定

	//パーティクル発生関数
	void EmitBlack();

private:
	Math::Vector2	m_pos;		//座標
	Math::Vector2	m_move;		//移動量
	float			m_size;		//サイズ
	Math::Color		m_color;	//色
	int				m_lifeSpan;	//有効期間(活動限界)
	Math::Matrix	m_mat;		//行列
	float			m_transcnt; //透過カウント
	KdTexture* m_pTexture;	//テクスチャ(アドレス)
};

