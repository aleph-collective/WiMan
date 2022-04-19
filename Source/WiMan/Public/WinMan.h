// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WinMan.generated.h"

/**
 * 
 */
UCLASS()
class WIMAN_API UWinMan : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Data")
		FVector2D MousePos;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Data")
		FVector2D MousePosOffset;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings")
		bool bIsDragEnable = true;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings")
		bool bEnableDebug = false;
};