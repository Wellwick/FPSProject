// Copyright Epic Games, Inc. All Rights Reserved.


#include "FPSProjectGameModeBase.h"

void AFPSProjectGameModeBase::StartPlay() {
    Super::StartPlay();

    check(GEngine != nullptr);

    // Display a debug message for six seconds
    // The -1 "Key" value arguments prevents the message from being updated or
    // refreshed
    GEngine->AddOnScreenDebugMessage(-1, 6.0f, FColor::Yellow, TEXT("Hey planet, this is FPSGameMode!"));

}