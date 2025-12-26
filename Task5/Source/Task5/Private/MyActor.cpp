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

// 액터의 현재 위치 출력
void AMyActor::PrintCurrentLocation()
{
	FVector ActorLocation = GetActorLocation();
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, FString::Printf(TEXT("Actor Location : %s"), *ActorLocation.ToString()));
	}
}

// 랜덤 값만큼 액터 회전
void AMyActor::Turn()
{
	float RValue1, RValue2, RValue3;
	FRotator newRot = GetActorRotation();

	RValue1 = FMath::RandRange(-90.0f, 90.0f);
	RValue2 = FMath::RandRange(-90.0f, 90.0f);
	RValue3 = FMath::RandRange(-90.0f, 90.0f);
	
	newRot.Add(RValue1, RValue2, RValue3);

	SetActorRotation(newRot);
}

// 랜덤 값만큼 액터 이동
void AMyActor::Move()
{
	int32 RValue1, RValue2, RValue3;
	FVector newLoc = GetActorLocation();

	RValue1 = FMath::RandRange(-100, 100);
	RValue2 = FMath::RandRange(-100, 100);
	RValue3 = FMath::RandRange(0, 100);

	newLoc += FVector(RValue1, RValue2, RValue3);
	MovedDistance += FVector::Dist(GetActorLocation(), newLoc);
	SetActorLocation(newLoc);
}

// 이벤트 함수
void AMyActor::Event()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Event Occur!"));
	EventCount++;
}

// 랜덤으로 이벤트 실행
void AMyActor::PlayEventRandom(int32 percent) {
	int RValue = FMath::RandRange(1, 100);
	if (RValue <= percent) {
		Event();
	}
}

// 반복 실행 함수
void AMyActor::RepeatFunctions()
{
	Count++;
	Turn();
	Move();
	PrintCurrentLocation();
	PlayEventRandom(50);

	if (Count >= 10)
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);

		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, FString::Printf(TEXT("Moved Distance : %f"), MovedDistance));
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, FString::Printf(TEXT("Event Occured : %d"), EventCount));
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("Repeat End"));
	}
}