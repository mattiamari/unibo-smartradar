#include <Arduino.h>
#include <EnableInterrupt.h>
#include <TimerOne.h>

#include <radar.h>

#include <pirimpl.h>
#include <servoimpl.h>
#include <sonarimpl.h>
#include <ledimpl.h>
#include <buttonimpl.h>
#include <eventhandler.h>
#include <serialimpl.h>

#define SERIAL_BAUD 57600
#define PIN_SONAR_TRIG 4
#define PIN_SONAR_ECHO 5
#define PIN_PIR 10
#define PIN_SERVO 6
#define PIN_LED_1 6
#define PIN_LED_2 7
#define PIN_BTN_1 9
#define PIN_BTN_2 8
#define PIN_BTN_3 7


smartradar::Sonar *sonar;
smartradar::Pir *pir;
smartradar::Servo *servo;
smartradar::Led *led1;
smartradar::Led *led2;

smartradar::Serial *serial;

smartradar::Radar *radar;


void onBtn1Press() {
    Serial.println("btn1");
    radar->setModeManual();
}

void onBtn2Press() {
    Serial.println("btn2");
    radar->setModeSingle();
}

void onBtn3Press() {
    Serial.println("btn3");
    radar->setModeAuto();
}

void onPirTrigger() {
    Serial.println("pir");
    radar->pirTriggered();
}

void onTick() {
    radar->tick();
}

void setup()
{
    Serial.begin(SERIAL_BAUD);

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
    // enableInterrupt(PIN_PIR, onPirTrigger, RISING);

    Timer1.initialize(TICK_INTERVAL_MS * 1000);
    Timer1.attachInterrupt(onTick);

    Serial.println("Setup end");
}

void loop()
{

}
