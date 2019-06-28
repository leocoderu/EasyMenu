#include <Bounce2.h>            // Для кнопки без дребезга
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#include <EasyMenu.h>

#define BUTACTION 11     // ПИН Кнопки сброса памяти 
#define BUTMODE 12       // ПИН кнопки полива

#define CONTRAST 40      // Контраст дисплея

#define MAXLENGTH 15      // Максимальная длина строки меню
#define MAXROW 6          // Максимальное количество строк меню Экран 5110 - 6 строк, но -1 это шапка, -1 это "< Back"
#define TIMEOUTMENU 7000  // Таймоут меню, после которого включается главный экран

  oneMenu menu[] {
  0,  255,  "Main  menu",     0, 1,
  1,  0,    "First",          0, 1,
  10, 1,    "Submenu First",  4, 1,
  11, 1,    "Submenu Second", 5, 1,
  2,  0,    "Second",         0, 1,
  3,  0,    "Raindrop",       2, 1,
  4,  0,    "Options",        0, 1,
  5,  4,    "Display",        0, 1,
  6,  5,    "Contrast",       0, 1,
  7,  6,    "Up",             8, 1,
  8,  6,    "Down",           9, 1,
  12, 0,    "Temp menu",      0, 1,
  13, 0,    "ZZTop menu",     0, 1,
  255,255,  "< Back",         255, 1       // Специальный пункт меню, возврата на уровень выше
};

Adafruit_PCD8544 display = Adafruit_PCD8544(9, 8, 7, 6, 5);

Menu myMenu = Menu(&display, TIMEOUTMENU, MAXLENGTH, MAXROW, menu);




Bounce butMode = Bounce(); 
Bounce butAction = Bounce(); 

// Метод запускаемый из класса
/*void switchLight() {
  // Some action
}*/

void setup() {
  butMode.attach(BUTMODE, INPUT_PULLUP);
  butMode.interval(25);
  butAction.attach(BUTACTION, INPUT_PULLUP);
  butAction.interval(25);

  Serial.begin(9600);

  display.begin();
  display.setContrast(CONTRAST);
  
  welcomeScreen();
  delay(1000);

  myMenu.activity = true;

  //myMenu.menu[14];
  //myMenu.menu[0].nameMenu = "First         ";//oneMenu menu[] {0, 255, "", 0, " \"Main  menu\"", true};
  //myMenu.menu[1].nameMenu = "Second        ";
  //myMenu.menu[1] = {1, 0, "> First", 0, " \"First menu\"", true};

 
  myMenu.getMenu();

}

void loop() {

    // Нажатие на кнопку "Mode"
    bool butChanged = butMode.update();
    if (butChanged) {
      int butModeValue = butMode.read();
      if (butModeValue == HIGH) {
        //char strTemp[] = myMenu.getMenu();
        
        //modeMenu();
      }
    }

    // Нажатие на кнопку "Action"
    bool resBut = butAction.update();
    if (resBut) {
      int resButValue = butAction.read();
      if (resButValue == HIGH) {
        //res = actionMenu(viewMenuID);
      }
    }


/*    uint8_t actID;
    actID = 0;//myMenu.getAction();
    switch (actID) {
      case 0:   // No action
        break;
      case 1:
        break;
      case 2:
        break;
      case 3:
        break;

      case 255: switchLight();
        break;
      default:
        break;
    }

    //if (!myMenu.activity) printMain();
*/
}
