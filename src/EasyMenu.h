// Interface for the EasyMenu.
//
// Copyright (c) 2019, LeoCode
// All rights reserved.
//
// Distributed under the 2-clause BSD license.
#ifndef EASYMENU_H_
#define EASYMENU_H_

typedef struct oneMenu {
	byte id;                  // Идентификатор пункта
	byte parent;              // Идентификатор родительского пункта
	char nameMenu[MAXLENGTH]; // Название пункта меню
	uint8_t actionID;         // Action ID свойство, то что должно произойти на нажатии на пункт меню
	char param[MAXLENGTH];    // Параметр меню, для каталога - это шапка каталога, его название
} oneMenu;

class Menu {
public:
	bool acivity;
	void verify();
	Menu(uint8_t PIN1, uint8_t PIN2, uint8_t TIMEOUT, unit8_t DX, uint8_t DY);
	~Menu();
		
private:
	uint8_t PIN1;			// ПИН кнопки Mode
	uint8_t PIN2;			// ПИН кнопки Action
	uint8_t TIMEOUT;		// Таймоут Меню
	uint8_t DISP_X;			// Размер дисплея в символах по ширине
	uint8_t DISP_Y;			// Размер дисплея в символах по высоте
	
	long 	timeMenu;		// Время сработки меню
	uint8_t curMenuPos; 	// Позиция в меню
	int     curMenuID;   	// -1 - Меню не отобржается, 0 - 0-ая ячейка массива menu и т.д.
	int     viewMenuID;		// Подсвеченный пункт меню
	
	void modeMenu();
	void actionMenu(int viewID);
	void checkTimeMenu();
	int  getMenuPos(byte idMenu);
};

#endif  // EASYMENU_H_