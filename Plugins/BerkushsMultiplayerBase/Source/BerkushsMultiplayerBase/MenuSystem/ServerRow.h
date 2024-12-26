// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ServerRow.generated.h"

/**
 * 
 */
UCLASS()
class BERKUSHSMULTIPLAYERBASE_API UServerRow : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* ServerName;
	
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* HostUser;

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* ConnectionFraction;

	UPROPERTY(BlueprintReadOnly, Category = "Berkush's Multiplayer Base")
	bool bIsSelected = false;
	
	void Setup(class UMainMenu* Parent, uint32 Index);

private:
	UPROPERTY(meta=(BindWidget))
	class UButton* RowButton;

	UPROPERTY()
	class UMainMenu *Parent;

	uint32 Index;

	UFUNCTION()
	void OnClicked();
	
};
