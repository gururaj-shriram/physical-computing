#define MODE_SWITCH_CHAR '1'

enum flashlight_state {
  ALL_OFF,
  ALL_ON,
  ALL_STROBE
};

flashlight_state mode = ALL_OFF;
char serial_data;
unsigned long prev_millis = 0;
int interval = 500; // 500 milliseconds
bool strobe_lights_on = false;

void all_off() {
  for (int x = 2; x < 8; x++) {
    digitalWrite(x, LOW);
  } 
}

void all_on() {
  for (int x = 2; x < 8; x++) {
    digitalWrite(x, HIGH);
  } 
}

void all_strobe() {
  if (millis() - prev_millis >= interval) {
    // Switch between on and off for a strobe effect
    strobe_lights_on = !strobe_lights_on;
   
    if (strobe_lights_on) {
      all_on();
    } else {
      all_off();
    }

    prev_millis = millis();
  }
}

void setup() {
  Serial.begin(9600);       
  for (int x = 2; x < 8; x++) {
    pinMode(x, OUTPUT);
  }
}

void loop() {
  if (Serial.available()) {
    // receive data from MindWave
    serial_data = Serial.read();

    if (serial_data == MODE_SWITCH_CHAR) {
      mode = mode + 1;
      // If the mode is out of bounds, restart with all off
      mode = mode > ALL_STROBE ? ALL_OFF : mode;
    }
  }

  // the value of prev_millis should stay consistent with 
  // millis unless the light is on strobe mode
  if (mode != ALL_STROBE) {
    prev_millis = millis();
  }

  switch (mode) {
    case ALL_OFF:
      all_off();
      break;
    case ALL_ON:
      all_on();
      break;
    case ALL_STROBE:
      all_strobe();
      break;
    default:
      // shouldn't reach here, but it exists as a precaution
      all_off();
      break;
  }
}
