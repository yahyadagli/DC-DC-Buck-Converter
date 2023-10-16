#include <Arduino.h>
#include <FastPwmPin.h>

float Kp = 1.62f;
float Ki = 0.323;
float duty_cycle = 0.0f;
float THRESHOLD = 0.8f;
void setup() {
  Serial.begin(9600);
  pinMode(10,OUTPUT);
  FastPwmPin::enablePwmPin(10, 25000L, 50);
  pinMode(A0, INPUT);
  pinMode(A5, INPUT);
}

float sum_error = 0.0f;

void loop() {
  int vs = analogRead(A0);
  int vo = analogRead(A5);

  // Vbattery = 9v, vs = 920
  // 0-1 --> 0-255
  // Buck converter - D = Vo/Vs

  float error = 511.0f-(float)vo;
  sum_error += error;
 
  float latest_duty_cycle = (511.0f + Kp*error + Ki*sum_error) / (float)vs;

  if( abs(duty_cycle - latest_duty_cycle) >= THRESHOLD)
  {
    duty_cycle = latest_duty_cycle;
    analogWrite(10,(int)(duty_cycle * 255.0f));
  }
  delay(10);


}