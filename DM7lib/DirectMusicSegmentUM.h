namespace MifuminLib {
	namespace DM7Lib {

#pragma region Unmanaged Classes

		// アンマネージドなDirectMusicSegmentクラス
		private class DirectMusicSegmentUM
		{
		private:
			IDirectMusicSegment* m_lpSegment;
			IDirectMusicSegmentState* m_lpState;
		public:
			DirectMusicSegmentUM(IDirectMusicPerformance* pPerf, IDirectMusicLoader* pLoader, WCHAR* wszMidiFileName);
			~DirectMusicSegmentUM();

			HRESULT Play(IDirectMusicPerformance* pPerf, DWORD dwFlags, __int64 i64StartTime);
			HRESULT Stop(IDirectMusicPerformance* pPerf);
			HRESULT SetRepeats(DWORD dwRepeats);
			HRESULT SetLoopPoints(MUSIC_TIME mtStart, MUSIC_TIME mtEnd);
			MUSIC_TIME GetLength();
			MUSIC_TIME GetSeek();
			bool IsPlaying(IDirectMusicPerformance* pPerf);
			bool IsLoaded();
		};

	}
}
