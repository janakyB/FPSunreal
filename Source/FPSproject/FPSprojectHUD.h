// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FPSprojectHUD.generated.h"


UCLASS()
class AFPSprojectHUD : public AHUD
{
	GENERATED_BODY()
		 
public:
	AFPSprojectHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

	virtual void BeginPlay() override; 

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

	UPROPERTY(EditAnyWhere, Category = Health)
		TSubclassOf<class UUserWidget> HUDWidgetClass;

	UPROPERTY(EditAnyWhere, Category = Health)
		class UUserWidget* CurrentWidget;
};

