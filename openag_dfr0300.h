#ifndef OPENAG_DRF0300_H
#define OPENAG_DFR0300_H


#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <OneWire.h>
#include <openag_module.h>
#include <std_msgs/Float32.h>

//
#include <DallasTemperature.h>

 class Dfr0300: public Module{
  public:
  //Public Functions
  Dfr0300(int ec_pin);
  //water_temp(int w_pin);
  //Ds18b20(int w_pin);
  void begin();
  void update();
  bool get_water_electrical_conductivity(std_msgs::Float32 &msg);
  //
  //water_Temp(int w_pin);
  
  private:
  float getTemp();
  float getData();
  float averageArray(int* arr, int number);
  //bool readSensor();
  
  //Private Variables
  int _ec_pin;
  float _water_electrical_conductivity;
  bool _send_water_electrical_conductivity;
  uint32_t _time_of_last_query;
  const uint32_t _min_update_interval = 2000;
  
  float _ec_calibration_coefficient;
  float _ec_calibration_offset;
  
  //
  float _water_temperature;
  //OneWire _w_oneWire;
  //const int w_pin = 5;
  //DeviceAddress _w_address;
  //DallasTemperature _w_sensors;
  //bool _send_water_temperature;
  //float _w_water_temperature;
  //uint32_t _w_time_of_last_query;
  //bool _w_waiting_for_conversion;
  //const static uint32_t _w_min_update_interval = 1800;
  //int _w_pin = 5;
  //int w_pin = _w_pin;

};

#endif
