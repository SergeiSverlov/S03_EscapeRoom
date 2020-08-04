// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorOpen.h"
#include "Grabber.h"

// Sets default values for this component's properties
UDoorOpen::UDoorOpen()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorOpen::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();

	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing PressurePlate"), *(GetOwner()->GetName()))
	}
}

void UDoorOpen::OpenDoor()
{
	// Owner->SetActorRotation(FRotator(0.f, OpenAngle, 0.f));
	OnOpenRequest.Broadcast();
}


// Called every frame
void UDoorOpen::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the Trigger Volume every frame
	if (GetTotalMassOfActorsOnPlate() > 30.f) // TODO make into a parametre
	{
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	// Check if it is time to close the door
	if (GetWorld()->GetTimeSeconds()- LastDoorOpenTime > DoorCloseDelay)
	{
		CloseDoor();
	}
}

void UDoorOpen::CloseDoor ()
{
	Owner->SetActorRotation(FRotator(0.f, 90.f, 0.f));
}

float UDoorOpen::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.f;

	// find all the overlaping actors
	TArray<AActor*> OverlappingActors;
	if (!PressurePlate) { return TotalMass; }
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	// itterate through them adding their masses
	for (auto* Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("%s on pressure plate"), *Actor->GetName());
	}

	return TotalMass;
}