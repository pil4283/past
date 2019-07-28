#pragma once
 
#define MAX_KEYBUFF_SIZE  255

class KKeyboard
{
public:
	KKeyboard(void);
	~KKeyboard(void);	

private:
	int m_aKeyBuff[MAX_KEYBUFF_SIZE];

public:
	void OnKeyDown(int key);
	void OnKeyUp(int key);
	void Clear(void);
	int FindKey(int key);
};
