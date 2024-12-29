// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.


#include "OverheadWidget.h"

#include "Components/TextBlock.h"
#include "GameFramework/PlayerState.h"

void UOverheadWidget::SetDisplayText(FString TextToDisplay)
{
	if (DisplayText)
	{
		DisplayText->SetText(FText::FromString(TextToDisplay));
	}
}

void UOverheadWidget::SetNicknameText(FString TextToDisplay)
{
	if (NicknameText)
	{
		NicknameText->SetText(FText::FromString(TextToDisplay));
	}
}

void UOverheadWidget::ShowPlayerNetRole(APawn* InPawn)
{
	ENetRole LocalRole = InPawn->GetLocalRole();
	ENetRole RemoteRole = InPawn->GetRemoteRole();
	FString LocalRoleString;
	FString RemoteRoleString;
	switch (LocalRole)
	{
	case ENetRole::ROLE_Authority: LocalRoleString = FString("Authority"); break;
	case ENetRole::ROLE_AutonomousProxy: LocalRoleString = FString("AutonomousProxy"); break;
	case ENetRole::ROLE_SimulatedProxy: LocalRoleString = FString("SimulatedProxy"); break;
	default: LocalRoleString = FString("Error!"); break;
	}
	switch (RemoteRole)
	{
	case ENetRole::ROLE_Authority: RemoteRoleString = FString("Authority"); break;
	case ENetRole::ROLE_AutonomousProxy: RemoteRoleString = FString("AutonomousProxy"); break;
	case ENetRole::ROLE_SimulatedProxy: RemoteRoleString = FString("SimulatedProxy"); break;
	default: RemoteRoleString = FString("Error!"); break;
	}
	
	FString Roles = FString::Printf(TEXT("Local: %s & Remote: %s"), *LocalRoleString, *RemoteRoleString);
	SetDisplayText(Roles);
}

void UOverheadWidget::ShowPlayerNickname(APawn* InPawn)
{
	if(auto ps = InPawn->GetPlayerState())
	{
		SetNicknameText(ps->GetPlayerName());
	}
}

void UOverheadWidget::NativeDestruct()
{
	RemoveFromParent();
	
	Super::NativeDestruct();
}
