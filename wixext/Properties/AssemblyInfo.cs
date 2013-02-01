//-------------------------------------------------------------------------------------------------
// <copyright file="AssemblyInfo.cs" company="X2 Systems Limited">
//   Copyright (c) 2013, X2 Systems Limited.
//   This software is released under Microsoft Reciprocal License (MS-RL).
//   The license and further copyright text can be found in the file LICENSE.TXT
//   LICENSE.TXT at the root directory of the distribution.
// </copyright>
// 
// <summary>
// The assembly information for the Windows Installer XML Toolset Bootstrapper Application Layer Extension.
// </summary>
//-------------------------------------------------------------------------------------------------

using System;
using System.Reflection;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

using Microsoft.Tools.WindowsInstallerXml;
using Microsoft.Tools.WindowsInstallerXml.Extensions;

[assembly: AssemblyTitle("WiX Toolset Bootstrapper Application Layer Extension")]
[assembly: AssemblyDescription("Windows Installer XML Toolset Bootstrapper Application Layer Extension")]
[assembly: AssemblyCulture("")]
[assembly: CLSCompliant(true)]
[assembly: ComVisible(false)]
[assembly: AssemblyDefaultWixExtension(typeof(BalExtension))]
