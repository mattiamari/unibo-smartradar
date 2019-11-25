#include <Arduino.h>
#include <EnableInterrupt.h>
#include <TimerOne.h>

#include <radar.h>

#include <pirimpl.h>
#include <servoimpl.h>
#include <sonarimpl.h>
#include <potentiometerimpl.h>
#include <ledimpl.h>
#include <serialimpl.h>

#define SERIAL_BAUD 115200
#define PIN_SONAR_TRIG 4
#define PIN_SONAR_ECHO 5
#define PIN_PIR 10
#define PIN_SERVO 6
#define PIN_LED_1 12
#define PIN_LED_2 11
#define PIN_BTN_1 9
#define PIN_BTN_2 8
#define PIN_BTN_3 7
#define PIN_POT A0


smartradar::Sonar *sonar;
smartradar::Pir *pir;
smartradar::Servo *servo;
smartradar::Potentiometer *pot;
smartradar::Led *led1;
smartradar::Led *led2;
smartradar::Serial *serial;
smartradar::Radar *radar;

unsigned long time = 0;
unsigned long diff;

enum SerialCommands {
    CMD_SWITCH_MANUAL = 97, // a 0x61
    CMD_SWITCH_SINGLE,      // b 0x62
    CMD_SWITCH_AUTO,        // c 0x63
    CMD_SERVO_LEFT,         // d 0x64
    CMD_SERVO_RIGHT,        // e 0x65
    CMD_SPEED               // f 0x66
};
// terminating character is z 0x7A

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

void serialEvent() {
    char buf[3];
    char tmp;
    int16_t *duration = (int16_t *)&(buf[1]);

    Serial.readBytesUntil('z', buf, 3);

    switch (buf[0]) {
        case CMD_SWITCH_AUTO: radar->setModeAuto(); break;
        case CMD_SWITCH_SINGLE: radar->setModeSingle(); break;
        case CMD_SWITCH_MANUAL: radar->setModeManual(); break;
        case CMD_SERVO_LEFT: radar->servoLeft(); break;
        case CMD_SERVO_RIGHT: radar->servoRight(); break;
        case CMD_SPEED:
            tmp = buf[1];
            buf[1] = buf[2];
            buf[2] = tmp;
            radar->setScanDuration(*duration);
    }
}

void setup()
{
    Serial.begin(SERIAL_BAUD);

    sonar  = new smartradar::SonarImpl(PIN_SONAR_TRIG, PIN_SONAR_ECHO);
    pir    = new smartradar::PirImpl();
    servo  = new smartradar::ServoImpl(PIN_SERVO);
    pot    = new smartradar::PotentiometerImpl(PIN_POT);
    led1   = new smartradar::LedImpl(PIN_LED_1);
    led2   = new smartradar::LedImpl(PIN_LED_2);
    serial = new smartradar::SerialImpl();
    radar  = new smartradar::Radar(serial, sonar, pir, servo, pot, led1, led2);

    enableInterrupt(PIN_BTN_1, onBtn1Press, RISING);
    enableInterrupt(PIN_BTN_2, onBtn2Press, RISING);
    enableInterrupt(PIN_BTN_3, onBtn3Press, RISING);
    enableInterrupt(PIN_PIR, onPirTrigger, RISING);

    led1->turnOn();
    led2->turnOn();
    servo->setAngle(servo->getAngleMax());
    delay(800);
    servo->setAngle(servo->getAngleMin());
    led1->turnOff();
    led2->turnOff();

    Serial.println("Setup end");

    radar->setModeManual();
}

void loop()
{
    time = millis();
    radar->tick();
    diff = millis() - time;

    if (diff < TICK_INTERVAL_MS) {
        delay(TICK_INTERVAL_MS - diff);
    } else if (diff > TICK_INTERVAL_MS) {
        Serial.println("Can't keep up");
    }
}
