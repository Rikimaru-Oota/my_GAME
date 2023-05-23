#pragma once

class CMessage
{
public:
	CMessage();
	~CMessage();

	void Init();
	void Update();
	void Draw();
	
	bool GetAlive() { return m_bAlive; }
	Math::Vector2 GetPos(){ return m_pos; }
	int GetMsgNum() { return m_msg; }

	void SetTexture(KdTexture* apTexture);
	void SetAlive();
	void SetMessage(Math::Vector2 pos, int number);
	void SetScrollPos(Math::Vector2 scrPos);

private:
	KdTexture* m_pTexture;		//画像
	Math::Matrix m_mat;			//行列
	Math::Vector2 m_pos;		//座標
	bool m_bAlive;				//生成フラグ
	int m_msg;					//メッセージの種類判別
	Math::Vector2	 m_scrollPos;	//スクロール量取得用
};

