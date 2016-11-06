#if ARDUINO >= 100
 #include <Arduino.h>
#else
 #include "WProgram.h"
#endif

#include <OneWire.h>
#include <DallasTemperature.h>
#include <openag_module.h>
#include <std_msgs/Float32.h>

/**
 * \brief Sensor module for temperature
 */
class Ds18b20 : public Module {
  public:
    Ds18b20(int _w_pin);
    void begin();
    //void update();
    // bool get_water_temperature(std_msgs::Float32 &msg);

  private:
    OneWire _w_oneWire;
    DeviceAddress _w_address;
    DallasTemperature _w_sensors;
    //bool _send_water_temperature;
    float _w_water_temperature;
    uint32_t _w_time_of_last_query;
    bool _w_waiting_for_conversion;
    const static uint32_t _w_min_update_interval = 2000;
};

#endif
