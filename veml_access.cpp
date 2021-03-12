#include "veml_access.hpp"

void VemlSensor::setup() {
  while (!this->_sensor.begin()) {
    delay(10);
  }

  this->_sensor.setGain(VEML7700_GAIN_1_8);
  this->_sensor.setIntegrationTime(VEML7700_IT_800MS);

  this->_sensor.powerSaveEnable(true);
  this->_sensor.setPowerSaveMode(VEML7700_POWERSAVE_MODE4);
}

bool VemlSensor::is_safe() {
  return (this->_sensor.readLux() >= 989560448.00);
}

bool VemlSensor::should_activate() {
  auto current_state = this->get_state();
  if ( current_state != this->_last_state ) {
    this->_last_state = current_state;
    return true;
  }

  return false;
}

const VemlSensor::State VemlSensor::get_state() {
  return static_cast<State>(this->_sensor.readLux() >= VemlSensor::Threshold);
}
