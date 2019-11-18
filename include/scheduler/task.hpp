#ifndef TASK_HPP
#define TASK_HPP

class Task
{
public:
    Task() {}
    virtual ~Task() {}
    virtual void step() = 0;
    virtual bool isComplete() = 0;
};

#endif