unsigned long start_mls = 0;
int timeout = 100;
bool timed_out = false;

void setup() {
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, INPUT);
  Serial.begin(9600);
}

void loop() {}

void ledctrl(String led) {
  if (led.length() >= 25) {
    timed_out = false;
    digitalWrite(A0, HIGH);
    start_mls = millis();
    while (digitalRead(A2) == LOW) {
      if (timed_out) {
        break;
      }
      if (millis() >= start_mls + timeout) {
        timed_out = true;
      }
    }
    digitalWrite(A0, LOW);
    while (digitalRead(A2) == HIGH) {
      if (timed_out) {
        break;
      }
      if (millis() >= start_mls + timeout) {
        timed_out = true;
      }
    };
    for (int i = 0; i < 25; i++) {
      if (led.charAt(i) != '0') {
        digitalWrite(A1, HIGH);
        digitalWrite(A0, HIGH);
        while (digitalRead(A2) == LOW) {
          if (timed_out) {
            break;
          }
          if (millis() >= start_mls + timeout) {
            timed_out = true;
          }
        }
        digitalWrite(A0, LOW);
        digitalWrite(A1, LOW);
        while (digitalRead(A2) == HIGH) {
          if (timed_out) {
            break;
          }
          if (millis() >= start_mls + timeout) {
            timed_out = true;
          }
        }
      } else {
        digitalWrite(A0, HIGH);
        while (digitalRead(A2) == LOW) {
          if (timed_out) {
            break;
          }
          if (millis() >= start_mls + timeout) {
            timed_out = true;
          }
        }
        digitalWrite(A0, LOW);
        while (digitalRead(A2) == HIGH) {
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
  if (digitalRead(A2) == HIGH || timed_out) {
    ledctrl(led);
  }
}
