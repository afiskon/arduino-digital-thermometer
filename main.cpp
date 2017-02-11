#include <Arduino.h>
#include <glcd.h>
#include <fonts/SystemFont5x7.h>

#define ZERO_X_OFFSET 35
#define MAX_TEMPERATURE 28
#define MIN_TEMPERATURE (-28)
#define HIST_SIZE 128

float hist[HIST_SIZE] = { 0.0 };
int curr_hist_idx = 0;

void setup()
{
  GLCD.Init(NON_INVERTED);
  GLCD.SelectFont(System5x7);
}

inline float sensor_to_celsius(int sensor)
{
  return ((((float)sensor * 5000.0) / 1024.0) - 500.0) / 10.0;
}

inline int limit_temperature(int t)
{
  if(t > MAX_TEMPERATURE)
    return MAX_TEMPERATURE;

  if(t < MIN_TEMPERATURE)
    return MIN_TEMPERATURE;

  return t;
}

void loop()
{
  int sensor = analogRead(5);
  float celsius = sensor_to_celsius(sensor);
  GLCD.ClearScreen();
  GLCD.CursorTo(0, 0);
  GLCD.Puts("Current: " + String(celsius));

  hist[curr_hist_idx] = celsius;

  int stop_i = curr_hist_idx;

  curr_hist_idx++;
  if(curr_hist_idx == HIST_SIZE)
    curr_hist_idx = 0;

  GLCD.DrawLine(0, ZERO_X_OFFSET, HIST_SIZE-1, ZERO_X_OFFSET, BLACK);
  /*
  GLCD.DrawLine(0, ZERO_X_OFFSET - MAX_TEMPERATURE, HIST_SIZE-1, ZERO_X_OFFSET - MAX_TEMPERATURE, BLACK);
  GLCD.DrawLine(0, ZERO_X_OFFSET - MIN_TEMPERATURE, HIST_SIZE-1, ZERO_X_OFFSET - MIN_TEMPERATURE, BLACK);
  */

  int prev_i;
  int i = curr_hist_idx;
  int x = 0;
  do
  {
    if(x >= 1)
      GLCD.DrawLine(x-1, ZERO_X_OFFSET - limit_temperature(hist[prev_i]), x, ZERO_X_OFFSET - limit_temperature(hist[i]), BLACK);

    x++;
    prev_i = i;

    i++;
    if(i == HIST_SIZE)
      i = 0;
  } while(i != stop_i);

  delay(2000);
}
