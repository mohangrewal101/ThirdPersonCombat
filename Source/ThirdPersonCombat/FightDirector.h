// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "EnemyAICharacter.h"
#include "FightDirector.generated.h"

UCLASS()
class THIRDPERSONCOMBAT_API AFightDirector : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFightDirector();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void UpdateDebugWidgets(AEnemyAICharacter* EnemyInstance);

private:

	UFUNCTION()
	void ScoreByPosition();

	UFUNCTION()
	void ScoreByAttack();

	UFUNCTION(BlueprintCallable)
	void RecalculateScores();

	UFUNCTION(BlueprintCallable)
	AEnemyAICharacter* FindHighestGrade();

	UFUNCTION(BlueprintCallable)
	void IncrementAttackWait(AEnemyAICharacter* AttackingEnemy);

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AEnemyAICharacter*> EnemyList;

	UPROPERTY(BlueprintReadOnly)
	TMap<AEnemyAICharacter*, float> EnemyGrading;

	UPROPERTY(BlueprintReadOnly)
	TMap<AEnemyAICharacter*, float> EnemyAttackWait;

};
