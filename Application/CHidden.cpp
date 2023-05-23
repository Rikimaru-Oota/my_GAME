#include"CHidden.h"
#include"Utility.h"

CHidden::CHidden()
	:m_mat()
	,m_bHidden(false)
	, m_hiddenCnt(0)
{
}

CHidden::~CHidden()
{
}

// 初期化
void CHidden::Init()
{
	m_bHidden = false;
	m_hiddenCnt = 0;
}

// 更新
void CHidden::Updata()
{
	if (m_bHidden)
	{
		m_hiddenCnt++;
		// 隠れ身解除
		if (m_hiddenCnt > HIDDEN_CNT_MAX)
		{
			m_bHidden = false;
		}
	}
	else
	{
		m_hiddenCnt--;
		if (m_hiddenCnt <= 0)
		{
			m_hiddenCnt = 0;
		}
	}
}

// フラグセット
void CHidden::bSetHidden()
{
	m_bHidden = false;
}

// 隠れ蓑使用
void CHidden::Hidden()
{
	if(!m_bHidden) m_bHidden = true;
	else m_bHidden = false;
}
