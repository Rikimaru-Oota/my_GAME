#pragma once

class CSword
{
public:
	CSword();
	~CSword();

	void Init();
	void Updata(Math::Vector2 playerPos);
	void Draw();
	void SetTexture(KdTexture* apTexture);
	const Math::Vector2 CSword::GetPos();		//座標取得
	const Math::Vector2 CSword::GetMove();		//移動量取得

	//攻撃処理
	void Slash(Math::Vector2 Pos, const float deg);
	const bool bGetSlash();		//フラグ状態取得

	void SetScrollPos(Math::Vector2 scrPos);	//スクロール量取得

private:

	KdTexture*		 m_pTexture;	//画像(テクスチャ)
	Math::Vector2	 m_pos;			//座標
	Math::Vector2	 m_move;		//移動量
	Math::Matrix	 m_mat;			//行列
	Math::Matrix	 m_transMat;	//移動行列
	Math::Matrix	 m_scaleMat;	//拡大行列
	Math::Matrix	 m_rotMat;	//拡大行列
	Math::Vector2	 m_size;		//拡大サイズ
	bool			 m_bSlash;		//攻撃フラグ
	int				 m_slashCnt;	//攻撃発動時間
	int				 m_slashAnime;	//アニメーション
	float			 m_deg;			//角度
	Math::Vector2	 m_scrollPos;	//スクロール量取得用

};
