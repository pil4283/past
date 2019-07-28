#pragma once
#include "pmap.h"

#define SENTRY_COUNT 50
#define DISPENSER_COUNT 20

class PTower
{
public:
	PTower(void);
	~PTower(void);
	void TowerDraw(HDC hdc);
	int m_x;
	int m_y;
	int m_w;
	int m_h;
	bool BulletCheck(void);
	int m_rw;
	int m_rh;
	int m_rx;
	int m_ry;
	int Life;
	int Bullet;
	void Dispenser(HDC hdc);
	int d_x;
	int d_y;
	int d_w;
	int d_h;
	int d_rx;
	int d_ry;
	int d_rw;
	int d_rh;
	int DispenserLife;
	void TeleporterDraw(HDC hdc);
	void TowerIni(HINSTANCE hInst);
	HINSTANCE g_hinst;
	HBITMAP m_Origin;
	void DrawSentry(HDC hdc);
	HBITMAP p_Sentry;
	PMap m_Map;
	PEnemy m_Enemy[ENEMY_COUNT];
	int m_c;
	int exp;
	int m_Info;
	void DrawInfo(HDC hdc);
	HBITMAP m_Bullet;
	int FBullet;
	int Level;
	HBITMAP m_Upgrade;
	int Fexp;
	void TWOAttackCheck(void);
	void THRAttackCheck(void);
	int Missile;
	HBITMAP m_Missile;
	int FMissile;
	int Damage;
};
