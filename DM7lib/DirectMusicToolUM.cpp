#include "stdafx.h"
#include "DirectMusicToolUM.h"
#include "DirectMusic.h"

using namespace MifuminLib::DM7Lib;

DirectMusicToolUM::DirectMusicToolUM() : m_cRef(1)
{
	InitializeCriticalSection(&m_CrSec);
}

DirectMusicToolUM::~DirectMusicToolUM()
{
	DeleteCriticalSection(&m_CrSec);
}

STDMETHODIMP DirectMusicToolUM::QueryInterface(const IID &iid, void **ppv)
{
	if (iid == IID_IUnknown || iid == IID_IDirectMusicTool)
	{
		*ppv = static_cast<IDirectMusicTool*>(this);
	} else
	{
		*ppv = NULL;
		return E_NOINTERFACE;
	}

	reinterpret_cast<IUnknown*>(this)->AddRef();
	return S_OK;
}

STDMETHODIMP_(ULONG) DirectMusicToolUM::AddRef()
{
	return InterlockedIncrement(&m_cRef);
}

STDMETHODIMP_(ULONG) DirectMusicToolUM::Release()
{
	if( 0 == InterlockedDecrement(&m_cRef) )
	{
		delete this;
		return 0;
	}
	return m_cRef;
}

HRESULT STDMETHODCALLTYPE DirectMusicToolUM::Init(IDirectMusicGraph* pGraph)
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE DirectMusicToolUM::GetMsgDeliveryType(DWORD* pdwDeliveryType)
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE DirectMusicToolUM::GetMediaTypeArraySize(DWORD* pdwNumElements)
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE DirectMusicToolUM::GetMediaTypes(DWORD** padwMediaTypes, DWORD dwNumElements)
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE DirectMusicToolUM::ProcessPMsg(IDirectMusicPerformance* pPerf,DMUS_PMSG* pDMUS_PMSG)
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE DirectMusicToolUM::Flush(IDirectMusicPerformance* pPerf,DMUS_PMSG* pDMUS_PMSG,REFERENCE_TIME rtTime)
{
	return E_NOTIMPL;
}
