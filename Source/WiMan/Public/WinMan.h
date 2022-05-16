// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/Button.h"
#include "WinMan.generated.h"

/**
 * 
 */
UCLASS()
class WIMAN_API UWinMan : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Data")
		FVector2D MousePos;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Data")
		FVector2D MousePosOffset;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Data")
		FVector2D MinSize = FVector2D(480, 360);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WiMan: Settings")
		FLinearColor WindowColor = FLinearColor(0.02, 0.02, 0.02, 0.975);
	
	UCanvasPanel* CanvasRef;
	UCanvasPanelSlot* CanvasAsSlot;
	UButton* TitleButtonRef;
	UButton* RescaleCornerButtonRef;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WiMan: Settings")
		bool bCanDrag = true;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WiMan: Settings")
		bool bCanRescale = true;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "WiMan: Settings")
		bool bEnableDebug = false;
	
	FTimerHandle TimerHandle;

	UFUNCTION(BlueprintCallable, Category = "WiMan")
		void Drag();
	UFUNCTION(BlueprintCallable, Category = "WiMan")
		void Rescale();

	UFUNCTION(BlueprintCallable, Category = "WiMan")
		void SetDragClickLocDiff();
	UFUNCTION(BlueprintCallable, Category = "WiMan")
		void SetRescaleClickLocDiff();
	UFUNCTION(BlueprintCallable, Category = "WiMan")
		bool CheckMinRes();
	UFUNCTION(BlueprintCallable, Category = "WiMan")
		void FixWindowRes();

	UFUNCTION(BlueprintCallable, Category = "WiMan: Update")
		void UpdateDragLocation();
	UFUNCTION(BlueprintCallable, Category = "WiMan: Update")
		void StopUpdateDragLocation();
	UFUNCTION(BlueprintCallable, Category = "WiMan: Update")
		void UpdateScaleLocation();
	UFUNCTION(BlueprintCallable, Category = "WiMan: Update")
		void StopUpdateScaleLocation();

	UFUNCTION(BlueprintCallable, Category = "WiMan: OnPressed")
		void DragOnPressed();
	UFUNCTION(BlueprintCallable, Category = "WiMan: OnPressed")
		void RescaleOnPressed();

	UFUNCTION(BlueprintCallable, Category = "WiMan: Settings")
		void ConfigReferences(UCanvasPanel* Canvas, UButton* TitleButton, UButton* CornerButton);
};
