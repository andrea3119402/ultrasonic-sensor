/*
  Capitulo 5 de Arduino desde cero en Español
  Primer programa que envía mediante el Monitor Serial el valor de distancia
  leído por el sensor ultrasónico HC-SR04.

  Autor: bitwiseAr

*/
#include <protothreads.h> // corre dos procesos paralelos, para que un proceso no detenga al otro "delays"
#include <Servo.h>

static struct pt pt1, pt2, pt3, pt4; // declarar cada proceso

Servo myservo;
Servo myservo2;
int pos = 0;    // variable to store the servo position
int pos2 = 0;    // variable to store the servo position

//int potpin = A0;  // analog pin used to connect the potentiometer
//int val;    // variable to read the value from the analog pin


int TRIG = 6;      // trigger en pin 10
int ECO = 5;      // echo en pin 11
int LED = 4;      // LED en pin 3

int TRIG2 = 10;      // trigger en pin 10
int ECO2 = 11;      // echo en pin 11
int LED2 = 3;      // LED en pin 

int DURACION;
int DISTANCIA;

int DURACION2;
int DISTANCIA2;

void setup()
{
  pinMode(TRIG, OUTPUT);  // trigger como salida
  pinMode(ECO, INPUT);    // echo como entrada
  pinMode(LED, OUTPUT);   // LED como salida
  myservo.attach(12);  // attaches the servo on pin 9 to the servo object

  pinMode(TRIG2, OUTPUT);  // trigger como salida
  pinMode(ECO2, INPUT);    // echo como entrada
  pinMode(LED2, OUTPUT);   // LED como salida
  myservo2.attach(13);  // attaches the servo on pin 9 to the servo object

  PT_INIT(&pt1);  // initialise the two
  PT_INIT(&pt2); 
  PT_INIT(&pt3);
  PT_INIT(&pt4);   
  Serial.begin(9600);     // inicializacion de comunicacion serial a 9600 bps


}

static int protothread1(struct pt *pt) { //proceso 1, rotar el servo
  PT_BEGIN(pt);
  while (1) { // never stop
    for (pos = 0; pos <= 3; pos++) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      // delay(15);                       // waits 15 ms for the servo to reach the position
      PT_SLEEP(pt, 20); //delay, solo duerme el proceso, no todos los r
    }
    for (pos = 3; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      // delay(15);
      PT_SLEEP(pt, 20);  
    }
  }
  PT_END(pt);
}

static int protothread2(struct pt *pt) {
  PT_BEGIN(pt);
  while (1) {
    PT_SLEEP(pt, 200);
    digitalWrite(TRIG, HIGH);     // generacion del pulso a enviar
    PT_SLEEP(pt, 1);
    digitalWrite(TRIG, LOW);    // del sensor

    DURACION = pulseIn(ECO, HIGH);  // con funcion pulseIn se espera un pulso
    // alto en Echo
    DISTANCIA = DURACION / 58.2;    // distancia medida en centimetros
    Serial.println("DISTANCIA 1");    // envio de valor de distancia por monitor serial
    Serial.println(DISTANCIA);   // envio de valor de distancia por monitor serial
    // delay(200);       // demora entre datos
    PT_SLEEP(pt, 500);

  if (DISTANCIA <= 70 && DISTANCIA >= 25) {
    digitalWrite(LED, HIGH);      // enciende LED
    // delay(DISTANCIA * 10);      // demora proporcional a la distancia
    PT_SLEEP(pt, DISTANCIA * 10);

    digitalWrite(LED, LOW);     // apaga LED
  }
  }
  PT_END(pt);
}


static int protothread3(struct pt *pt) { //proceso 1, rotar el servo
  PT_BEGIN(pt);
  while (1) { // never stop
    for (pos2 = 0; pos2 <= 3; pos2++) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo2.write(pos2);              // tell servo to go to position in variable 'pos'
      // delay(15);                       // waits 15 ms for the servo to reach the position
      PT_SLEEP(pt, 20); //delay, solo duerme el proceso, no todos los r
    }
    for (pos2 = 3; pos2 >= 0; pos2 -= 1) { // goes from 180 degrees to 0 degrees
      myservo2.write(pos2);              // tell servo to go to position in variable 'pos'
      // delay(15);
      PT_SLEEP(pt, 20);  
    }
  }
  PT_END(pt);
}

static int protothread4(struct pt *pt) {
  PT_BEGIN(pt);
  while (1) {
    PT_SLEEP(pt, 200);
    digitalWrite(TRIG2, HIGH);     // generacion del pulso a enviar
    PT_SLEEP(pt, 1);
    digitalWrite(TRIG2, LOW);    // del sensor

    DURACION2 = pulseIn(ECO2, HIGH);  // con funcion pulseIn se espera un pulso
    // alto en Echo
    DISTANCIA2 = DURACION2 / 58.2;    // distancia medida en centimetros
    Serial.println("DISTANCIA 2");    // envio de valor de distancia por monitor serial
    Serial.println(DISTANCIA2);
    // delay(200);       // demora entre datos
    PT_SLEEP(pt, 500);

  if (DISTANCIA2 <= 70 && DISTANCIA2 >= 25) {
    digitalWrite(LED2, HIGH);      // enciende LED
    // delay(DISTANCIA * 10);      // demora proporcional a la distancia
    PT_SLEEP(pt, DISTANCIA2 * 10);

    digitalWrite(LED2, LOW);     // apaga LED
  }
  }
  PT_END(pt);
}


void loop()
{

  protothread1(&pt1); // llamar a cada procesp
  protothread2(&pt2); 
  protothread3(&pt3); // llamar a cada procesp
  protothread4(&pt4); 

}
