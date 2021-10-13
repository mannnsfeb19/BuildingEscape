// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldPosition.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UWorldPosition::UWorldPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWorldPosition::BeginPlay()
{
	Super::BeginPlay();
	
	// FString Log = TEXT("Hello!!!");
	// FString* PtrLog = &Log;

	// Log.Len();

	// (*PtrLog).Len();	// . has precedence over * so put in brackets
	// PtrLog->Len();


	// //UE_LOG(LogTemp, Warning, TEXT("%s"), *Log); // here *Log is an overloaded operator
	// UE_LOG(LogTemp, Warning, TEXT("%s"), **PtrLog);

	//UE_LOG(LogTemp, Warning, TEXT("Object Name is : %s"), *ObjectName);


	FString ObjectName = GetOwner()->GetName();
		
	FString ObjectPosition = GetOwner()->GetActorLocation().ToString();
	UE_LOG(LogTemp, Warning, TEXT("%s Position is : %s"), *ObjectName, *ObjectPosition);
	
	//or 

	// FString ObjectPosition = GetOwner()->GetActorTransform().GetLocation().ToString();

	// UE_LOG(LogTemp, Warning, TEXT("%s Position is : %s"), *ObjectName, *ObjectPosition);
	
}



// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

