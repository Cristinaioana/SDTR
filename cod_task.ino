#include <Arduino_FreeRTOS.h>

const int trigPin1 = 9;
const int echoPin1 = 12;
const int trigPin2 = 11;
const int echoPin2 = 10;

float distance1, distance2;
unsigned long duration1, duration2;

void setup() {
  Serial.begin(9600);

  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  
  pinMode(2, OUTPUT);  
  pinMode(3, OUTPUT);  
  pinMode(4, OUTPUT);  
  pinMode(5, OUTPUT);  
  pinMode(6, OUTPUT);  
  pinMode(7, OUTPUT);  

  xTaskCreate(sensorTask1,  "SensorTask1",  100, NULL, 1, NULL);
  xTaskCreate(sensorTask2,  "SensorTask2",  100, NULL, 1, NULL);
  xTaskCreate(controlTask1, "ControlTask1", 100, NULL, 2, NULL);
  xTaskCreate(controlTask2, "ControlTask2", 100, NULL, 2, NULL);
  xTaskCreate(sendDataTask, "SendDataTask", 100, NULL, 2, NULL);

  vTaskStartScheduler();  // Start the FreeRTOS scheduler
}

void loop() {
  // The loop function should be empty or used for low-priority tasks.
}

static void sensorTask1(void* pvParameters) {
  while (1) 
  {
    digitalWrite(trigPin1, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin1, LOW);

    duration1 = pulseIn(echoPin1, HIGH);
    distance1 = (duration1 / 2) / 29.1;

    vTaskDelay(250 / portTICK_PERIOD_MS);
  }
}

static void sensorTask2(void* pvParameters) {
  while (1) 
  {
    digitalWrite(trigPin2, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin2, LOW);

    duration2 = pulseIn(echoPin2, HIGH);
    distance2 = (duration2 / 2) / 29.1;

    vTaskDelay(250 / portTICK_PERIOD_MS);
  }
}

static void controlTask1(void* pvParameters) {
  while (1) 
  {
    if (distance1 > 25) {
      digitalWrite(4, LOW);
      digitalWrite(3, LOW);
      digitalWrite(2, LOW);
    } else if (distance1 < 25 && distance1 >= 20) {
      digitalWrite(4, LOW);
      digitalWrite(3, LOW);
      digitalWrite(2, HIGH);
    } else if (distance1 <= 20 && distance1 >= 10) {
      digitalWrite(4, LOW);
      digitalWrite(3, HIGH);
      digitalWrite(2, HIGH);
    } else if (distance1 < 10 && distance1 > 0) {
      digitalWrite(4, HIGH);
      digitalWrite(3, HIGH);
      digitalWrite(2, HIGH);
    }

    vTaskDelay(150 / portTICK_PERIOD_MS);  // Task delay of 100 milliseconds
  }
}

static void controlTask2(void* pvParameters) {
  while (1) 
  {
    if (distance2 > 25) {
      digitalWrite(7, LOW);
      digitalWrite(6, LOW);
      digitalWrite(5, LOW);
    } else if (distance2 < 25 && distance2 >= 20) {
      digitalWrite(7, LOW);
      digitalWrite(6, LOW);
      digitalWrite(5, HIGH);
    } else if (distance2 <= 20 && distance2 >= 10) {
      digitalWrite(7, LOW);
      digitalWrite(6, HIGH);
      digitalWrite(5, HIGH);
    } else if (distance2 < 10 && distance2 > 0) {
      digitalWrite(7, HIGH);
      digitalWrite(6, HIGH);
      digitalWrite(5, HIGH);
    }

    vTaskDelay(150 / portTICK_PERIOD_MS);  // Task delay of 100 milliseconds
  }
}

static void sendDataTask(void* pvParameters) {
  while (1) {
    // Send distance data to HC-05 module
    Serial.print("Distanta senzor fata (cm): ");
    Serial.println(distance1);
    Serial.print("Distanta senzor spate (cm): ");
    Serial.println(distance2);

    vTaskDelay(150 / portTICK_PERIOD_MS);  // Task delay of 1 second
  }
}