#include <pt.h>
#include <Arduino.h>

class Blaster {
    private:
    int darts;
    int default_rps = 0;
    int default_power = 0;
    int idle_power = 0;


    public:
    int rev_pin;
    int fire_pin;
    // Sets the default rps power and idle flywheel power
    void defaults( float rps, float power, int idle_power ) {
        this->default_rps = rps;
        this->default_power = power;
        this->idle_power = idle_power;
    }

    // Changes the ammo count when putting in a new magazine
    void reload( int darts ) {
        this->darts = darts;
    }

    // Revs the flywheels
    //! Needs to be protothreaded in main
    void rev( float power = 0, int time = 0 ) {
        if ( power = 0 ) power = this->default_power;

        // Goes to flywheels and controls the speed of the dart
        analogWrite( this->rev_pin, power / 100 * 255 );
        delay( time );
        analogWrite( this->rev_pin, this->idle_power );
    }

    // Powers a solenoid to push the darts
    //! Needs to be protothreaded in main
    void fire( float rps = 0, float power = 0, float time = 0 ) {
        if ( rps = 0 ) rps = this->default_rps;
        if ( power = 0 ) power = this->default_power;

        // Revs the flywheels before fireing
        rev( power / 100 * 255, time );

        // Fire once
        digitalWrite( this->fire_pin, HIGH );
        delay( time );
        digitalWrite( this->fire_pin, LOW );
    }
};