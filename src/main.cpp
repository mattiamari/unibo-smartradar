#include <Arduino.h>
#include <Timer.h>
#include <EnableInterrupt.h>

#include <radar.h>

#include <pirimpl.h>
#include <servoimpl.h>
#include <sonarimpl.h>
#include <ledimpl.h>
#include <buttonimpl.h>
#include <eventhandler.h>
#include <serialimpl.h>


#define PIN_SONAR_TRIG 3
#define PIN_SONAR_ECHO 4
#define PIN_PIR 9
#define PIN_SERVO 5
#define PIN_LED_1 6
#define PIN_LED_2 7
#define PIN_BTN_1 2
#define PIN_BTN_2 3
#define PIN_BTN_3 8


smartradar::Sonar *sonar;
smartradar::Pir *pir;
smartradar::Servo *servo;
smartradar::Led *led1;
smartradar::Led *led2;

smartradar::Serial *serial;

smartradar::Radar *radar;

Timer tmr;


void onBtn1Press() {
    radar->setModeManual();
}

void onBtn2Press() {
    radar->setModeSingle();
}

void onBtn3Press() {
    radar->setModeAuto();
}

void onPirTrigger() {
    radar->pirTriggered();
}

void onTick() {
    radar->tick();
}

void setup()
{
    sonar  = new smartradar::SonarImpl(PIN_SONAR_TRIG, PIN_SONAR_ECHO);
    pir    = new smartradar::PirImpl();
    servo  = new smartradar::ServoImpl(PIN_SERVO);
    led1   = new smartradar::LedImpl(PIN_LED_1);
    led2   = new smartradar::LedImpl(PIN_LED_2);
    serial = new smartradar::SerialImpl();
    radar  = new smartradar::Radar(serial, sonar, pir, servo, led1, led2);

    enableInterrupt(PIN_BTN_1, onBtn1Press, RISING);
    enableInterrupt(PIN_BTN_2, onBtn2Press, RISING);
    enableInterrupt(PIN_BTN_3, onBtn3Press, RISING);
    enableInterrupt(PIN_PIR, onPirTrigger, RISING);

    tmr.every(TICK_INTERVAL_MS, onTick);
}

void loop()
{

}
