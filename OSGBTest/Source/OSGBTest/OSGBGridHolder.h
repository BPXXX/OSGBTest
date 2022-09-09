// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KismetProceduralMeshLibrary.h"
#include "ProceduralMeshComponent.h"
#include "OSGBGridHolder.generated.h"
class AOSGBMgr;
//struct FOSGGeom;
class OSGGeom;
UCLASS()
class OSGBTEST_API AOSGBGridHolder : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOSGBGridHolder();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		USceneComponent* RootComp;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		TArray<UProceduralMeshComponent*> PMeshArray;

	public:
		void DrawOSGBObject(const TArray<OSGGeom*>& Geoms);
};
