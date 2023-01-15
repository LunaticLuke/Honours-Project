// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


UENUM()
enum class EGrabType : uint8
{
	None  UMETA(DisplayName = "None"),
	Free UMETA(DisplayName = "Free"),
	Snap UMETA(DisplayName = "Snap"),
	Custom UMETA(DisplayName = "Custom")
};

UENUM()
enum class NodeDataTypes:uint8
{
	Int  UMETA(DisplayName = "Int"),
	Float UMETA(DisplayName = "Float"),
	Bool UMETA(DisplayName = "Bool"),
	String UMETA(DisplayName = "String"),
	Char UMETA(DisplayName = "Char"),
	Unassigned UMETA(DisplayName = "Unassigned")
};


/**
 * 
 */
class HONOURSPROJECT_API EnumManager
{
public:
	EnumManager();
	~EnumManager();
	static FString ConvertDataTypeToString(NodeDataTypes DataTypeToConvert)
	{
		switch (DataTypeToConvert)
		{
		case NodeDataTypes::Bool:
			return "bool";
			break;
		case NodeDataTypes::Char:
			return "char";
			break;
		case NodeDataTypes::Float:
			return "float";
			break;
		case NodeDataTypes::Int:
			return "int";
			break;
		case NodeDataTypes::String:
			return "string";
			break;
		case NodeDataTypes::Unassigned:
			return "No Data Type";
			break;
		default:
			return "Error";
			break;
		}
		
	}


	
};
