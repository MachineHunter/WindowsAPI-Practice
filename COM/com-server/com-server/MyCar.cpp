#include "stdafx.h"
#include "MyCar.h"
#include "CarLocalServerTypeInfo_i.c"
#include <stdio.h> 
#include "locks.h"

// Construction/Destruction
MyCar::MyCar() : m_refCount(0), m_currSpeed(0), m_maxSpeed(0) {
	m_petName = SysAllocString(L"Default Pet Name");
	Lock();
}

MyCar::~MyCar() {
	UnLock();
	if (m_petName) SysFreeString(m_petName);
	MessageBox(NULL,
		"MyCar is being distructed. Make sure you see this message, if not, you might have memory leak!",
		"Destructor", MB_OK | MB_SETFOREGROUND);
}

// IUnknown
STDMETHODIMP MyCar::QueryInterface(REFIID riid, void** pIFace) {
	if (riid == IID_IUnknown) {
		*pIFace = (IUnknown*)(IEngine*)this;
		// MessageBox(NULL, "Handed out IUnknown","QI",MB_OK | MB_SETFOREGROUND);
	}
	else if (riid == IID_IEngine) {
		*pIFace = (IEngine*)this;
		// MessageBox(NULL, "Handed out IEngine","QI",MB_OK | MB_SETFOREGROUND);
	}
	else if (riid == IID_ICreateMyCar) {
		*pIFace = (ICreateMyCar*)this;
		// MessageBox(NULL, "Handed out ICreateMyCar","QI",MB_OK | MB_SETFOREGROUND);
	}
	else {
		*pIFace = NULL;
		return E_NOINTERFACE;
	}

	((IUnknown*)(*pIFace))->AddRef();
	return S_OK;
}

STDMETHODIMP_(DWORD) MyCar::AddRef() {
	++m_refCount;
	return m_refCount;
}

STDMETHODIMP_(DWORD) MyCar::Release() {
	if (--m_refCount == 0) {
		delete this;
		return 0;
	}
	else
		return m_refCount;
}

// IEngine
STDMETHODIMP MyCar::GetMaxSpeed(int* maxSpeed) {
	*maxSpeed = m_maxSpeed;
	return S_OK;
}


// ICreateMyCar
STDMETHODIMP MyCar::SetMaxSpeed(int maxSp) {
	if (maxSp < MAX_SPEED)
		m_maxSpeed = maxSp;
	return S_OK;
}
