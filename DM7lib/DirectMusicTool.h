#pragma once

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Collections::Generic;

namespace MifuminLib {
	namespace DM7Lib {

		public ref class DirectMusicTool
		{
		public:
			virtual HRESULT Init(IDirectMusicGraph* pGraph) { return E_NOTIMPL; }
			virtual HRESULT GetMsgDeliveryType(DWORD* pdwDeliveryType) { return E_NOTIMPL; }
			virtual HRESULT GetMediaTypeArraySize(DWORD* pdwNumElements) { return E_NOTIMPL; }
			virtual HRESULT GetMediaTypes(DWORD** padwMediaTypes, DWORD dwNumElements) { return E_NOTIMPL; }
			virtual HRESULT ProcessPMsg(IDirectMusicPerformance* pPerf,DMUS_PMSG* pDMUS_PMSG) { return E_NOTIMPL; }
			virtual HRESULT Flush(IDirectMusicPerformance* pPerf,DMUS_PMSG* pDMUS_PMSG,REFERENCE_TIME rtTime) { return E_NOTIMPL; }
		};

	}
}
