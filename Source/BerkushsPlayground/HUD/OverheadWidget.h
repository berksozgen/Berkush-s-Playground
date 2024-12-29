// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OverheadWidget.generated.h"

/**
 * 
 */
UCLASS()
class BERKUSHSPLAYGROUND_API UOverheadWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* DisplayText;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* NicknameText;

	void SetDisplayText(FString TextToDisplay);
	void SetNicknameText(FString TextToDisplay);
	UFUNCTION(BlueprintCallable)
	void ShowPlayerNetRole(APawn* InPawn);
	UFUNCTION(BlueprintCallable)
	void ShowPlayerNickname(APawn* InPawn);
protected:
	virtual void NativeDestruct() override;
};
