/* ==========================================================
	・FPSControl.cpp
			フレーム処理
============================================================= */

#include "stdafx.h"

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#include "FPSControl.h"

#include "Memory_Leak.h"	// メモリーリーク検知用

/* ----------------------------------------------
			コンストラクタ
---------------------------------------------- */
CFpsControl::CFpsControl() 
	: m_frameTime(1000.0 / REQUEST_FPS),
	  m_isFrameSkip(IS_FRAMESKIP),
	  m_frameCount( 0 ),
	  m_FPS( 0 ),
	  m_SkipCount( 0 ),
	  m_SkipRate( 0 ),
	  m_isDraw( true )
{
	timeBeginPeriod(1);				// タイマー(timeGetTime)の精度を向上させる
}

/* ----------------------------------------------
			デストラクタ
---------------------------------------------- */
CFpsControl::~CFpsControl() {
	timeEndPeriod(1);			
}


/* ----------------------------------------------
	・InitFPS()
		初期化処理
---------------------------------------------- */
void CFpsControl::InitFPS() {
	m_lastTime = timeGetTime();
}


/* ----------------------------------------------
	・ControlFPS()
		フレーム制御処理
---------------------------------------------- */
void CFpsControl::ControlFPS() {
	m_frameCount++;

	// フレームスキップ処理
	// 現在の時刻が次のフレーム時間をオーバーしてしまった場合
	if( m_isFrameSkip && timeGetTime() > (DWORD)(m_lastTime + (m_frameCount+1) * m_frameTime) ) {
		m_isDraw = false;				// 描画フラグをfalseにする(描画しない)
		m_SkipCount++;
	}
	else {
		// 待機する
		while(timeGetTime() <= (DWORD)(m_lastTime + m_frameCount * m_frameTime)) {
			Sleep(1);
		}
		m_isDraw = true;				// 描画フラグをtrueにする(描画する)
	}

	// 現在時刻が前に測定した時刻(m_lastTime)より１秒以上経過していたら
	if(timeGetTime() - m_lastTime >= 1000) {
		m_lastTime = timeGetTime();		// 測定時刻を更新
		m_FPS = m_frameCount;			// フレームレートを更新(１秒あたりのフレーム処理回数:理想値60fps)
		m_SkipRate = m_SkipCount;		// スキップレートを更新
		m_frameCount = 0;
		m_SkipCount  = 0;

		/* ----- デバッグモードの時、FPSとスキップレートを表示 ------ */
/*
		#ifdef _DEBUG
			tostringstream os;
			os << _T("FPS = ") << m_FPS << _T(", SkipRate = ") << m_SkipRate << _T("\n");
			OutputDebugString( os.str().c_str() );
		#endif
*/
	}
}

/* ----------------------------------------------
	・GetDrawFrag()
		描画フラグgetter
---------------------------------------------- */
bool CFpsControl::GetDrawFrag() {
	return m_isDraw;
}

/* ----------------------------------------------
	・GetFPS()
		FPSgetter
---------------------------------------------- */
int CFpsControl::GetFPS() {
	return m_FPS;
}

/* ----------------------------------------------
	・GetSkipRate()
		フレームスキップgetter
---------------------------------------------- */
int CFpsControl::GetSkipRate() {
	return m_SkipRate;
}