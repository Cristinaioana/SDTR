/*
 * HC-SR04 example sketch
 *
 * https://create.arduino.cc/projecthub/Isaac100/getting-started-with-the-hc-sr04-ultrasonic-sensor-036380
 *
 * by Isaac100
 */

const int trigPin = 9;
const int echoPin = 12;

float duration, distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;
  Serial.print("Distanta masurata in fata(cm): ");
  Serial.print(distance); // afisare distanta(cm);
  Serial.println(" ");
  delay(100);

  if (distance > 25  )  // daca distanta > 25 cm;
    { 
      digitalWrite(4, LOW); // led rosu off;
      digitalWrite(3, LOW);  // led albastru off;
      digitalWrite(2, LOW);  // led verde off;
      
    }
    else if (distance < 25 && distance >= 20 ) // daca distanta intre 25cm si 20cm -> led VERDE ON si buzzer activ;
    {
      digitalWrite(4, LOW); // led rosu off;
      digitalWrite(3, LOW);  // led albastru off;
      digitalWrite(2, HIGH); // led verde on;
   
    }
    
    else if (distance <= 20 && distance >= 10 ) //daca distanta intre 20 si 10 cm -> led GALBEN ON si buzzer activ;
    {
      digitalWrite(4, LOW);
      digitalWrite(3, HIGH);
      digitalWrite(2, HIGH);
     
    } 
    
    else if (distance < 10 && distance > 0 ) // daca distanta < 10 cm -> led ROSU ON si buzzer activ;
    {
      digitalWrite(4, HIGH);
      digitalWrite(3, HIGH);
      digitalWrite(2, HIGH);
     
    }
    
}