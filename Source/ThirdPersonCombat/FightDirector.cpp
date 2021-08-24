// Fill out your copyright notice in the Description page of Project Settings.


#include "FightDirector.h"

// Sets default values
AFightDirector::AFightDirector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFightDirector::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFightDirector::ScoreByPosition()
{
	for (auto& Enemy : EnemyList) {
		//Depends on direction camera is facing
		float EnemyPositionToPlayer = FVector::DotProduct(Enemy->GetActorForwardVector(), 
			UKismetMathLibrary::GetForwardVector(UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraRotation())) * -1.0;
		//Depends on direction player is facing (In BP GetPlayerCharacter->GetActorForwardVector)

		float NewFightingGrade = *EnemyGrading.Find(Enemy) * 
			(UKismetMathLibrary::NormalizeToRange(EnemyPositionToPlayer, 1.0f, 5.0f) + 0.5f);
		EnemyGrading.Add(Enemy, NewFightingGrade);
	}
}

void AFightDirector::ScoreByAttack()
{
	for (auto& Enemy : EnemyList) {
		if (!EnemyAttackWait.Contains(Enemy)) EnemyAttackWait.Add(Enemy, 0.0f);
		EnemyGrading.Add(Enemy, *EnemyGrading.Find(Enemy) + *EnemyAttackWait.Find(Enemy));
		AFightDirector::UpdateDebugWidgets(Enemy);
	}
}

void AFightDirector::RecalculateScores()
{
	ScoreByPosition();
	ScoreByAttack();
}

AEnemyAICharacter* AFightDirector::FindHighestGrade()
{
	float HighestValue = 0;
	AEnemyAICharacter* HighestGradeAI = NULL;
	for(auto& GradingPair : EnemyGrading) {
		if (GradingPair.Value > HighestValue) {
			HighestValue = GradingPair.Value;
			HighestGradeAI = GradingPair.Key;
		}
	}
	return HighestGradeAI;
}

void AFightDirector::IncrementAttackWait(AEnemyAICharacter* AttackingEnemy)
{
	for (auto& Enemy : EnemyList) {
		if (Enemy != AttackingEnemy)
			EnemyAttackWait.Add(Enemy, *EnemyAttackWait.Find(Enemy) + FMath::RandRange(0.0f, 1.0f));
		else EnemyAttackWait.Add(Enemy, 0.0f);
	}
}

