// Building Escape Project by Manoj

#include "CollisionQueryParams.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogTemp, Warning, TEXT("Grabber Reporting for Duty!!!"));

	//putting below code inside a func like FindPhysicsHandle()

	FindPhysicsHandle();
	
	SetupInputComponent();
}

void UGrabber::FindPhysicsHandle()
{
	//checking for physics handle component
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (PhysicsHandle)
	{
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No Physics Handle Component Found on %s"), *GetOwner()->GetName());
	}
}

void UGrabber::SetupInputComponent()
{	
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if(InputComponent)
	{
		//not required below as it always be showing the name
		//UE_LOG(LogTemp, Warning, TEXT("Input Component found %s"), *GetOwner()->GetName());

		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		// i
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabber Pressed"));
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabber Release"));
}
// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// get player viewpoint
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	// draw a line from player showing the reach
	FVector LineTraceDirection = PlayerViewPointRotation.Vector();

	FVector LineTraceEnd = PlayerViewPointLocation + (LineTraceDirection * Reach);

	//draw debug line
	DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor(0, 0, 255),
		false,
		0.f,
		0,
		5.f);

	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	// Ray cast out to certain distance (Reach)
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams);

	//logging out to test

	AActor *ActorThatGotHit = Hit.GetActor();

	if (ActorThatGotHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Line Trace has hit %s"), *(ActorThatGotHit->GetName()));
	}

	//UE_LOG(LogTemp, Warning, TEXT("Pawn's Current Location : %s Current Direction : %s"), *PlayerViewPointRotation.ToString(), *PlayerViewPointRotation.ToString());
}
