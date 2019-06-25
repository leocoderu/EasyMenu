// Interface for the EasyMenu.
//
// Copyright (c) 2019, LeoCode
// All rights reserved.
//
// Distributed under the 3-clause BSD license.
#ifndef EASYMENU_H_
#define EASYMENU_H_

#include <Arduino.h>
#include <Bounce2.h>

typedef struct oneMenu {
	uint8_t id;                  // Идентификатор пункта
	uint8_t parent;              // Идентификатор родительского пункта
	char    nameMenu[DISP_X+1]; // Название пункта меню
	uint8_t actionID;            // Action ID свойство, то что должно произойти на нажатии на пункт меню
	char    param[DISP_X+1];    // Параметр меню, для каталога - это шапка каталога, его название
	bool    visible;			 // Виден пункт меню в списке или нет
} oneMenu;

typedef struct oneAction {
	uint8_t id;                  // Идентификатор метода
	char    nameMenu[DISP_X+1];  // Название метода который молжен быть запущен
} actionMenu;

Bounce butMode = Bounce(); // Создание объекта кнопки полива
Bounce butAction = Bounce(); // Создание объекта кнопки сброса памяти

Adafruit_PCD8544 display = Adafruit_PCD8544(9, 8, 7, 6, 5);							// <- Переменные!!!! ПИНЫ

class Menu {
public:
	bool acivity;
	void verify();
	Menu(uint8_t PIN1, uint8_t PIN2, uint8_t TIMEOUT, unit8_t DISP_X, uint8_t DISP_Y, oneMenu menu[], oneAction actions[]);
	~Menu();
		
private:
	uint8_t PIN1;			// ПИН кнопки Mode
	uint8_t PIN2;			// ПИН кнопки Action
	uint8_t TIMEOUT;		// Таймоут Меню
	uint8_t DISP_X;			// Размер дисплея в символах по ширине
	uint8_t DISP_Y;			// Размер дисплея в символах по высоте
	
	long 	   timeMenu;	// Время сработки меню
	uint8_t    curMenuPos; 	// Позиция в меню
	int        curMenuID;   // -1 - Меню не отобржается, 0 - 0-ая ячейка массива menu и т.д.
	int        viewMenuID;	// Подсвеченный пункт меню
	oneMenu    menu[];		// Структура меню
	oneAction  actions[];	// Список методов
	
	void modeMenu();
	void actionMenu(int viewID);
	void checkTimeMenu();
	int  getMenuPos(byte idMenu);
	void printMenu(int id);
	
};

#endif  // EASYMENU_H_