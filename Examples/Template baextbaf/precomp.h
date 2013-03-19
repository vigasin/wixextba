//-------------------------------------------------------------------------------------------------
// <copyright file="precomp.h" company="X2 Systems Limited">
//   Copyright (c) 2013, X2 Systems Limited.
//   This software is released under Microsoft Reciprocal License (MS-RL).
//   The license and further copyright text can be found in the file
//   LICENSE.TXT at the root directory of the distribution.
// </copyright>
// 
// <summary>
//    Precompiled header for standard bootstrapper application.
// </summary>
//-------------------------------------------------------------------------------------------------

#pragma once


#include <windows.h>
#include <gdiplus.h>
#include <msiquery.h>
#include <objbase.h>
#include <shlobj.h>
#include <shlwapi.h>
#include <stdlib.h>
#include <strsafe.h>

// Standard WiX header files, include as required
#include "dutil.h"
//#include "memutil.h"
//#include "dictutil.h"
//#include "dirutil.h"
#include "fileutil.h"
//#include "locutil.h"
//#include "logutil.h"
#include "pathutil.h"
//#include "resrutil.h"
//#include "shelutil.h"
#include "strutil.h"
//#include "thmutil.h"
//#include "uriutil.h"
//#include "xmlutil.h"
#include "regutil.h"

//#include "IBootstrapperEngine.h"
//#include "IBootstrapperApplication.h"

#include "BalBaseBootstrapperApplication.h"
//#include "balinfo.h"
//#include "balcondition.h"
#include "balutil.h"

#include "WixBootstrapperBAFunction.h"

