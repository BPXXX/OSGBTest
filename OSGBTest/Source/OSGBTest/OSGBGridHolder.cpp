// Fill out your copyright notice in the Description page of Project Settings.


#include "OSGBGridHolder.h"
#include "OSGBMgr.h"
// Sets default values
AOSGBGridHolder::AOSGBGridHolder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComp->SetRelativeLocation(FVector(0, 0, 0));
	SetRootComponent(RootComp);
}

// Called when the game starts or when spawned
void AOSGBGridHolder::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOSGBGridHolder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOSGBGridHolder::DrawOSGBObject(const TArray<OSGGeom*>& Geoms)
{
	for (int i = 0; i < Geoms.Num(); i++)
	{
		OSGGeom* Geom = Geoms[i];
		if (Geom)
		{
			TArray<FVector> Verteces = Geom->vertexArray;
			TArray<FVector> Normals = Geom->normalArray;
			TArray<FVector2D> UV;
			if (!Geom->textCoordArray.IsEmpty())
			{
				UV = Geom->textCoordArray;
			}
			else
			{
				for (int j = 0; j < Verteces.Num(); j++)
				{
					UV.Add(FVector2D(1, 1));
				}
			}
			TArray<int> Triangles = Geom->triangleArray;
			FString compName = FString("bp_RoadMeshComp") + FString::FromInt(i);
			UProceduralMeshComponent* newPComp = NewObject<UProceduralMeshComponent>(this, *compName);
			newPComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
			newPComp->CreationMethod = EComponentCreationMethod::Instance;
			newPComp->RegisterComponent();
			TArray<FProcMeshTangent> tangents;
			TArray<FVector> normals;
			TArray<FColor> vertexColors;
			newPComp->CreateMeshSection(0, Verteces, Triangles, Normals, UV, TArray<FVector2D>(), TArray<FVector2D>(), TArray<FVector2D>(), vertexColors, tangents, false);
			PMeshArray.Add(newPComp);
			
		}
	}
}