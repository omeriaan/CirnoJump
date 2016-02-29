/* ==========================================================
	・FPSControl.h
			フレーム管理クラス
============================================================= */

#ifndef __FPSCONTROL_H__
#define __FPSCONTROL_H__

#include <windows.h>

/* ---------------------------------------------------
	フレーム管理クラス : CFpsControlクラス
--------------------------------------------------- */
class CFpsControl {
private:
	DWORD	m_lastTime;				// 前の測定時間
	int		m_frameCount;			// フレームカウンター
	double	m_frameTime;			// １フレームにかける時間
	int		m_FPS;					// １秒間あたりのフレーム処理回数(実回数)
	int		m_SkipCount;			// スキップカウンター
	int		m_SkipRate;				// １秒間あたりのフレームスキップが起きた回数
	bool	m_isFrameSkip;			// フレームスキップフラグ(true:有 false:無)
	bool	m_isDraw;				// 描画フラグ

public:
	CFpsControl();					// コンストラクタ
	~CFpsControl();					// デストラクタ
	void	InitFPS();				// 初期化処理
	void	ControlFPS();			// フレーム制御処理
	bool	GetDrawFrag();			// 描画フラグgetter
	int		GetFPS();				// FPSgetter
	int		GetSkipRate();			// スキップレートgetter
};


#endif