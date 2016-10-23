#include "stdafx.h"
#include "DirectMusicSegmentUM.h"

using namespace MifuminLib::DM7Lib;

DirectMusicSegmentUM::DirectMusicSegmentUM(IDirectMusicPerformance* pPerf, IDirectMusicLoader* pLoader, WCHAR* wszMidiFileName)
{
	m_lpSegment = NULL;
	DMUS_OBJECTDESC desc = { sizeof(DMUS_OBJECTDESC) };
	desc.dwValidData = DMUS_OBJ_CLASS | DMUS_OBJ_FILENAME | DMUS_OBJ_FULLPATH;
	desc.guidClass = CLSID_DirectMusicSegment;
	wcscpy_s(desc.wszFileName, 260, wszMidiFileName);
	if (FAILED(pLoader->GetObject(&desc, IID_IDirectMusicSegment2, (void**) &m_lpSegment))) {
		m_lpSegment = NULL;
		return;
	}
	m_lpSegment->SetParam(GUID_StandardMIDIFile, 0, 0, 0, (void*)pPerf);
	m_lpSegment->SetParam(GUID_Download, -1, 0, 0, (void*)pPerf);

	m_lpState = NULL;
}

DirectMusicSegmentUM::~DirectMusicSegmentUM()
{
	if (m_lpSegment==NULL) return;
	m_lpSegment->Release();
	if (m_lpState!=NULL) m_lpState->Release();
}

HRESULT DirectMusicSegmentUM::Play(IDirectMusicPerformance* pPerf, DWORD dwFlags, __int64 i64StartTime)
{
	if (m_lpState!=NULL) m_lpState->Release();
	return pPerf->PlaySegment(m_lpSegment, dwFlags, i64StartTime, &m_lpState);
}

HRESULT DirectMusicSegmentUM::SetRepeats(DWORD dwRepeats)
{
	if (m_lpSegment==NULL) return E_FAIL;
	return m_lpSegment->SetRepeats(dwRepeats);
}

HRESULT DirectMusicSegmentUM::SetLoopPoints(MUSIC_TIME mtStart, MUSIC_TIME mtEnd)
{
	if (m_lpSegment==NULL) return E_FAIL;
	return m_lpSegment->SetLoopPoints(mtStart, mtEnd);
}

MUSIC_TIME DirectMusicSegmentUM::GetLength()
{
	if (m_lpSegment==NULL) return 0;
	MUSIC_TIME mt=0;
	if (FAILED(m_lpSegment->GetLength(&mt))) return 0;
	return mt;
}

bool DirectMusicSegmentUM::IsPlaying(IDirectMusicPerformance* pPerf)
{
	if (m_lpSegment==NULL) return false;
	return pPerf->IsPlaying(m_lpSegment, NULL)==S_OK;
}

MUSIC_TIME DirectMusicSegmentUM::GetSeek()
{
	if (m_lpState==NULL) return 0;
	MUSIC_TIME mt=0;
	if (FAILED(m_lpState->GetSeek(&mt))) return 0;
	return mt;
}

HRESULT DirectMusicSegmentUM::Stop(IDirectMusicPerformance* pPerf)
{
	if (m_lpSegment==NULL) return E_FAIL;
	return pPerf->Stop(m_lpSegment, NULL, 0, 0);
}

bool DirectMusicSegmentUM::IsLoaded() { return m_lpSegment!=NULL; }
