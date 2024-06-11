#include "DistanceSensor.h"


void distance_sensor_initialize() {
    
  /* uruchamia sonar (puls 10 ms na `TRIGGER')
  * oczekuje na powrotny sygnał i aktualizuje
  */
  digitalWrite(DISTANCE_SENSOR_TRIG, HIGH);
  delay(10);
  digitalWrite(DISTANCE_SENSOR_TRIG, LOW);

  unsigned long time_of_travel = pulseIn(DISTANCE_SENSOR_ECHO, HIGH);

  /* prędkość dźwięku = 340m/s => 1 cm w 29 mikrosekund
  * droga tam i z powrotem, zatem:
  */
}

int getDistance() {
  unsigned long tot;      // czas powrotu (time-of-travel)
  unsigned int distance;
  digitalWrite(DISTANCE_SENSOR_TRIG, HIGH);
  delay(10);
  digitalWrite(DISTANCE_SENSOR_TRIG, LOW);
  tot = pulseIn(DISTANCE_SENSOR_ECHO, HIGH);

/* prędkość dźwięku = 340m/s => 1 cm w 29 mikrosekund
 * droga tam i z powrotem, zatem:
 */
  distance = tot/58;
  return distance;
}