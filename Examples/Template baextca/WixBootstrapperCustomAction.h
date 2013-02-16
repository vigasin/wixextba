//-------------------------------------------------------------------------------------------------
// <copyright file="WixBootstrapperCustomAction.h" company="X2 Systems Limited">
//   Copyright (c) 2013, X2 Systems Limited.
//   This software is released under Microsoft Reciprocal License (MS-RL).
//   The license and further copyright text can be found in the file
//   LICENSE.TXT at the root directory of the distribution.
// </copyright>
//-------------------------------------------------------------------------------------------------

#include <windows.h>

#include "IBootstrapperEngine.h"
//#include "IBootstrapperApplication.h"

interface IWixBootstrapperCustomAction
{
public:
    virtual STDMETHODIMP OnDetectCustomAction() {};
    virtual STDMETHODIMP OnPlanCustomAction() {};
};

extern "C" typedef HRESULT (WINAPI *PFN_BOOTSTRAPPER_CUSTOM_ACTION_CREATE)(
    __in IBootstrapperEngine* pEngine,
    __in HMODULE hModule,
    __out IWixBootstrapperCustomAction** ppCustomAction
    );

