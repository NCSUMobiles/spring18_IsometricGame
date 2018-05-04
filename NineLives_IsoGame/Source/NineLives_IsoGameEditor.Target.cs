// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class NineLives_IsoGameEditorTarget : TargetRules
{
	public NineLives_IsoGameEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "NineLives_IsoGame" } );
	}
}
