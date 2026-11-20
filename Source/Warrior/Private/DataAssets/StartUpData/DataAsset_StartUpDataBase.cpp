// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"

#include "AbilitySystem/WarriorAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/WarriorGameplayAbility.h"

void UDataAsset_StartUpDataBase::GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InASCToGive,
                                                              int32 ApplyLevel)
{
	checkf(InASCToGive, TEXT("InASCToGive is null"))
	
	GrantAbility(ActivateOnGivenAbilities, InASCToGive, ApplyLevel);
	
	GrantAbility(ReactivateOnGivenAbilities, InASCToGive, ApplyLevel);
}

void UDataAsset_StartUpDataBase::GrantAbility(const TArray<TSubclassOf<UWarriorGameplayAbility>>& InAbilitiesToGive,
	UWarriorAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	if (InAbilitiesToGive.IsEmpty())
	{
		return;
	}
	
	for (auto& Ability : InAbilitiesToGive)
	{
		if (!Ability) continue;
		
		FGameplayAbilitySpec Spec(Ability);
		Spec.SourceObject = InASCToGive->GetAvatarActor();
		Spec.Level = ApplyLevel;
		
		InASCToGive->GiveAbility(Spec);
	}
	
}
