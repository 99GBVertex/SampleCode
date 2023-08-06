// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UMG/MasterWidget.h"
#include "Components/Overlay.h"
#include "Manager/UIManager.h"

TObjectPtr<UWidget> UMasterWidget::GetTypeRoot(EUIType InUIType)
{
	TObjectPtr<UWidget> OutTypeLayer = nullptr;
	switch (InUIType)
	{
	case EUIType::PAGE:			OutTypeLayer = Page;		break;
	case EUIType::POPUP:		OutTypeLayer = Popup;		break;
	case EUIType::SYSTEM_POPUP:	OutTypeLayer = SystemPopup;	break;
	case EUIType::NONE:
	default:
		break;
	}
	return OutTypeLayer;
}
