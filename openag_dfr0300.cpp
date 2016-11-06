
 #include "openag_dfr0300.h"
 //#include "ds18b20.h"
 
 Dfr0300::Dfr0300(int ec_pin){
   _ec_pin = ec_pin;
   status_level = OK;
   status_msg = "";
 }
 
 Dfr0300::water_temp(int _w_pin) : _oneWire(_w_pin) {
  _w_sensors = DallasTemperature(&_w_oneWire);
  _sw_ensors.setWaitForConversion(false);
 }
 
 void Dfr0300::begin(){
   Serial2.begin(9600);
   _time_of_last_query = 0;
   _ec_calibration_offset = 0.15;
 }
 
 void Dfr0300::update(){
   if (millis() - _time_of_last_query > _min_update_interval){
     getTamp();
     getData();
     _time_of_last_query = millis();
   }
 }
 
 bool Dfr0300::get_water_electric_conductivity(std_msgs::Float32 &msg){
   msg.data = _water_electrical_conductivity;
   bool res = _send_water_electrical_conductivity;
   _send_water_electrical_conductivity = false;
   return res;
 }
 
  float Dfr0300::averageArray(int* arr, int number){
   int i;
   int max,min;
   float avg;
   long amount=0;
   if (number<=0){ //if
     return 0;
   } //if(number<=0)
  
   if (number<5){ // less than 5, calculated directly statistics
     for(i=0;i<number;i++){ //if
       amount+=arr[i];
     } //for (i=0;i<number;i++)
      avg = amount/number;
      return avg;
   } //if (number<5)
  
   else {  //first_else
    
       if(arr[0]<arr[1]){// if(arr[0]<arr[1])
         min = arr[0];
         max = arr[1];
       } // if(arr[0]<arr[1])
    
       else{ // second_else
         min = arr[1];
         max = arr[0];
       } // second_else
    
       for (i=2; i<number; i++){//for (i=2; i<number; i++)
         if (arr[i]<min){ //if (arr[i]<min)
           amount+=min;
           min=arr[i];
         } //if (arr[i]<min)
         else 
         { // third_else
           if (arr[i]>max){ // if (arr[i]>max)
             amount+=max;
             max=arr[i];
           } //if (arr[i]>max)
          
           else
           { //fourth_else
             amount+=arr[i];
           } //fourth_else
         } //third_else
       } //for (i=2; i<number; i++)
       avg = (float) amount/(number-2);
     } // first_else 
  return avg;
} //end of function

//.......................................Private.......................................//

 float Dfr0300::getData(void){
   Serial2.println("HiData");
   int analog_sum = 0;
   const int samples = 20;
   for (int i = 0; i<samples; i++){
     analog_sum += analogRead(_ec_pin);
   }
   float analog_average = (float) analog_sum / samples;
   float analog_voltage = analog_average*(float)5000/1024;
   float temperature_coefficient = 1.0 + 0.0185*(_w_water_temperature - 25.0);
   float voltage_coefficient = analog_voltage / temperature_coefficient;
   if(voltage_coefficient < 0) {
    return 0;
    //Serial.println("No solution!");   //25^C 1413us/cm<-->about 216mv  if the voltage(compensate)<150,that is <1ms/cm,out of the range
  }
  else if (voltage_coefficient > 3300) {
    return 0;
    //Serial.println("Out of the range!");  //>20ms/cm,out of the range
  }
  else { 
    if(voltage_coefficient <= 448) {
      _water_electrical_conductivity = (6.84*voltage_coefficient-64.32)/1000 + _ec_calibration_offset);
      return _water_electrical_conductivity   //1ms/cm<EC<=3ms/cm
    }
    else if (voltage_coefficient <= 1457) {
      _water_electrical_conductivity = (6.98*voltage_coefficient-127)/1000 + _ec_calibration_offset
      return _water_electrical_conductivity  //3ms/cm<EC<=10ms/cm
    }
    else {
      _water_electrical_conductivity = (5.3*voltage_coefficient+2278)/1000 + _ec_calibration_offset;
      Serial2.println(_water_electrical_conductivity); 
      return _water_electrical_conductivity; //10ms/cm<EC<20ms/cm
    }
   }
 }
 
 float Dfr0300::getTemp(void){
  if (w__waiting_for_conversion) {
    if (w__sensors.isConversionComplete()) {
      status_level = OK;
      status_msg = "";
      _w_waiting_for_conversion = false;
      _w_water_temperature = _w_sensors.getTempC(_address);
    }
    else if (millis() - _w_time_of_last_query > _w_min_update_interval) {
      status_level = ERROR;
      status_msg = "Sensor isn't responding to queries";
    }
  }
  if (millis() - _w_time_of_last_query > _w_min_update_interval) {
    _w_sensors.requestTemperatures();
    _waiting_for_conversion = true;
    _time_of_last_query = millis();
  }
 }
 
 }
