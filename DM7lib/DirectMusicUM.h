namespace MifuminLib {
	namespace DM7Lib {

		class DirectMusicSegmentUM;

		// アンマネージドなDirectMusicクラス
		private class DirectMusicUM
		{
		private:
			bool m_bIsValid;
			IDirectMusicPerformance* m_lpPerf;
			IDirectMusic* m_lpMusic;
			IDirectMusicLoader* m_lpLoader;
			IDirectMusicPort* m_lpPort;

		public:
			DirectMusicUM();
			~DirectMusicUM();

			void CloseDown();
			HRESULT SelectPort(REFCLSID rclsidPort);
			HRESULT SelectDefaultPort();
			HRESULT EnumPort(DWORD dwIndex, DMUS_PORTCAPS& rPortCaps);
			DirectMusicSegmentUM* LoadSegment(WCHAR* wszMidiFileName);
			void UnloadSegment(DirectMusicSegmentUM* pSegment);
			HRESULT Play(DirectMusicSegmentUM* pSegment, DWORD dwFlags, __int64 i64StartTime);
			bool IsPlaying(DirectMusicSegmentUM* pSegment);
			HRESULT Stop();
			HRESULT Stop(DirectMusicSegmentUM* pSegment);
			HRESULT SetMasterVolume(long mbVolume);
			HRESULT SetMasterTempo(float fTempo);
			HRESULT GMReset();
			HRESULT GSReset();
			HRESULT XGReset();
			HRESULT SendSysExMsg(LPBYTE pbSysExData, DWORD dwSysExLength);
			bool IsValid();
		};

	}
}
