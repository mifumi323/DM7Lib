#pragma once

namespace MifuminLib {
	namespace DM7Lib {

		// �A���}�l�[�W�h��DirectMusicTool�N���X
		private class DirectMusicToolUM : public IDirectMusicTool
		{
		public:
			DirectMusicToolUM();
			~DirectMusicToolUM();

			// IUnknown�C���^�[�t�F�[�X�̎���
			virtual STDMETHODIMP QueryInterface(const IID &iid, void **ppv);
			virtual STDMETHODIMP_(ULONG) AddRef();
			virtual STDMETHODIMP_(ULONG) Release();

			// IDirectMusicTool�C���^�[�t�F�[�X�̎���
			HRESULT STDMETHODCALLTYPE Init(IDirectMusicGraph* pGraph);
			HRESULT STDMETHODCALLTYPE GetMsgDeliveryType(DWORD* pdwDeliveryType);
			HRESULT STDMETHODCALLTYPE GetMediaTypeArraySize(DWORD* pdwNumElements);
			HRESULT STDMETHODCALLTYPE GetMediaTypes(DWORD** padwMediaTypes, DWORD dwNumElements);
			HRESULT STDMETHODCALLTYPE ProcessPMsg(IDirectMusicPerformance* pPerf,DMUS_PMSG* pDMUS_PMSG);
			HRESULT STDMETHODCALLTYPE Flush(IDirectMusicPerformance* pPerf,DMUS_PMSG* pDMUS_PMSG,REFERENCE_TIME rtTime);

		private:
			long m_cRef; // �Q�ƃJ�E���^�B
			CRITICAL_SECTION m_CrSec; // �����o�ϐ����X���b�h�Z�[�t�ɂ���B

			int m_nID;
		};

	}
}
