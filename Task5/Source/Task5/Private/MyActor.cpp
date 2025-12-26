// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "Engine/Engine.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AMyActor::RepeatFunctions, 3.0f, true);
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyActor::PrintCurrentLocation()
{
	FVector ActorLocation = GetActorLocation();
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, FString::Printf(TEXT("Actor : %s"), *GetName()));
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, ActorLocation.ToString());
	}
}

void AMyActor::Turn()
{
	float RValue1, RValue2, RValue3;
	FRotator newRot = GetActorRotation();

	RValue1 = FMath::RandRange(-.0f, 90.0f);
	RValue2 = FMath::RandRange(1.0f, 90.0f);
	RValue3 = FMath::RandRange(1.0f, 90.0f);
	
	newRot.Add(RValue1, RValue2, RValue3);

	SetActorRotation(newRot);
}

void AMyActor::Move()
{
	int32 RValue1, RValue2, RValue3;
	FVector newLoc = GetActorLocation();

	RValue1 = FMath::RandRange(-100, 100);
	RValue2 = FMath::RandRange(-100, 100);
	RValue3 = FMath::RandRange(-100, 100);

	newLoc += FVector(RValue1, RValue2, RValue3);

	SetActorLocation(newLoc);
}

void AMyActor::RepeatFunctions()
{
	Count++;
	Turn();
	Move();
	PrintCurrentLocation();

	if (Count >= 10)
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("Repeat End"));
	}
}