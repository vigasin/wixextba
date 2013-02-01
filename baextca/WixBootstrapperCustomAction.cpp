//-------------------------------------------------------------------------------------------------
// <copyright file="WixBootstrapperCustomAction.cpp" company="X2 Systems Limited">
//   Copyright (c) 2013, X2 Systems Limited.
//   This software is released under Microsoft Reciprocal License (MS-RL).
//   The license and further copyright text can be found in the file
//   LICENSE.TXT at the root directory of the distribution.
// </copyright>
//-------------------------------------------------------------------------------------------------


#include "precomp.h"

extern "C" HRESULT WINAPI OnDetectBeginCustomAction(
    __in IBootstrapperEngine* pEngine
    )
{
    HRESULT hr = S_OK;
    HKEY hkKey = NULL;
    LPWSTR sczValue = NULL;
    LPWSTR sczFormatedValue = NULL;
    ULARGE_INTEGER uliVersion = { };

    // This is required to enable logging functions
    BalInitialize(pEngine);

    BalLog(BOOTSTRAPPER_LOG_LEVEL_STANDARD, "OnDetectBeginCustomAction()");

    // Example of setting a variables
    hr = pEngine->SetVariableString(L"Variable1", L"String value");
    BalExitOnFailure(hr, "Failed to set variable.");
    hr = pEngine->SetVariableNumeric(L"Variable2", 1234);
    BalExitOnFailure(hr, "Failed to set variable.");
    //---------------------------------------------------------------------------------------------


    //---------------------------------------------------------------------------------------------
    // Example of reading burn variable.
    BalGetStringVariable(L"WixBundleName", &sczValue);
    BalExitOnFailure(hr, "Failed to get variable.");

    hr = pEngine->SetVariableString(L"Variable4", sczValue);
    BalExitOnFailure(hr, "Failed to set variable.");
    //---------------------------------------------------------------------------------------------

    ReleaseNullStr(sczValue); // Release string so it can be re-used

    //---------------------------------------------------------------------------------------------
    // Examples of reading burn variable and formatting it.
    BalGetStringVariable(L"InstallFolder", &sczValue);
    BalExitOnFailure(hr, "Failed to get variable.");

    hr = pEngine->SetVariableString(L"Variable5", sczValue);
    BalExitOnFailure(hr, "Failed to set variable.");

    BalFormatString(sczValue, &sczFormatedValue);
    BalExitOnFailure(hr, "Failed to format variable.");

    hr = pEngine->SetVariableString(L"Variable6", sczFormatedValue);
    BalExitOnFailure(hr, "Failed to set variable.");
    //---------------------------------------------------------------------------------------------

    ReleaseNullStr(sczValue); // Release string so it can be re-used
        
    //---------------------------------------------------------------------------------------------
    BalFormatString(L"WixBundleVersion=[WixBundleVersion]", &sczValue);
    BalExitOnFailure(hr, "Failed to format variable.");

    hr = pEngine->SetVariableString(L"Variable7", sczValue);
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

    hr = pEngine->SetVariableString(L"InstallFolder", sczValue);
    BalExitOnFailure(hr, "Failed to set variable.");
    //---------------------------------------------------------------------------------------------

    ReleaseNullStr(sczValue); // Release string so it can be re-used

    //---------------------------------------------------------------------------------------------
    // Example of function call to get the file version of this bundle
    BalFormatString(L"[WixBundleOriginalSource]", &sczValue);
    BalExitOnFailure(hr, "Failed to format variable.");

    FileVersion(sczValue, &uliVersion.HighPart, &uliVersion.LowPart);
    BalExitOnFailure(hr, "Failed to get file version.");

    hr = pEngine->SetVariableVersion(L"FileVersion", uliVersion.QuadPart);
    BalExitOnFailure(hr, "Failed to set variable.");
    //---------------------------------------------------------------------------------------------

LExit:
    ReleaseRegKey(hkKey);
    ReleaseStr(sczValue);
    ReleaseStr(sczFormatedValue);

    return hr;
}

