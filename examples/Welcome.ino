void welcomeScreen(){
	display.clearDisplay();
	display.setTextSize(1);
	display.setTextColor(BLACK);
	display.setCursor(0,0);
	display.println("Sprinkler v1.0");
	display.println("");
	display.println("Powered by");
	display.println("       Arduino");
	display.display();
}
