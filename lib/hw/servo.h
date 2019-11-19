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
    };
}

#endif