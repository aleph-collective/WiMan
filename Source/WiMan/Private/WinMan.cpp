// Fill out your copyright notice in the Description page of Project Settings.


#include "WinMan.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"

void UWinMan::NativeConstruct()
{
	Super::NativeConstruct();

	if(RescaleCornerButtonRef)
	{
		if(!RescaleCornerButtonRef->OnPressed.IsBound())
		{
			RescaleCornerButtonRef->OnPressed.AddDynamic(this, &UWinMan::RescaleOnPressed);
		}

		if(!RescaleCornerButtonRef->OnReleased.IsBound())
		{
			RescaleCornerButtonRef->OnReleased.AddDynamic(this, &UWinMan::StopUpdateScaleLocation);
		}
	}

	if(TitleButtonRef)
	{
		if(!TitleButtonRef->OnPressed.IsBound())
		{
			TitleButtonRef->OnPressed.AddDynamic(this, &UWinMan::DragOnPressed);
		}

		if(!TitleButtonRef->OnReleased.IsBound())
		{
			TitleButtonRef->OnReleased.AddDynamic(this, &UWinMan::StopUpdateDragLocation);
		}
	}
}

void UWinMan::Drag()
{
	CanvasAsSlot = Cast<UCanvasPanelSlot>(CanvasRef->Slot);
	MousePos = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
	CanvasAsSlot->SetPosition(MousePos - MousePosOffset);
}

void UWinMan::Rescale()
{
	CanvasAsSlot = Cast<UCanvasPanelSlot>(CanvasRef->Slot);
	MousePos = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
	CanvasAsSlot->SetSize((MousePos - MousePosOffset) - (CanvasAsSlot->GetPosition() + CanvasAsSlot->GetSize()) + CanvasAsSlot->GetSize());
}

void UWinMan::SetDragClickLocDiff()
{
	CanvasAsSlot = Cast<UCanvasPanelSlot>(CanvasRef->Slot);
	FVector2D PosOnViewport = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
	MousePosOffset = PosOnViewport - CanvasAsSlot->GetPosition();
}

void UWinMan::SetRescaleClickLocDiff()
{
	CanvasAsSlot = Cast<UCanvasPanelSlot>(CanvasRef->Slot);
	FVector2D PosOnViewport = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
	MousePosOffset = PosOnViewport - (CanvasAsSlot->GetPosition() + CanvasAsSlot->GetSize());
}

bool UWinMan::CheckMinRes()
{
	CanvasAsSlot = Cast<UCanvasPanelSlot>(CanvasRef->Slot);
	return CanvasAsSlot->GetSize().X < MinSize.X && CanvasAsSlot->GetSize().Y < MinSize.Y;
}

void UWinMan::FixWindowRes()
{
	CanvasAsSlot = Cast<UCanvasPanelSlot>(CanvasRef->Slot);
	CanvasAsSlot->SetSize(MinSize);
}

void UWinMan::UpdateDragLocation()
{
	if (bCanDrag) {
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UWinMan::UpdateDragLocation, 0.02f, true);
		Drag();
	}
}

void UWinMan::StopUpdateDragLocation()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}

void UWinMan::UpdateScaleLocation()
{
	if (bCanRescale) {
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UWinMan::UpdateScaleLocation, 0.02f, true);
		if (CheckMinRes()) {
			StopUpdateScaleLocation();
			FixWindowRes();
		} else {
			Rescale();
		};
	};
}

void UWinMan::StopUpdateScaleLocation()
{
	CanvasAsSlot = Cast<UCanvasPanelSlot>(RescaleCornerButtonRef->Slot);
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	CanvasAsSlot->SetPosition(FVector2D(0, 0));
}

void UWinMan::DragOnPressed()
{
	SetDragClickLocDiff();
	UpdateDragLocation();
}

void UWinMan::RescaleOnPressed()
{
	SetRescaleClickLocDiff();
	UpdateScaleLocation();
}

void UWinMan::ConfigReferences(UCanvasPanel* Canvas, UButton* TitleButton, UButton* CornerButton)
{
	CanvasRef = Canvas;
	TitleButtonRef = TitleButton;
	RescaleCornerButtonRef = CornerButton;
}
