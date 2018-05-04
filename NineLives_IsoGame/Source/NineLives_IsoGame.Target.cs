// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class NineLives_IsoGameTarget : TargetRules
{
	public NineLives_IsoGameTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "NineLives_IsoGame" } );
	}
}
