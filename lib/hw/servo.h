#ifndef SMARTRADAR_SERVO_H
#define SMARTRADAR_SERVO_H

namespace smartradar
{
    class Servo
    {
    public:
        Servo() {};
        ~Servo() {};
        virtual void setAngle(int angle) = 0;
        virtual int getAngle() = 0;
        virtual int getAngleMin() = 0;
        virtual int getAngleMax() = 0;
    };
}

#endif