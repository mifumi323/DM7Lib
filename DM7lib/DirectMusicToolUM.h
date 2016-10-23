#pragma once

namespace MifuminLib {
	namespace DM7Lib {

		// アンマネージドなDirectMusicToolクラス
		private class DirectMusicToolUM : public IDirectMusicTool
		{
		public:
			DirectMusicToolUM();
			~DirectMusicToolUM();

			// IUnknownインターフェースの実装
			virtual STDMETHODIMP QueryInterface(const IID &iid, void **ppv);
			virtual STDMETHODIMP_(ULONG) AddRef();
			virtual STDMETHODIMP_(ULONG) Release();

			// IDirectMusicToolインターフェースの実装
			HRESULT STDMETHODCALLTYPE Init(IDirectMusicGraph* pGraph);
			HRESULT STDMETHODCALLTYPE GetMsgDeliveryType(DWORD* pdwDeliveryType);
			HRESULT STDMETHODCALLTYPE GetMediaTypeArraySize(DWORD* pdwNumElements);
			HRESULT STDMETHODCALLTYPE GetMediaTypes(DWORD** padwMediaTypes, DWORD dwNumElements);
			HRESULT STDMETHODCALLTYPE ProcessPMsg(IDirectMusicPerformance* pPerf,DMUS_PMSG* pDMUS_PMSG);
			HRESULT STDMETHODCALLTYPE Flush(IDirectMusicPerformance* pPerf,DMUS_PMSG* pDMUS_PMSG,REFERENCE_TIME rtTime);

		private:
			long m_cRef; // 参照カウンタ。
			CRITICAL_SECTION m_CrSec; // メンバ変数をスレッドセーフにする。

			int m_nID;
		};

	}
}
