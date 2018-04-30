#pragma once

#define pin_moisture_sensor 29
#define adc_ch_moisture ch1
#define gardener_moisture_sensor_calibration_factor 1

#include "gardener_param.h"

float gardener_get_moisture_sensor_value();
float gardener_get_moisture_sensor_percentage( float adcval );
float gardener_get_moisture_sensor_percentage();


void update_params_moisture_sensor();

float gardener_get_moisture_sensor_value()
{

        // power on moisture sensor
        digitalWrite(pin_moisture_sensor, HIGH);
        
        // delay 5 sec:
        usleep(1000 * ( 5 * 1000 ) );

        float moisture_avalue = 0.0;
	moisture_avalue = analogRead(adc_ch_moisture) * gardener_moisture_sensor_calibration_factor;

        // turn moisture sensor back OFF:
        digitalWrite(pin_moisture_sensor, LOW);
	
	return moisture_avalue;
}

float gardener_get_moisture_sensor_percentage( float adcval )
{
	return (adcval * 100 / 32767.0);
}

float gardener_get_moisture_sensor_percentage()
{
	float adcval = 0.0;
        
        // get reading
	adcval = gardener_get_moisture_sensor_value();
        //cout << adcval;
        
	return (adcval * 100 / 32767.0);
}


void update_params_moisture_sensor()
{
    //write moisture sensor value param:
    float moisture_sensor_value = gardener_get_moisture_sensor_value();
    write_gardener_param("moisture_sensor_value", std::to_string(moisture_sensor_value));

    //write moisture sensor percentage param:
    float moisture_sensor_percentage = gardener_get_moisture_sensor_percentage();
    write_gardener_param("moisture_sensor_percentage", std::to_string(moisture_sensor_percentage));
}

void init_moisture_sensor()
{
    // set up parameters:
    clear_gardener_param("moisture_sensor_value");
    clear_gardener_param("moisture_sensor_percentage");
    
    // set up gpio pin mode
    pinMode(pin_moisture_sensor, OUTPUT);
    // make sure it is OFF
    digitalWrite(pin_moisture_sensor, LOW);
}
