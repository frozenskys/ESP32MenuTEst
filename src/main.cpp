#include <heltec.h>
#include<IoAbstraction.h>

#include <images.h>

const int spinwheelClickPin = 26;
const int encoderAPin = 14;
const int encoderBPin = 27;
const int maximumEncoderValue = 128;

int16_t encValue;

void logo(){
	Heltec.display -> clear();
	Heltec.display -> drawXbm(0,0,logo_width,logo_height,(const unsigned char *)logo_bits);
	Heltec.display -> display();
}

void onSpinwheelClicked(pinid_t pin, bool heldDown) {
  Serial.print("Button pressed ");
  Serial.println(heldDown ? "Held" : "Pressed");
}

void onEncoderChange(int newValue) {
  Serial.print("Encoder change ");
  Serial.println(newValue);
  encValue = newValue;
}

void setup()
{
	Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Enable*/, false /*Serial Enable*/);
	Serial.begin(115200);
	Serial.println("Setup Started");

	logo();
	delay(3000);
	
	switches.initialise(ioUsingArduino(), true);
	switches.addSwitch(spinwheelClickPin, onSpinwheelClicked);
	setupRotaryEncoderWithInterrupt(encoderAPin, encoderBPin, onEncoderChange);
	switches.changeEncoderPrecision(maximumEncoderValue, 100);

	Serial.println("Encoder Started...");
	Heltec.display->clear();
	Heltec.display -> display();
	Serial.println("Setup Finished");
}

void updateMenu()
{
  char data[20];
	sprintf(data, "Value %d", encValue);
	Heltec.display -> setColor(BLACK);
	Heltec.display -> fillRect(0,37,128,9);
	Heltec.display -> setColor(WHITE);
	Heltec.display -> drawString(2, 36, data);
	Heltec.display -> display();
}

void loop()
{
  taskManager.runLoop();
  updateMenu();
}