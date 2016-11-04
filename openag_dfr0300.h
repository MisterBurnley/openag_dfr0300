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

 class Dfr0300: public Module{
  public:
  //Public Functions
  Dfr0300(int ec_pin);
  void begin();
  void update();
  bool get_water_electric_conductivity(std_msgs::Float32 &msg);
  
  private:
  float getData();
  float avergeArray(int* arr, int number);
  //bool readSensor();
  
  //Private Variables
  int _ec_pin;
  float _water_electric_conductivity;
  bool _send_water_electric_conductivity;
  uint32_t _time_of_last_query;
  
  
  float _ec_calibration_coefficient_;
  float _ec_calibration_offset_;
  

};

#endif
