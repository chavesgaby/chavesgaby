#include "config.h"
#include <ESP32Servo.h>
Servo myservo;
ESP32PWM pwm;
/************************ Example Starts Here *******************************/

// this int will hold the current count for our sketch
int count = 0;
float temp = 0;
float tempC = 0;
int f=0;
int valdiz = 0;
int valuni = 0;
int valdec = 0;
int grado = 0;
// set up the 'counter' feed
AdafruitIO_Feed *Temp = io.feed("Temp");
AdafruitIO_Feed *Reloj = io.feed("Reloj");

void setup() {
  Serial.begin(9600);
  // start the serial connection
  // wait for serial monitor to open
  while (! Serial);

  Serial.print("Connecting to Adafruit IO");

  // connect to io.adafruit.com
  io.connect();

  // wait for a connection
  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());

  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(27, OUTPUT);//a
  pinMode(26, OUTPUT);//b
  pinMode(25, OUTPUT);//c
  pinMode(33, OUTPUT);//d
  pinMode(32, OUTPUT);//e
  pinMode(5, OUTPUT);//f
  pinMode(19, OUTPUT);//dot
  pinMode(18, OUTPUT);//g
  pinMode(21, OUTPUT);
  pinMode(22, OUTPUT);
  pinMode(23, OUTPUT);
  pinMode(34, INPUT_PULLUP);
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  myservo.setPeriodHertz(50);// Standard 50hz servo
  io.run();
  myservo.attach(2, 500, 2400);
  pwm.attachPin(4, 10000);
  myservo.write(0);
  delay(100);
  myservo.detach();
  pwm.detachPin(4);
}

void loop() {
  if (digitalRead(34) == LOW) {
    while (f == 0) {
      if (digitalRead(34) == HIGH) {
        f = 1;
      }
    }
    f = 0;
    int temp;
    temp = ((1.611328125) * analogRead(35)) / 10;
    valdiz = int(temp / 10);
    valuni = int(temp - valdiz * 10);
    valdec = (temp * 10) - (int(temp) * 10);
    myservo.attach(2, 500, 2400);
    pwm.attachPin(4, 10000);
    if (temp < 37) {
      digitalWrite(13, HIGH);
      digitalWrite(12, LOW);
      digitalWrite(14, LOW);
      Reloj->save(0);
      if (grado == 0) {
        grado = 0;
      }
      else if (grado == 90) {
        for (int i = 90; i >= 0; i -= 45) {
          myservo.attach(2, 500, 2400);
          pwm.attachPin(4, 10000);
          myservo.write(i);
          delay(100);
          myservo.detach();
          pwm.detachPin(4);
          grado = 0;
        }

      }
      else if (grado == 180) {
        for (int i = 180; i >= 0; i -= 45) {
          myservo.attach(2, 500, 2400);
          pwm.attachPin(4, 10000);
          myservo.write(i);
          delay(100);
          myservo.detach();
          pwm.detachPin(4);
          grado = 0;
        }

      }

    }
    else if (temp > 37 && temp < 37.5) {
      digitalWrite(13, LOW);
      digitalWrite(12, HIGH);
      digitalWrite(14, LOW);

      if (grado == 0) {
        for (int i = 0; i <= 90; i += 45) {
          myservo.attach(2, 500, 2400);
          pwm.attachPin(4, 10000);
          myservo.write(i);
          delay(100);
          myservo.detach();
          pwm.detachPin(4);
        }
      }
      else if (grado == 180) {
        for (int i = 180; i <= 90; i -= 45) {
          myservo.attach(2, 500, 2400);
          pwm.attachPin(4, 10000);
          myservo.write(i);
          delay(100);
          myservo.detach();
          pwm.detachPin(4);
        }
      }
      else {
        grado = 90;
      }
      grado = 90;
      Reloj->save(90);

    }
    else if (temp > 37.5) {
      digitalWrite(13, LOW);
      digitalWrite(12, LOW);
      digitalWrite(14, HIGH);

      if (grado == 0) {
        for (int i = 0; i <= 180; i += 45) {
          myservo.attach(2, 500, 2400);
          pwm.attachPin(4, 10000);
          myservo.write(i);
          delay(100);
          myservo.detach();
          pwm.detachPin(4);
        }
      }
      else if (grado == 90) {
        for (int i = 90; i <= 180; i += 45) {
          myservo.attach(2, 500, 2400);
          pwm.attachPin(4, 10000);
          myservo.write(i);
          delay(100);
          myservo.detach();
          pwm.detachPin(4);
        }
      }
      else {
        grado = 180;
      }
      grado = 180;
      Reloj->save(180);
    }
    Temp->save(temp);

    // increment the count by 1
    count++;

    // Adafruit IO is rate limited for publishing, so a delay is required in
    // between feed->save events. In this example, we will wait three seconds
    // (1000 milliseconds == 1 second) during each loop.
    delay(10);

  }
  for (int i = 21; i <= 23; i++) {
    //Muestra unidades
    digitalWrite(19, HIGH);
    if (i == 23) {
      numeros(valdec);
    }
    else if (i == 21) {
      numeros(valdiz);
    }
    else if (i == 22) {
      numeros(valuni);
    }
    digitalWrite(i, HIGH);
    delay(10);
    digitalWrite(i, LOW);
  }


}
void numeros(int valor) {
  if (valor == 0) {
    digitalWrite(27, HIGH);
    digitalWrite(26, HIGH);
    digitalWrite(25, HIGH);
    digitalWrite(33, HIGH);
    digitalWrite(32, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(18, LOW);
  }
  else if ( valor == 1) {
    digitalWrite(26, HIGH);
    digitalWrite(25, HIGH);
    digitalWrite(27, LOW);
    digitalWrite(33, LOW);
    digitalWrite(32, LOW);
    digitalWrite(5, LOW);
    digitalWrite(18, LOW);
  }
  else if (valor == 2) {
    digitalWrite(27, HIGH);
    digitalWrite(26, HIGH);
    digitalWrite(25, LOW);
    digitalWrite(33, HIGH);
    digitalWrite(32, HIGH);
    digitalWrite(5, LOW);
    digitalWrite(18, HIGH);
  }
  else if (valor == 3) {
    digitalWrite(27, HIGH);
    digitalWrite(26, HIGH);
    digitalWrite(25, HIGH);
    digitalWrite(33, HIGH);
    digitalWrite(32, LOW);
    digitalWrite(5, LOW);
    digitalWrite(18, HIGH);
  }
  else if (valor == 4) {
    digitalWrite(27, LOW);
    digitalWrite(26, HIGH);
    digitalWrite(25, HIGH);
    digitalWrite(33, LOW);
    digitalWrite(32, LOW);
    digitalWrite(5, HIGH);
    digitalWrite(18, HIGH);
  }
  else if (valor == 5) {
    digitalWrite(27, HIGH);
    digitalWrite(26, LOW);
    digitalWrite(25, HIGH);
    digitalWrite(33, HIGH);
    digitalWrite(32, LOW);
    digitalWrite(5, HIGH);
    digitalWrite(18, HIGH);
  }
  else if (valor == 6) {
    digitalWrite(27, HIGH);
    digitalWrite(26, LOW);
    digitalWrite(25, HIGH);
    digitalWrite(33, HIGH);
    digitalWrite(32, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(18, HIGH);
  }
  else if (valor == 7) {
    digitalWrite(27, HIGH);
    digitalWrite(26, HIGH);
    digitalWrite(25, HIGH);
    digitalWrite(33, LOW);
    digitalWrite(32, LOW);
    digitalWrite(5, LOW);
    digitalWrite(18, LOW);
  }
  else if (valor == 8) {
    digitalWrite(27, HIGH);
    digitalWrite(26, HIGH);
    digitalWrite(25, HIGH);
    digitalWrite(33, HIGH);
    digitalWrite(32, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(18, HIGH);
  }
  else if (valor == 9) {
    digitalWrite(27, HIGH);
    digitalWrite(26, HIGH);
    digitalWrite(25, HIGH);
    digitalWrite(33, LOW);
    digitalWrite(32, LOW);
    digitalWrite(5, HIGH);
    digitalWrite(18, HIGH);

  }

}
