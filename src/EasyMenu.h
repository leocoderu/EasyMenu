// Interface for the EasyMenu.
//
// Copyright (c) 2019, LeoCode
// All rights reserved.
//
// Distributed under the 3-clause BSD license.
#ifndef EASYMENU_H_
#define EASYMENU_H_

#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

typedef struct oneMenu {
	uint8_t id;                 // Идентификатор пункта
	uint8_t parent;             // Идентификатор родительского пункта
	char    nameMenu[15]; 		// Название пункта меню
	uint8_t actionID;           // Action ID свойство, то что должно произойти на нажатии на пункт меню
	char    param[15];    		// Параметр меню, для каталога - это шапка каталога, его название
	bool    visible;			// Виден пункт меню в списке или нет
} oneMenu;

class Menu {
	public:
		bool activity;
		Menu(Adafruit_PCD8544* display, uint8_t TIMEOUT, uint8_t DISP_X, uint8_t DISP_Y);
		~Menu();
		oneMenu menu[]; 
  	
		void getMenu();
		
	private:
		uint8_t _TIMEOUT;			// Таймоут Меню
		uint8_t _DISP_X;			// Размер дисплея в символах по ширине
		uint8_t	_DISP_Y;			// Размер дисплея в символах по высоте
	
		long 	_timeMenu;			// Время сработки меню
		uint8_t _curMenuPos = 0; 	// Позиция в меню
		int     _curMenuID  = -1;	// -1 - Меню не отобржается, 0 - 0-ая ячейка массива menu и т.д.
		int     _viewMenuID = -1;	// Подсвеченный пункт меню
		
		Adafruit_PCD8544* _display; // 
		
		void printMenu(int id);
};

#endif //EASYMENU_H_