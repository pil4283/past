#pragma once
#include "penemy.h"
#include "pmap.h"
#include "pplayer.h"
#include "ptower.h"
#include "PGameMenu.h"
#include "jmainmenu.h"
//////////////////////
//
#define ENEMY_COUNT 30
#define Player_Life 10
#define SENTRY_COUNT 50

class PGame
{
public:
	PGame(void);
	~PGame(void);
	PEnemy m_Enemy[ENEMY_COUNT];
	PMap m_Map;
	PPlayer m_Player;
	PTower m_Tower[SENTRY_COUNT];
	PTower m_Sentrygun[SENTRY_COUNT];
	PTower m_Dispenser[DISPENSER_COUNT];
	PTower m_TeleporterIN;
	PTower m_TeleporterOUT;
	PGameMenu m_GameMenu;
	JMainMenu m_MainMenu;
	HWND m_hWnd;
	void Draw(HDC hdc);
	void Ini(HWND hWnd);
	void AttackCheck(void);
	void MoveEnemy(void);
	void CheckEnemy(void);
	void CheckStageOver(void);
	void GameMenu(HDC hdc);
	void ButtonDown(WPARAM wParam, LPARAM lParam , HWND hWnd);
	void ButtonUp(WPARAM wParam, LPARAM lParam);
	void Drag(WPARAM wParam, LPARAM lParam,HWND hWnd);
	void SupplyCheck(void);
	bool SentryMap();
	bool DispenserMap(void);
	bool TeleporterINMap(void);
	bool TeleporterOUTMap(void);
	void TeleporterCheck(void);
	int stage;
	int CheckStage;
	void RButtonDown(WPARAM wParam, LPARAM lParam);
	void RButtonUp(WPARAM wParam, LPARAM lParam);
	void TWOAttackCheck(void);
	void THRAttackCheck(void);
	void MissileCheck(void);
	void TWOSupplyCheck(void);
	void THRSupplyCheck(void);
	void GameOverCheck(void);
};