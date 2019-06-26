#include <Arduino.h>
#include <EasyMenu.h>

// Constructor
Menu::Menu(Adafruit_PCD8544* display, uint8_t TIMEOUT, uint8_t DISP_X, uint8_t DISP_Y)
{
	_TIMEOUT = TIMEOUT;
	_DISP_X = DISP_X;
	_DISP_Y = DISP_Y;
	//memcpy(_menu, menu, sizeof(menu));
	//for (int i=0; i < sizeof(menu)/sizeof(menu[0]); i++) {
	//	_menu[i]=menu[i];
	//}
	//Serial.println(sizeof(menu));
	//_menu = menu;
	_display = display;
}

// Destructor
Menu::~Menu()
{

}
 
/*uint8_t Menu::getAction(bool butMode, bool butAction) 
{
	uint8_t res = 0;
	
	if (butMode) modeMenu();
	

	// Проверка на бездействие в меню
	checkTimeMenu();
	return res;
}*/

/*void Menu::checkTimeMenu() {
	if (millis() - timeMenu > TIMEOUT) {
		activity = false;
		curMenuPos = 0;
		viewMenuID = -1; //-1
		curMenuID = -1;  
	} else {
		activity = true;
	}
}*/

void Menu::getMenu() { 
	_curMenuPos++;
    if (_curMenuID == -1) _curMenuID = 0;
    
	_timeMenu = millis();
	
	printMenu(_curMenuID);    
}

/*uint8_t Menu::actionMenu(int viewID) {
	uint8_t actionID;
	if (viewID == -1) {actionID = 255;}
		else {actionID = menu[viewID].actionID;};
  
	switch (actionID){
		case 0: 	curMenuID = viewMenuID;
					curMenuPos = 1; 
					printMenu(curMenuID);
					return 0;
					break;
            
		case 255:	if (curMenuID == -1) {
						// Если уровень наивысший, то включаем и отключаем свет
						return 255;
					} else {
						// Иначе производим выход на уровень меню выше
						curMenuPos = 1;
						if (menu[curMenuID].parent != 255) {
							curMenuID = getMenuPos(menu[curMenuID].parent);
							printMenu(curMenuID);
						} else {
							timeMenu = millis()-TIMEOUTMENU-1;
						}
						return 0;
					}                 
					break;
    
		default: 	Serial.println("No action for this!");
					return actionID;
					break;
	}
}
*/

/*
uint8_t Menu::getMenuPos(uint8_t idMenu){
  int result = 0;
  for (int i=0; i<(sizeof(menu)/sizeof(menu[0])); i++){
    if (menu[i].id == idMenu) {
      result = i;
      break;
    }      
  }
  
  return result;
}
*/

void Menu::printMenu(int id){    
    _display->clearDisplay();
    _display->setTextSize(1);
    _display->setTextColor(BLACK);
    _display->setCursor(0, 0);
    if (menu[_curMenuID].param != "") _display->println(menu[_curMenuID].param);

	_display->println("  Print from");
	_display->println("	  Method");
	
	for (int i=0; i < 2; i++) {
		Serial.print("Arr: ");Serial.println(menu[i].nameMenu);
	}
    // Подсчитываем кол-во элементов выборки из общего массива
/*    uint8_t qElem = 0;    
    for(int i=0; i<(sizeof(menu)/sizeof(menu[0])); i++){ if (menu[i].parent == menu[id].id) qElem++; }
   
    // Объявляем массив размером выборки +1 для пункта "< Back"
    qElem++; 
    oneMenu subArr[qElem];
    qElem = 1;
    
    // Переписываем подменю в отдельный массив
    for(int i=0; i<(sizeof(menu)/sizeof(menu[0])); i++){ 
      if (menu[i].parent == menu[id].id) {
        subArr[qElem-1] = menu[i];
        qElem++; 
      }
    }
    // Дописываем Возврат в конце подменю
    subArr[qElem-1] = (oneMenu){255, id, "< Back", 255, ""};
    
    if (curMenuPos > qElem) curMenuPos = 1; //qElem;
    
    uint8_t from = 0;             // Цикл от
    uint8_t to = from+qElem;      // Цикл до
    if (qElem > MAXROW-1) { to = from+(MAXROW-1);}
                         
    if (curMenuPos > MAXROW-1) {   
       from = curMenuPos-(MAXROW-1);
       to = from + (MAXROW-1);        
    }
    
    for(int i = from; i < to; i++){
        if ((i+1) == curMenuPos) {
          display.setTextColor(WHITE, BLACK);
          viewMenuID = getMenuPos(subArr[i].id);
        } else {
          display.setTextColor(BLACK);
        };
        display.println(subArr[i].nameMenu);
    }
*/	
    _display->display();
}