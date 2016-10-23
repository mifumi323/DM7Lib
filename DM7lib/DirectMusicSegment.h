#pragma once

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Collections::Generic;

#include "Enumrators.h"

namespace MifuminLib {
	namespace DM7Lib {

		class DirectMusicSegmentUM;
		class DirectMusicUM;

		public ref class DirectMusicSegment
		{
		private:
			DirectMusicSegmentUM* m_pSegment;
		public:
			~DirectMusicSegment();
			!DirectMusicSegment();

			void SetRepeats(DWORD dwRepeats);
			void SetRepeats(bool bRepeat);
			void SetLoopPoints(long mtStart, long mtEnd);
			void SetLoop(bool bRepeat, long mtStart, long mtEnd);

			long GetLength();
			long GetSeek();
			bool IsLoaded();

		internal:
			DirectMusicSegment(DirectMusicUM* pMusic, WCHAR* wszMidiFileName);

			void Play(DirectMusicUM* pMusic, SegmentFlags dwFlags, __int64 i64StartTime);
			void Play(DirectMusicUM* pMusic);
			bool IsPlaying(DirectMusicUM* pMusic);
			void Stop(DirectMusicUM* pMusic);
		};

	}
}
