// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SECTION_03_ESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// How far the head of the player can we reach things
	float Reach = 100.f;
	
	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	UInputComponent* InputComponent = nullptr;

	void Grab(); // Ray-cast and grab what is in Reach
	void Release(); // called when Grab released
	void SetupInputComponent(); // setup attached input component
	void FindPhysicsHandleComponent(); // find attached physics handle
	FHitResult GetFirstPhysicsBodyInReach() const; // return LineTraceHit of the first physics body in Reach
	FVector GetReachLineEnd() const; // get the end of reach line
	FVector GetReachLineStart() const;	// get the start of reach line
};
