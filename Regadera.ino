//Librerias


#include <OneWire.h>
#include <DallasTemperature.h>


//Pines de sensores y actuadores
int bombaPin = 8;
int trigPin = 6;
int echoPin = 7;
int val1 = 9;
int val2 = 10;
int ledR = 11;
int ledV = 12;
int interruptor = 4;
int buzzer = 13 ;//the pin of the active buzzer

 long tiempo = millis();
  long prendido = 0;
  long sw = 0;

OneWire ourWire(5);                //Se establece el pin 2  como bus OneWire
DallasTemperature sensors(&ourWire); // sensor


void setup() {
  
  Serial.begin(9600);//iniciailzamos la comunicación

  pinMode(bombaPin, OUTPUT);
  pinMode(trigPin, OUTPUT); //pin como salida
  pinMode(echoPin, INPUT);  //pin como entrada
  digitalWrite(trigPin, LOW);//Inicializamos el pin con 0
  pinMode(val1, OUTPUT);
  pinMode(val2, OUTPUT);
  pinMode(ledR, OUTPUT);
  pinMode(ledV, OUTPUT);
  pinMode(interruptor, INPUT);
  pinMode(buzzer, OUTPUT);
  sensors.begin();   //Se inicia el sensor
  
 
}

void loop() {
  //Switch
  int encendido = digitalRead(interruptor);

  //Cuando inicia el switch
  if (encendido == 1) {
  
  if (sw ==0){
    prendido = millis();
  }
      sw = 1;


    //Inicia a medir el sensor ultrasonico
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);      //Enviamos un pulso de 10us
    digitalWrite(trigPin, LOW);

    long t; //timepo que demora en llegar el eco
    long d; //distancia en centimetros
    t = pulseIn(echoPin, HIGH); //obtenemos el ancho del pulso
    d = t / 59;
    Serial.println("Distancia: ");
    Serial.print(d);

   //Sensor de temperatura
    sensors.requestTemperatures();   //Se envía el comando para leer la temperatura
    float temp = sensors.getTempCByIndex(0); //Se obtiene la temperatura en ºC

    Serial.print("Temperatura= ");
    Serial.print(temp);
    Serial.println(" C");
    delay(100);


    //Condiciones para iniciar bomba
    //Temp correcta y dist correcta
    if (d < 30 && temp > 24) {
      digitalWrite(bombaPin, LOW);
      digitalWrite(val1, LOW);
      digitalWrite(val2, HIGH);
      digitalWrite(ledV, HIGH);
      digitalWrite(ledR, LOW);


      //Temp incorrecta y dist correcta
    } else {
      digitalWrite(bombaPin, LOW);
      digitalWrite(val1, HIGH);
      digitalWrite(val2, LOW);
      digitalWrite(ledV, LOW);
      digitalWrite(ledR, HIGH);
    }

    long lapso = millis()-prendido;
  if(lapso > 180000){
    digitalWrite(ledV, HIGH);
    digitalWrite(ledR, HIGH);
        digitalWrite(buzzer, HIGH);

  }
  
  }

  

  //Temp
  else {
    digitalWrite(bombaPin, HIGH);
    digitalWrite(val1, LOW);
    digitalWrite(val2, LOW);
    digitalWrite(ledV, LOW);
    digitalWrite(ledR, LOW);
    digitalWrite(buzzer, LOW);
  }

  if (encendido == 0) {
    sw = 0;
    digitalWrite(buzzer, LOW);
  }

  

}

void buzz () {
  //Alarma para indicar que han pasado x minutos
  Serial.println("hola");
  

}
