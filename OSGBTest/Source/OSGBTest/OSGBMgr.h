// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <vector>
#include <osgDB/ReadFile>
#include <osg/Geometry>
#include <osgDB/WriteFile>
#include<osgDB/ReaderWriter>
#include <osg/Geode> 
#include <osg/Geometry>
#include <osg/Drawable>
#include <osg/Node>
#include <osg/NodeVisitor>
#include <osg/TriangleIndexFunctor>
#include <osg/TriangleFunctor>

#include "OSGBGridHolder.h"
#include "OSGBMgr.generated.h"
class OSGAttributeVisiter :public osg::Drawable::AttributeFunctor
{

public:
	TArray<FVector> vertexArray;
	TArray<FVector> normalArray;
	TArray<FVector2D> textCoordArray;
	virtual void apply(osg::Drawable::AttributeType, unsigned, osg::Vec2*) override;
	virtual void apply(osg::Drawable::AttributeType, unsigned, osg::Vec3*) override;
};

class TriangleIndex
{
public:
	//osg::ref_ptr<osg::UIntArray> indexs;
	TArray<int> triangleIndexes;
	int triangleNum;
	TriangleIndex(){};
	~TriangleIndex(){};
	void operator()(const unsigned int& v1, const unsigned int& v2, const unsigned int& v3);
};
class OSGGeom
{

public:
	TArray<FVector> vertexArray;
	TArray<FVector> normalArray;
	TArray<FVector2D> textCoordArray;
	TArray<int> triangleArray;
public:
	OSGGeom()
	{
		vertexArray = TArray<FVector>();
		normalArray = TArray<FVector>();
		textCoordArray = TArray<FVector2D>();
		triangleArray = TArray<int>();
	}
};
class  OSGNodeVisiter :public osg::NodeVisitor
{
public:
	TArray<OSGGeom*> NodeGeoms;
public:
	virtual  void apply(osg::Geode& node) override;
	OSGNodeVisiter()
	{
		setTraversalMode(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN);
		NodeGeoms = TArray<OSGGeom*>();
	}
};
UCLASS()
class OSGBTEST_API AOSGBMgr : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOSGBMgr();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void DrawOSGBMap(FString mapName);
};
