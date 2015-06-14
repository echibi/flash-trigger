#define BUTTON_PIN 5
#define FLASH_TRIGGER_PIN 12
#define SENSOR_PIN A0
#define LED_PIN 13
#define STANDBY 0
#define ACTIVE 1
#define SENSOR_THRESHOLD 1

int mode = STANDBY;

// How long should the flash wait before it fires when sensor has detected something.
long flashDelayMS = 110; 

void setup() {
  Serial.begin(9600);
	pinMode(BUTTON_PIN, INPUT);
	pinMode(FLASH_TRIGGER_PIN, OUTPUT);
	pinMode(LED_PIN, OUTPUT);
	digitalWrite(LED_PIN, HIGH); 
}


void loop() {
    Serial.println(analogRead(SENSOR_PIN));
	if (digitalRead(BUTTON_PIN) == HIGH)  
	{
		mode = ACTIVE;
		digitalWrite(LED_PIN, LOW); // Flash is ready ( disable the led )
	}
	if ((mode == ACTIVE) && (analogRead(SENSOR_PIN) > SENSOR_THRESHOLD)) //
	{ // We are in active mode and sensor is picking up something.
		delay(flashDelayMS);
		digitalWrite(FLASH_TRIGGER_PIN, HIGH); // Flash
		delay(50);
		digitalWrite(FLASH_TRIGGER_PIN, LOW);
		mode = STANDBY; // Go back to standby mode.
		digitalWrite(LED_PIN, HIGH); 
	}
}
