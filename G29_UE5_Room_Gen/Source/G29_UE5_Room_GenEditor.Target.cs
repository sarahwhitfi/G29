// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class G29_UE5_Room_GenEditorTarget : TargetRules
{
	public G29_UE5_Room_GenEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "G29_UE5_Room_Gen" } );
	}
}
