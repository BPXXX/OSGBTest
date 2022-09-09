// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"
#include "HAL/FileManagerGeneric.h"
#include <osgDB/ReadFile>
#include <osg/Geometry>
#include <osgDB/WriteFile>
#include<osgDB/ReaderWriter>
#include <osg/Geode> 
#include <osg/Geometry>
#include <osg/Drawable>
#include <osg/Node>
#include <osg/NodeVisitor>
class FOSGBLibraryModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	virtual void testtest();
};
