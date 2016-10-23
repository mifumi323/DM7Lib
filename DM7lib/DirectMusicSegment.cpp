#include "stdafx.h"
#include "DirectMusicSegment.h"
#include "DirectMusicSegmentUM.h"
#include "DirectMusicUM.h"

using namespace MifuminLib::DM7Lib;

DirectMusicSegment::~DirectMusicSegment()
{
	if (m_pSegment==NULL) return;
	delete m_pSegment;
	m_pSegment = NULL;
}

DirectMusicSegment::!DirectMusicSegment()
{
	if (m_pSegment==NULL) return;
	delete m_pSegment;
	m_pSegment = NULL;
}

void DirectMusicSegment::SetRepeats(DWORD dwRepeats)
{
	if (FAILED(m_pSegment->SetRepeats(dwRepeats))) throw gcnew Exception("SetRepeats Failed");
}

void DirectMusicSegment::SetRepeats(bool bRepeat)
{
	if (FAILED(m_pSegment->SetRepeats(bRepeat?-1:0))) throw gcnew Exception("SetRepeats Failed");
}

void DirectMusicSegment::SetLoopPoints(long mtStart, long mtEnd)
{
	if (FAILED(m_pSegment->SetLoopPoints(mtStart, mtEnd))) throw gcnew Exception("SetLoopPoints Failed");
}

void DirectMusicSegment::SetLoop(bool bRepeat, long mtStart, long mtEnd)
{
	if (FAILED(m_pSegment->SetRepeats(bRepeat?-1:0))) throw gcnew Exception("SetRepeats Failed");
	if (FAILED(m_pSegment->SetLoopPoints(mtStart, mtEnd))) throw gcnew Exception("SetLoopPoints Failed");
}

long DirectMusicSegment::GetLength()
{
	if (!m_pSegment->IsLoaded()) throw gcnew Exception("Segment is not Loaded");
	return m_pSegment->GetLength();
}

long DirectMusicSegment::GetSeek()
{
	if (!m_pSegment->IsLoaded()) throw gcnew Exception("Segment is not Loaded");
	return m_pSegment->GetSeek();
}

bool DirectMusicSegment::IsLoaded() { return m_pSegment->IsLoaded(); }

DirectMusicSegment::DirectMusicSegment(DirectMusicUM* pMusic, WCHAR* wszMidiFileName)
{
	m_pSegment = pMusic->LoadSegment(wszMidiFileName);
}

void DirectMusicSegment::Play(DirectMusicUM* pMusic, SegmentFlags dwFlags, __int64 i64StartTime)
{
	if (FAILED(pMusic->Play(m_pSegment, (DWORD)dwFlags, i64StartTime))) throw gcnew Exception("Play Fialed");
}

void DirectMusicSegment::Play(DirectMusicUM* pMusic)
{
	Play(pMusic, SegmentFlags::None, 0);
}

bool DirectMusicSegment::IsPlaying(DirectMusicUM* pMusic)
{
	if (!m_pSegment->IsLoaded()) throw gcnew Exception("Segment is not Loaded");
	return pMusic->IsPlaying(m_pSegment);
}

void DirectMusicSegment::Stop(DirectMusicUM* pMusic)
{
	if (!m_pSegment->IsLoaded()) throw gcnew Exception("Segment is not Loaded");
	if (FAILED(pMusic->Stop(m_pSegment))) throw gcnew Exception("Stop Fialed");
}
