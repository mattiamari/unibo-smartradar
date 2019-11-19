#ifndef SMARTRADAR_PIR_H
#define SMARTRADAR_PIR_H

namespace smartradar
{
    class Pir
    {
    public:
        Pir() {};
        ~Pir() {};
        virtual bool isDetecting();
    };
}

#endif