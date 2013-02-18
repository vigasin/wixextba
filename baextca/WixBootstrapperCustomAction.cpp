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
    STDMETHODIMP OnDetectCustomAction()
    {
        HRESULT hr = S_OK;
        HKEY hkKey = NULL;
        LPWSTR sczValue = NULL;
        LPWSTR sczFormatedValue = NULL;

        BalLog(BOOTSTRAPPER_LOG_LEVEL_STANDARD, "Running detect custom action");

        //---------------------------------------------------------------------------------------------
        // Example of custom action failure
        //hr = E_NOTIMPL;
        //BalExitOnFailure(hr, "Test failure.");
        //---------------------------------------------------------------------------------------------

        //---------------------------------------------------------------------------------------------
        // Example of setting a variables
        hr = m_pEngine->SetVariableString(L"Variable1", L"String value");
        BalExitOnFailure(hr, "Failed to set variable.");
        hr = m_pEngine->SetVariableNumeric(L"Variable2", 1234);
        BalExitOnFailure(hr, "Failed to set variable.");
        //---------------------------------------------------------------------------------------------

        //---------------------------------------------------------------------------------------------
        // Example of reading burn variable.
        BalGetStringVariable(L"WixBundleName", &sczValue);
        BalExitOnFailure(hr, "Failed to get variable.");

        hr = m_pEngine->SetVariableString(L"Variable4", sczValue);
        BalExitOnFailure(hr, "Failed to set variable.");
        //---------------------------------------------------------------------------------------------

        ReleaseNullStr(sczValue); // Release string so it can be re-used

        //---------------------------------------------------------------------------------------------
        // Examples of reading burn variable and formatting it.
        BalGetStringVariable(L"InstallFolder", &sczValue);
        BalExitOnFailure(hr, "Failed to get variable.");

        hr = m_pEngine->SetVariableString(L"Variable5", sczValue);
        BalExitOnFailure(hr, "Failed to set variable.");

        BalFormatString(sczValue, &sczFormatedValue);
        BalExitOnFailure(hr, "Failed to format variable.");

        hr = m_pEngine->SetVariableString(L"Variable6", sczFormatedValue);
        BalExitOnFailure(hr, "Failed to set variable.");
        //---------------------------------------------------------------------------------------------

        ReleaseNullStr(sczValue); // Release string so it can be re-used

        //---------------------------------------------------------------------------------------------
        BalFormatString(L"WixBundleVersion=[WixBundleVersion]", &sczValue);
        BalExitOnFailure(hr, "Failed to format variable.");

        hr = m_pEngine->SetVariableString(L"Variable7", sczValue);
        BalExitOnFailure(hr, "Failed to set variable.");
        //---------------------------------------------------------------------------------------------

        ReleaseNullStr(sczValue); // Release string so it can be re-used

        //---------------------------------------------------------------------------------------------
        // Example of reading 64 bit registry and setting the InstallFolder variable to the value read.
        hr = RegOpen(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\NET Framework Setup\\NDP\\v3.5", KEY_READ | KEY_WOW64_64KEY, &hkKey);
        BalExitOnFailure(hr, "Failed to open registry key.");

        hr = RegReadString(hkKey, L"InstallPath", &sczValue);
        BalExitOnFailure(hr, "Failed to read registry value.");

        // Example of function call
        PathBackslashTerminate(&sczValue);

        hr = m_pEngine->SetVariableString(L"InstallFolder", sczValue);
        BalExitOnFailure(hr, "Failed to set variable.");
        //---------------------------------------------------------------------------------------------

        ReleaseNullStr(sczValue); // Release string so it can be re-used

        //---------------------------------------------------------------------------------------------
        hr = PathRelativeToModule(&sczValue, NULL, m_hModule);
        hr = m_pEngine->SetVariableString(L"ModulePath", sczValue);
        //---------------------------------------------------------------------------------------------

        ReleaseNullStr(sczValue); // Release string so it can be re-used

        //---------------------------------------------------------------------------------------------
        hr = GetFileVersion();
        BalExitOnFailure(hr, "Failed to get version.");
        //---------------------------------------------------------------------------------------------

    LExit:
        ReleaseRegKey(hkKey);
        ReleaseStr(sczValue);
        ReleaseStr(sczFormatedValue);

        return hr;
    }


    STDMETHODIMP OnDetectCompleteCustomAction()
    {
        BalLog(BOOTSTRAPPER_LOG_LEVEL_STANDARD, "Running detect complete custom action");
        return S_OK;
    }

        
    STDMETHODIMP OnPlanCustomAction()
    {
        HRESULT hr = S_OK;

        BalLog(BOOTSTRAPPER_LOG_LEVEL_STANDARD, "Running plan custom action");

        //---------------------------------------------------------------------------------------------
        // Example of converting 4 radio button values in to 1
        LONGLONG llValue = 0;
        if (SUCCEEDED(BalGetNumericVariable(L"RadioButton1", &llValue)) && llValue)
        {
            m_pEngine->SetVariableNumeric(L"RadioButton", 1);
            BalExitOnFailure(hr, "Failed to set variable.");
        }
        else if (SUCCEEDED(BalGetNumericVariable(L"RadioButton2", &llValue)) && llValue)
        {
            m_pEngine->SetVariableNumeric(L"RadioButton", 2);
            BalExitOnFailure(hr, "Failed to set variable.");
        }
        else if (SUCCEEDED(BalGetNumericVariable(L"RadioButton3", &llValue)) && llValue)
        {
            m_pEngine->SetVariableNumeric(L"RadioButton", 3);
            BalExitOnFailure(hr, "Failed to set variable.");
        }
        else if (SUCCEEDED(BalGetNumericVariable(L"RadioButton4", &llValue)) && llValue)
        {
            m_pEngine->SetVariableNumeric(L"RadioButton", 4);
            BalExitOnFailure(hr, "Failed to set variable.");
        }
        else
        {
            m_pEngine->SetVariableNumeric(L"RadioButton", 0);
            BalExitOnFailure(hr, "Failed to set variable.");
        }
        //---------------------------------------------------------------------------------------------

    LExit:
        return hr;
    }


    STDMETHODIMP OnPlanCompleteCustomAction()
    {
        BalLog(BOOTSTRAPPER_LOG_LEVEL_STANDARD, "Running plan complete custom action");
        return S_OK;
    }

private:
    //---------------------------------------------------------------------------------------------
    // Example of function call to get the file version of this bundle
    //---------------------------------------------------------------------------------------------
    HRESULT GetFileVersion()
    {
        HRESULT hr = S_OK;
        LPWSTR sczValue = NULL;
        ULARGE_INTEGER uliVersion = { };

        BalFormatString(L"[WixBundleOriginalSource]", &sczValue);
        BalExitOnFailure(hr, "Failed to format variable.");

        FileVersion(sczValue, &uliVersion.HighPart, &uliVersion.LowPart);
        BalExitOnFailure(hr, "Failed to get file version.");

        hr = m_pEngine->SetVariableVersion(L"FileVersion", uliVersion.QuadPart);
        BalExitOnFailure(hr, "Failed to set variable.");

    LExit:
        ReleaseStr(sczValue);

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
