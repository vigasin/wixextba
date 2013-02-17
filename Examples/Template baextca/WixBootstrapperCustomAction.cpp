//-------------------------------------------------------------------------------------------------
// <copyright file="WixBootstrapperCustomAction.cpp" company="X2 Systems Limited">
//   Copyright (c) 2013, X2 Systems Limited.
//   This software is released under Microsoft Reciprocal License (MS-RL).
//   The license and further copyright text can be found in the file
//   LICENSE.TXT at the root directory of the distribution.
// </copyright>
//-------------------------------------------------------------------------------------------------


#include "precomp.h"

class CWixBootstrapperCustomAction : IWixBootstrapperCustomAction
{
public:
    virtual STDMETHODIMP OnDetectCustomAction()
    {
        HRESULT hr = S_OK;

        BalLog(BOOTSTRAPPER_LOG_LEVEL_STANDARD, "Running detect custom action");

        //-------------------------------------------------------------------------------------------------
        // YOUR CODE GOES HERE
        BalExitOnFailure(hr, "Dummy.");
        //-------------------------------------------------------------------------------------------------

    LExit:
        return hr;
    }


    STDMETHODIMP OnPlanCustomAction()
    {
        HRESULT hr = S_OK;

        BalLog(BOOTSTRAPPER_LOG_LEVEL_STANDARD, "Running plan custom action");

        //-------------------------------------------------------------------------------------------------
        // YOUR CODE GOES HERE
        BalExitOnFailure(hr, "Dummy.");
        //-------------------------------------------------------------------------------------------------

    LExit:
        return hr;
    }


private:
    HMODULE m_hModule;
    IBootstrapperEngine* m_pEngine;


public:
    //
    // Constructor - initialize member variables.
    //
    CWixBootstrapperCustomAction(
        __in IBootstrapperEngine* pEngine,
        __in HMODULE hModule
        )
    {
        m_hModule = hModule;
        m_pEngine = pEngine;
    }

    //
    // Destructor - release member variables.
    //
    ~CWixBootstrapperCustomAction()
    {
    }
};


extern "C" HRESULT WINAPI CreateBootstrapperCustomAction(
    __in IBootstrapperEngine* pEngine,
    __in HMODULE hModule,
    __out CWixBootstrapperCustomAction** ppCustomAction
    )
{
    HRESULT hr = S_OK;

    // This is required to enable logging functions
    BalInitialize(pEngine);

    CWixBootstrapperCustomAction* pCustomAction = NULL;

    pCustomAction = new CWixBootstrapperCustomAction(pEngine, hModule);
    ExitOnNull(pCustomAction, hr, E_OUTOFMEMORY, "Failed to create new bootstrapper custom action object.");

    *ppCustomAction = pCustomAction;
    pCustomAction = NULL;

LExit:
    return hr;
}
