// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"

// Sets default values
AMyActor::AMyActor()
	: MoveCount(0), EventCount(0), TotalMoveDistance(0), CurrentTargetDistance(0)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();

	// 액터의 게임 시작 위치는 (0, 50, 0)으로 고정
	StartLocation = FVector(0, 50, 0);
	SetActorLocation(StartLocation);

	// TargetLocation 설정을 위한 이벤트 함수 호출
	ChoiceRandomDirection();
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 매 프레임 갱신
	RotatingActor(DeltaTime);
	MovingActor(DeltaTime);
}

// 액터의 현재 위치(CurrentLocation)를 MoveVelocity * DeltaTime 만큼 갱신
// StartLocation을 기준으로 CurrentLocation와의 거리 계산
// 현재 이동 거리(CurrentMoveDistance)가 CurrentTargetDistance를 초과할 시, 
//		액터는 TargetLocation으로 위치 보정
//		TotalMoveDistance 갱신
//		MoveCount 추가 후, 이벤트 발생 및 다음 이동을 위한 변수 값 갱신
//		MovceCount == 10이면,
//			총 이동 거리 및 이벤트 발생 횟수 화면에 출력
void AMyActor::MovingActor(float DeltaTime)
{
	if (MoveCount >= 10)
		return;

	FVector CurrentLocation = GetActorLocation();

	CurrentLocation += MoveVelocity * DeltaTime;
	SetActorLocation(CurrentLocation);

	CurrentMoveDistance = FVector::Dist(StartLocation, CurrentLocation);
	if (CurrentMoveDistance > CurrentTargetDistance)
	{
		SetActorLocation(TargetLocation);

		TotalMoveDistance += CurrentTargetDistance;

		++MoveCount;

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, 
			FString::Printf(TEXT("%d Current Location: %s"), MoveCount, *TargetLocation.ToString()));
	
		StartLocation = TargetLocation;

		if (MoveCount == 10)
		{
			GEngine->AddOnScreenDebugMessage
			(
				-1, 10.0f, FColor::Yellow,
				FString::Printf(TEXT("Total Move Distance : %.2f"), TotalMoveDistance)
			);

			GEngine->AddOnScreenDebugMessage
			(
				-1, 10.0f, FColor::Green,
				FString::Printf(TEXT("Event Count : %d"), EventCount)
			);
		}

		if (MoveCount >= 10)
			return;

		ChoiceRandomDirection();
	}
}

// 회전 속도에 DeltaTime을 곱하여,
// 프레임 속도와 관계 없이 동일한 회전 속도를 유지하며 회전
void AMyActor::RotatingActor(float DeltaTime)
{
	AddActorLocalRotation(RotationVelocity * DeltaTime);
}

// 매 이동 시작 시, 50% 확률로 6가지 방향(MoveDirection) 중 하나 선택
// 이동 속도(RandomSpeed)를 랜덤으로 설정하여 MoveVelocity 갱신 
// 목표 이동 거리(CurrentTargetDistance) 랜덤 설정 및 TargetLocation 갱신
void AMyActor::ChoiceRandomDirection()
{
	if (FMath::FRand() <= 0.5f)
	{
		float RandomValue = FMath::FRand();

		FVector MoveDirection = FVector::ZeroVector;

		if (RandomValue < 1.0f / 3.0f)
		{
			MoveDirection.X = 1;
		}
		else if (RandomValue < 2.0f / 3.0f)
		{
			MoveDirection.Y = 1;
		}
		else
		{
			MoveDirection.Z = 1;
		}

		float RandomSign = FMath::FRand();
		if (RandomSign < 0.5f)
		{
			MoveDirection *= -1;
		}

		float RandomSpeed = FMath::RandRange(100.0f, 300.0f);
		MoveVelocity = MoveDirection * RandomSpeed;

		++EventCount;
	}

	CurrentTargetDistance = FMath::RandRange(500.0f, 1000.0f);
	TargetLocation = StartLocation + MoveVelocity.GetSafeNormal() * CurrentTargetDistance;
}

