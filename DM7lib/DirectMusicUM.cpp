#include "stdafx.h"
#include "DirectMusicUM.h"
#include "DirectMusicSegmentUM.h"

using namespace MifuminLib::DM7Lib;

DirectMusicUM::DirectMusicUM()
{
	// 念のための初期化
	m_bIsValid = true;
	m_lpPerf = NULL;
	m_lpMusic = NULL;
	m_lpLoader = NULL;
	m_lpPort = NULL;

	if (FAILED(::CoInitialize(NULL))) { m_bIsValid = false; return; }

	// パフォーマンスの初期化
	if (FAILED(CoCreateInstance(
		CLSID_DirectMusicPerformance,
		NULL,
		CLSCTX_INPROC,
		IID_IDirectMusicPerformance2,
		(void**)&m_lpPerf
		)))
	{ CloseDown(); return; }
	if (FAILED(m_lpPerf->Init(&m_lpMusic, NULL, NULL))) { CloseDown(); return; }

	// ポートの初期化
	if (FAILED(SelectDefaultPort())) { CloseDown(); return; }

	// ローダーの初期化
	if (FAILED(CoCreateInstance(
		CLSID_DirectMusicLoader,
		NULL,
		CLSCTX_INPROC,
		IID_IDirectMusicLoader,
		(void**)&m_lpLoader)))
	{ CloseDown(); return; }
}

DirectMusicUM::~DirectMusicUM() { CloseDown(); }

void DirectMusicUM::CloseDown()
{
	if (!m_bIsValid) return;
	if (m_lpPerf!=NULL) {
		m_lpPerf->Stop(NULL, NULL, 0, 0);
		m_lpPerf->CloseDown();
		m_lpPerf->Release();
		m_lpPerf = NULL;
	}
	if (m_lpPort!=NULL) {
		m_lpPort->Release();
		m_lpPort = NULL;
	}
	if (m_lpLoader!=NULL) {
		m_lpLoader->Release();
		m_lpLoader = NULL;
	}
	if (m_lpMusic!=NULL) {
		m_lpMusic->Release();
		m_lpMusic = NULL;
	}
	::CoUninitialize();
	m_bIsValid = false;
}

HRESULT DirectMusicUM::SelectPort(REFCLSID rclsidPort)
{
	if (!m_bIsValid) return E_FAIL;
	if (m_lpPort!=NULL) {
		m_lpPerf->RemovePort(m_lpPort);
		m_lpPort->Release();
		m_lpPort = NULL;
	}
	DMUS_PORTPARAMS p_params = { sizeof(DMUS_PORTPARAMS) };
	p_params.dwEffectFlags = DMUS_EFFECT_REVERB;
	p_params.dwChannelGroups = 1;
	p_params.dwValidParams = DMUS_PORTPARAMS_CHANNELGROUPS | DMUS_PORTPARAMS_EFFECTS;
	if (FAILED(m_lpMusic->CreatePort(rclsidPort, &p_params, &m_lpPort, NULL))) return E_FAIL;
	if (FAILED(m_lpPort->Activate(true))) return E_FAIL;
	if (FAILED(m_lpPerf->AddPort(m_lpPort))) return E_FAIL;
	if (FAILED(m_lpPerf->AssignPChannelBlock(0, m_lpPort, 1))) return E_FAIL;
	return S_OK;
}

HRESULT DirectMusicUM::SelectDefaultPort()
{
	if (!m_bIsValid) return E_FAIL;
	GUID guid=GUID_NULL;
	if (FAILED(m_lpMusic->GetDefaultPort(&guid))) { return E_FAIL; }
	return SelectPort(guid);
}

HRESULT DirectMusicUM::EnumPort(DWORD dwIndex, DMUS_PORTCAPS& rPortCaps)
{
	if (!m_bIsValid) return E_FAIL;
	rPortCaps.dwSize = sizeof(DMUS_PORTCAPS);
	return m_lpMusic->EnumPort(dwIndex, &rPortCaps);
}

DirectMusicSegmentUM* DirectMusicUM::LoadSegment(WCHAR* wszMidiFileName)
{
	if (!m_bIsValid) return NULL;
	return new DirectMusicSegmentUM(m_lpPerf, m_lpLoader, wszMidiFileName);
}

void DirectMusicUM::UnloadSegment(DirectMusicSegmentUM* pSegment)
{
	if (!m_bIsValid) return;
	delete pSegment;
}

HRESULT DirectMusicUM::Play(DirectMusicSegmentUM* pSegment, DWORD dwFlags, __int64 i64StartTime)
{
	if (!m_bIsValid) return E_FAIL;
	if (pSegment==NULL) return E_FAIL;
	return pSegment->Play(m_lpPerf, dwFlags, i64StartTime);
}

bool DirectMusicUM::IsPlaying(DirectMusicSegmentUM* pSegment)
{
	if (!m_bIsValid) return false;
	if (pSegment==NULL) return false;
	return pSegment->IsPlaying(m_lpPerf);
}

HRESULT DirectMusicUM::Stop()
{
	if (!m_bIsValid) return E_FAIL;
	return m_lpPerf->Stop(NULL, NULL, 0, 0);
}

HRESULT DirectMusicUM::Stop(DirectMusicSegmentUM* pSegment)
{
	if (!m_bIsValid) return E_FAIL;
	return pSegment->Stop(m_lpPerf);
}

HRESULT DirectMusicUM::SetMasterVolume(long mbVolume)
{
	if (!m_bIsValid) return E_FAIL;
	return m_lpPerf->SetGlobalParam(GUID_PerfMasterVolume, &mbVolume, sizeof(mbVolume));
}

HRESULT DirectMusicUM::SetMasterTempo(float fTempo)
{
	if (!m_bIsValid) return E_FAIL;
	return m_lpPerf->SetGlobalParam(GUID_PerfMasterTempo, &fTempo, sizeof(fTempo));
}

HRESULT DirectMusicUM::GMReset()
{
	BYTE msg[] = { 0xF0, 0x7E, 0x7F, 0x09, 0x01, 0xF7 };
	return SendSysExMsg(msg, sizeof(msg));
}

HRESULT DirectMusicUM::GSReset()
{
	BYTE msg[] = { 0xF0, 0x41, 0x10, 0x42, 0x12, 0x40, 0x00, 0x7F, 0x00, 0x41, 0xF7 };
	return SendSysExMsg(msg, sizeof(msg));
}

HRESULT DirectMusicUM::XGReset()
{
	BYTE msg[] = { 0xF0, 0x43, 0x10, 0x4C, 0x00, 0x00, 0x7E, 0x00, 0xF7 };
	return SendSysExMsg(msg, sizeof(msg));
}

HRESULT DirectMusicUM::SendSysExMsg(LPBYTE pbSysExData, DWORD dwSysExLength)
{
	// グラフを取得する
	IDirectMusicGraph* pGraph;
	if ( FAILED( m_lpPerf->QueryInterface( IID_IDirectMusicGraph, (void**)&pGraph )))
		return E_FAIL;

	// SysExメッセージを作成
	DMUS_SYSEX_PMSG* pSysEx;
	if ( FAILED( m_lpPerf->AllocPMsg( 
			sizeof(DMUS_SYSEX_PMSG) + dwSysExLength,
			(DMUS_PMSG**)&pSysEx ))) {
		pGraph->Release();
		return E_FAIL;
	}

	// メッセージの設定
	memcpy( pSysEx->abData, pbSysExData, dwSysExLength );
	pSysEx->dwSize = sizeof(DMUS_SYSEX_PMSG);
	pSysEx->dwLen = dwSysExLength;
	pSysEx->rtTime = 0;
	pSysEx->dwFlags = DMUS_PMSGF_REFTIME;
	pSysEx->dwType = DMUS_PMSGT_SYSEX;

	// メッセージの送信
	pGraph->StampPMsg( (DMUS_PMSG*)pSysEx );
	if (FAILED(m_lpPerf->SendPMsg( (DMUS_PMSG*)pSysEx ))) {
		m_lpPerf->FreePMsg( (DMUS_PMSG*)pSysEx );
		pGraph->Release();
		return E_FAIL;
	}

	pGraph->Release();
	return S_OK;
}

bool DirectMusicUM::IsValid() { return m_bIsValid; }
