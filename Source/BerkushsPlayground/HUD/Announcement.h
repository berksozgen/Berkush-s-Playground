// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Announcement.generated.h"

/**
 * 
 */
UCLASS()
class BERKUSHSPLAYGROUND_API UAnnouncement : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* WarmupTime;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* AnnouncementText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* InfoText;
	
};
