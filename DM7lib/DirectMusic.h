#pragma once

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Collections::Generic;

#include "Enumrators.h"

namespace MifuminLib {
	namespace DM7Lib {

		class DirectMusicUM;

		ref class DirectMusicSegment;
		ref class DirectMusicTool;

		public ref class DirectMusic
		{
		private:
			ref struct CGUID {
				unsigned long Data1;
				unsigned short Data2, Data3;
				array<unsigned char>^ Data4;

				CGUID(GUID& guid) {
					Data1 = guid.Data1;
					Data2 = guid.Data2;
					Data3 = guid.Data3;
					Marshal::Copy((IntPtr)guid.Data4, Data4 = gcnew array<unsigned char>(8), 0, 8);
				}

				operator GUID()
				{
					GUID guid = { Data1, Data2, Data3 };
					Marshal::Copy(Data4, 0, (IntPtr)guid.Data4, 8);
					return guid;
				}
			};
			DirectMusicUM* m_pMusic;
			Dictionary<String^, CGUID^>^ m_dicPort;
			array<String^>^ m_aryPortName;

			static List<DirectMusicTool^>^ m_lstTool;

			void Cleanup();
		public:

			DirectMusic();
			~DirectMusic();
			!DirectMusic();

			void SelectPort(String^ portName);
			void SelectDefaultPort();
			array<String^>^ EnumPort();

			DirectMusicSegment^ CreateSegment(String^ strMidiFileName);
			void Play(DirectMusicSegment^ pSegment);
			void Play(DirectMusicSegment^ pSegment, SegmentFlags dwFlags, __int64 i64StartTime);
			bool IsPlaying(DirectMusicSegment^ pSegment);
			void Stop();
			void Stop(DirectMusicSegment^ pSegment);

			void SetMasterVolume(long mbVolume);
			void SetMasterTempo(float fTempo);

			bool IsValid();

			void Reset(MifuminLib::DM7Lib::Reset reset);

			static void MyFunc();
		};

	}
}
