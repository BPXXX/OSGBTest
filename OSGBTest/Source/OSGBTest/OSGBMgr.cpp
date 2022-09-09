// Fill out your copyright notice in the Description page of Project Settings.


#include "OSGBMgr.h"
// Sets default values
AOSGBMgr::AOSGBMgr()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AOSGBMgr::BeginPlay()
{
	Super::BeginPlay();
	DrawOSGBMap("Test");
}

// Called every frame
void AOSGBMgr::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AOSGBMgr::DrawOSGBMap(FString mapName)
{
	FString contentAbsDir = FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir());
	FString mapFolderAbsDir = contentAbsDir + "OSGBData/" + mapName + "/";
	FString filePath = FPaths::ProjectContentDir() + "OSGBData/" + mapName + "/*";
	IFileManager& fileMgr = IFileManager::Get();
	TArray<FString>files;
	fileMgr.FindFiles(files, *filePath, true, true);
	for (int i = 0; i < files.Num(); i++)
	{
		FString rawpath = mapFolderAbsDir + files[i];
		FString finalPath = rawpath.Replace(*FString("/"),*FString("\\")).Replace(*FString(".osgb"), *FString(".OSGB"));
		std::string ss = TCHAR_TO_UTF8(*finalPath);
		osg::ref_ptr<osg::Node> node = osgDB::readNodeFile(ss);
		UE_LOG(LogTemp, Warning, TEXT("finalPath %s"), *finalPath);
		OSGNodeVisiter aNodeVisiter = OSGNodeVisiter();
		node->accept(aNodeVisiter);
		if (node)
		{
			UWorld* world = GetWorld();
			FString holderName = FString("Holder");
			AOSGBGridHolder* newHolder = world->SpawnActor<AOSGBGridHolder>();
			newHolder->DrawOSGBObject(aNodeVisiter.NodeGeoms);
			UE_LOG(LogTemp, Warning, TEXT("Node Valid "));
		}
	}



}

/*	OSG*/

void OSGAttributeVisiter::apply(osg::Drawable::AttributeType type, unsigned size, osg::Vec2* front)
{
	UE_LOG(LogTemp, Warning, TEXT("OSGAttributeVisiter::applyVec2 %d"), type);
	if (type == osg::Drawable::TEXTURE_COORDS_0)
	{
		for (unsigned i = 0; i < size; i++)
		{
			osg::Vec2 vec = *(front + i);
			double X = vec._v[0];
			double Y = vec._v[1];
			textCoordArray.Add(FVector2D(X, Y));
		}
	}
}

void OSGAttributeVisiter::apply(osg::Drawable::AttributeType type, unsigned size, osg::Vec3* front)
{
	if (type == osg::Drawable::VERTICES)
	{
		for (unsigned i = 0; i < size; i++)
		{
			osg::Vec3 vec = *(front + i);
			double X = vec._v[0];
			double Y = vec._v[1];
			double Z = vec._v[2];
			vertexArray.Add(FVector(X, Y, Z));
		//	vertexList->push_back(*(front + i));
		}
	}
	else if (type == osg::Drawable::NORMALS)
	{
		for (unsigned i = 0; i < size; i++)
		{
			osg::Vec3 vec = *(front + i);
			double X = vec._v[0];
			double Y = vec._v[1];
			double Z = vec._v[2];
			normalArray.Add(FVector(X, Y, Z));
		}
	}
}
void OSGNodeVisiter:: apply(osg::Geode& node)
{
	const float multiNum = 1000;
	for (size_t i = 0; i < node.getNumDrawables(); i++)
	{
		osg::ref_ptr<osg::Drawable> drawable = node.getDrawable(i);
		OSGAttributeVisiter functor;
		drawable->accept(functor);
		osg::TriangleIndexFunctor<TriangleIndex> triangleIndex;
		drawable->accept(triangleIndex);
		OSGGeom*newGeom = new OSGGeom;
		for (FVector vValue : functor.vertexArray)
		{

			newGeom->vertexArray.Add(vValue);
		}
		for (FVector nValue : functor.normalArray)
		{
			newGeom->normalArray.Add(nValue);
		}
		for (FVector2D texValue : functor.textCoordArray)
		{
			newGeom->textCoordArray.Add(texValue);
		}
		for (int j =  triangleIndex.triangleIndexes.Num()-1;j>=0;j--)
		{
			int triValue = triangleIndex.triangleIndexes[j];
			newGeom->triangleArray.Add(triValue);
		}
		OSGGeom* newGeomptr = newGeom;
		UE_LOG(LogTemp, Warning, TEXT("OSGNodeVisiter:: apply %d %d %d %d"), newGeomptr->vertexArray.Num()
		, newGeomptr->normalArray.Num(), newGeomptr->textCoordArray.Num(), newGeomptr->triangleArray.Num());
		NodeGeoms.Add(newGeomptr);
	}
}
void TriangleIndex::operator()(const unsigned int& v1, const unsigned int& v2, const unsigned int& v3)
{
	triangleIndexes.Add(v1);
	triangleIndexes.Add(v2);
	triangleIndexes.Add(v3);
}