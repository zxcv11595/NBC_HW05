// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

// 총 10회 이동 및 회전하는 액터
// 일정 확률로 속도, 방향, 이동 거리가 랜덤으로 결정
// 10회 이동 후, 총 이동 거리와 이벤트 발생 횟수를 화면에 출력
UCLASS()
class NBC_HW05_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	// 매 프레임 액터를 TragetLocation 방향으로 이동
	void MovingActor(float DeltaTime);
	// 매 프레임 회전
	void RotatingActor(float DeltaTime);
	// 랜덤 방향과 속도를 설정하여 다음 이동을 위한 TargetLocation 갱신
	void ChoiceRandomDirection();

private:
	FVector StartLocation;		// 현재 이동 구간의 시작 위치
	FVector TargetLocation;		// 현재 이동 구간의 목표 위치

	UPROPERTY(EditAnywhere)
	FVector MoveVelocity;		

	UPROPERTY(VisibleAnywhere)
	float CurrentMoveDistance;

	UPROPERTY(EditAnywhere)
	FRotator RotationVelocity;	

	int32 MoveCount;				// 총 10회 랜덤 위치로, 이동 횟수를 카운트하기 위한 변수
	int32 EventCount;				// ChoiceRandomDirection() 이벤트 발생 횟수

	float TotalMoveDistance;		// 총 이동거리
	float CurrentTargetDistance;	// 현재 이동 구간의 목표 이동 거리
};
