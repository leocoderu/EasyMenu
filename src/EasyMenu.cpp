#include "Arduino.h"
#include <EasyMenu.h>

// Constructor
Menu:Menu(uint8_t inPIN1, uint8_t inPIN2, uint8_t inTIMEOUT, uint8_t inDX, uint8_t DY)
{
    PIN1 = inPIN1;
	PIN2 = inPIN2;
	TIMEOUT = inTIMEOUT;
	DISP_X = inDX;
	DISP_Y = inDY;
}
 
// Destructor
Menu::~Menu()
{

}

void Menu::verify() 
{
	// Нажатие на кнопку "Mode"
	bool butChanged = butMode.update();
	if (butChanged) {
		int butModeValue = butMode.read();
		if (butModeValue == HIGH) {
		modeMenu();
		}
	} 

	// Нажатие на кнопку "Action"
	bool resBut = butAction.update();
	if (resBut) {
		int resButValue = butAction.read();
		if (resButValue == HIGH) {
		actionMenu(viewMenuID);
		}
	}

	// Проверка на бездействие в меню
	checkTimeMenu();
}

void Menu::checkTimeMenu() {
	if (millis() - timeMenu > TIMEOUT) {
		activity = false;
		curMenuPos = 0;
		viewMenuID = -1; //-1
		curMenuID = -1;  
	} else {
		activity = true;
	}
}

void Menu::modeMenu() { 
	curMenuPos++;
    if (curMenuID == -1) curMenuID = 0;
    //printMenu(curMenuID);
    
    timeMenu = millis();
}

void Menu::actionMenu(int viewID) {
	byte actionID;
	if (viewID == -1) {actionID = 255;}
		else {actionID = menu[viewID].actionID;};
  
	switch (actionID){
		case 0: 	curMenuID = viewMenuID;
					curMenuPos = 1; 
					printMenu(curMenuID);
					break;
            
		case 255:	if (curMenuID == -1) {
						// Если уровень наивысший, то включаем и отключаем свет
						//runMethod("switchLigth");
					} else {
						// Иначе производим выход на уровень меню выше
						curMenuPos = 1;
						if (menu[curMenuID].parent != 255) {
							curMenuID = getMenuPos(menu[curMenuID].parent);
							printMenu(curMenuID);
						} else {
							timeMenu = millis()-TIMEOUTMENU-1;
						}
					}                 
					break;
    
		default: 	Serial.println("No action for this!");
					break;
	}
}

int Menu::getMenuPos(byte idMenu){
  int result = 0;
  for (int i=0; i<(sizeof(menu)/sizeof(menu[0])); i++){
    if (menu[i].id == idMenu) {
      result = i;
      break;
    }      
  }
  return result;
}