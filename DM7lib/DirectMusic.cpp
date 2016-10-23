#include "stdafx.h"
#include "DirectMusic.h"
#include "DirectMusicUM.h"
#include "DirectMusicSegment.h"
#include "DirectMusicTool.h"

using namespace MifuminLib::DM7Lib;

DirectMusic::DirectMusic()
{
	// DirectMusicの初期化
	m_pMusic = new DirectMusicUM();
	if (!m_pMusic->IsValid()) {
		delete m_pMusic;
		m_pMusic = NULL;
		throw gcnew Exception("Cannot Initialize DirectMusic");
	}

	// ポート情報の初期化
	m_dicPort = gcnew Dictionary<String^, CGUID^>();
	Queue<String^>^ qPort = gcnew Queue<String^>();
	for (int i=0; ; i++) {
		DMUS_PORTCAPS pc = { sizeof(DMUS_PORTCAPS) };
		if (m_pMusic->EnumPort(i, pc)!=S_OK) break;
		String^ strPortName = Marshal::PtrToStringUni((IntPtr)pc.wszDescription);
		m_dicPort[strPortName] = gcnew CGUID(pc.guidPort);
		qPort->Enqueue(strPortName);
	}
	qPort->CopyTo(m_aryPortName = gcnew array<String^>(qPort->Count), 0);

	// ツールの初期化
	m_lstTool = gcnew List<DirectMusicTool^>();
}

DirectMusic::~DirectMusic() { Cleanup(); }

DirectMusic::!DirectMusic() { Cleanup(); }

void DirectMusic::Cleanup()
{
	if (m_pMusic==NULL) return;
	delete m_pMusic;
	m_pMusic = NULL;
}

void DirectMusic::SelectPort(String^ portName)
{
	if (m_pMusic==NULL) throw gcnew Exception("Cannot Use DirectMusic");
	CGUID^ guid;
	if (m_dicPort->TryGetValue(portName, guid)) {
		if (FAILED(m_pMusic->SelectPort(guid))) throw gcnew Exception("SelectPort Failed");
	}
	else throw gcnew Exception("Port Not Found");
}

void DirectMusic::SelectDefaultPort()
{
	if (m_pMusic==NULL) throw gcnew Exception("Cannot Use DirectMusic");
	if (FAILED(m_pMusic->SelectDefaultPort())) throw gcnew Exception("SelectDefaultPort Failed");
}

array<String^>^ DirectMusic::EnumPort()
{
	if (m_pMusic==NULL) throw gcnew Exception("Cannot Use DirectMusic");
	return m_aryPortName;
}

DirectMusicSegment^ DirectMusic::CreateSegment(String^ strMidiFileName)
{
	if (m_pMusic==NULL) throw gcnew Exception("Cannot Use DirectMusic");
	WCHAR* wszMidiFileName = (WCHAR*)Marshal::StringToHGlobalUni(strMidiFileName).ToPointer();
	DirectMusicSegment^ ret = gcnew DirectMusicSegment(m_pMusic, wszMidiFileName);
	Marshal::FreeHGlobal((IntPtr)wszMidiFileName);
	return ret;
}

void DirectMusic::Play(DirectMusicSegment^ pSegment)
{
	Play(pSegment, SegmentFlags::None, 0);
}

void DirectMusic::Play(DirectMusicSegment^ pSegment, SegmentFlags dwFlags, __int64 i64StartTime)
{
	if (m_pMusic==NULL) throw gcnew Exception("Cannot Use DirectMusic");
	pSegment->Play(m_pMusic, dwFlags, i64StartTime);
}

bool DirectMusic::IsPlaying(DirectMusicSegment^ pSegment)
{
	if (m_pMusic==NULL) throw gcnew Exception("Cannot Use DirectMusic");
	return pSegment->IsPlaying(m_pMusic);
}

void DirectMusic::Stop()
{
	if (m_pMusic==NULL) throw gcnew Exception("Cannot Use DirectMusic");
	m_pMusic->Stop();
}

void DirectMusic::Stop(DirectMusicSegment^ pSegment)
{
	if (m_pMusic==NULL) throw gcnew Exception("Cannot Use DirectMusic");
	pSegment->Stop(m_pMusic);
}

void DirectMusic::SetMasterVolume(long mbVolume)
{
	if (m_pMusic==NULL) throw gcnew Exception("Cannot Use DirectMusic");
	if (FAILED(m_pMusic->SetMasterVolume(mbVolume))) throw gcnew Exception("SetMasterVolume Failed");
}

void DirectMusic::SetMasterTempo(float fTempo)
{
	if (m_pMusic==NULL) throw gcnew Exception("Cannot Use DirectMusic");
	if (FAILED(m_pMusic->SetMasterTempo(fTempo))) throw gcnew Exception("SetMasterTempo Failed");
}

bool DirectMusic::IsValid() { return m_pMusic!=NULL; }

void DirectMusic::Reset(MifuminLib::DM7Lib::Reset reset)
{
	switch (reset){
		case Reset::GM:
			if (FAILED(m_pMusic->GMReset())) throw gcnew Exception("GMReset Failed");
			break;
		case Reset::GS:
			if (FAILED(m_pMusic->GSReset())) throw gcnew Exception("GSReset Failed");
			break;
		case Reset::XG:
			if (FAILED(m_pMusic->XGReset())) throw gcnew Exception("XGReset Failed");
			break;
		default:
			throw gcnew Exception("Unknown Reset Method");
	}
}

void DirectMusic::MyFunc() { }
