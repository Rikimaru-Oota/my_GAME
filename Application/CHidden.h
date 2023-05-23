#pragma once

constexpr int HIDDEN_CNT_MAX = 300;		// 隠れ身状態時間

class CHidden
{
public:
	CHidden();
	~CHidden();

	void Init();
	void Updata();

	const bool bGetHidden() { return m_bHidden; }		//フラグ状態取得
	const int GetHiddenCnt() { return m_hiddenCnt; }	//カウント取得
	
	void bSetHidden();		// フラグ状態変更

	void Hidden();	// 隠れ身

private:
	Math::Matrix	 m_mat;			//行列
	bool			 m_bHidden;		//隠れ身状態フラグ
	int				 m_hiddenCnt;	//隠れ身発動時間
};
