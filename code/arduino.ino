unsigned long start_mls = 0;
int timeout = 100; //maximum time the arduino will wait without getting confirmation from the micro:bit in ms, change if needed
bool timed_out = false;

void setup() {
  pinMode(/*PIN CONNECTED TO MICRO:BIT'S P0*/, OUTPUT);
  pinMode(/*PIN CONNECTED TO MICRO:BIT'S P1*/, OUTPUT);
  pinMode(/*PIN CONNECTED TO MICRO_BIT'S P2*/, INPUT);
  Serial.begin(9600);
}

void loop() {}

void ledctrl(String led) {
  if (led.length() >= 25) {
    timed_out = false;
    digitalWrite(/*PIN CONNECTED TO MICRO:BIT'S P0*/, HIGH);
    start_mls = millis();
    while (digitalRead(/*PIN CONNECTED TO MICRO_BIT'S P2*/) == LOW) {
      if (timed_out) {
        break;
      }
      if (millis() >= start_mls + timeout) {
        timed_out = true;
      }
    }
    digitalWrite(/*PIN CONNECTED TO MICRO:BIT'S P0*/, LOW);
    while (digitalRead(/*PIN CONNECTED TO MICRO_BIT'S P2*/) == HIGH) {
      if (timed_out) {
        break;
      }
      if (millis() >= start_mls + timeout) {
        timed_out = true;
      }
    };
    for (int i = 0; i < 25; i++) {
      if (led.charAt(i) != '0') {
        digitalWrite(/*PIN CONNECTED TO MICRO:BIT'S P1*/, HIGH);
        digitalWrite(/*PIN CONNECTED TO MICRO:BIT'S P0*/, HIGH);
        while (digitalRead(/*PIN CONNECTED TO MICRO_BIT'S P2*/) == LOW) {
          if (timed_out) {
            break;
          }
          if (millis() >= start_mls + timeout) {
            timed_out = true;
          }
        }
        digitalWrite(/*PIN CONNECTED TO MICRO:BIT'S P0*/, LOW);
        digitalWrite(/*PIN CONNECTED TO MICRO:BIT'S P1*/, LOW);
        while (digitalRead(/*PIN CONNECTED TO MICRO_BIT'S P2*/) == HIGH) {
          if (timed_out) {
            break;
          }
          if (millis() >= start_mls + timeout) {
            timed_out = true;
          }
        }
      } else {
        digitalWrite(/*PIN CONNECTED TO MICRO:BIT'S P0*/, HIGH);
        while (digitalRead(/*PIN CONNECTED TO MICRO_BIT'S P2*/) == LOW) {
          if (timed_out) {
            break;
          }
          if (millis() >= start_mls + timeout) {
            timed_out = true;
          }
        }
        digitalWrite(/*PIN CONNECTED TO MICRO:BIT'S P0*/, LOW);
        while (digitalRead(/*PIN CONNECTED TO MICRO_BIT'S P2*/) == HIGH) {
          if (timed_out) {
            break;
          }
          if (millis() >= start_mls + timeout) {
            timed_out = true;
          }
        }
      }
    }
  } else {
    timed_out = false;
  }
  if (digitalRead(/*PIN CONNECTED TO MICRO_BIT'S P2*/) == HIGH || timed_out) {
    ledctrl(led);
  }
}
