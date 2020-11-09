//
// Created by Anton on 28-4-2020.
//

#ifndef PROGRAMMEREN_EVENT_H
#define PROGRAMMEREN_EVENT_H


class Event {
public:
    virtual bool gameRunning()=0;
    virtual int eventManager()=0;
    virtual int getXScale()= 0;
    virtual int getYScale()= 0;
protected:
    bool* isRunning ;
    int resizedBreedte, resizedHoogte;
};



#endif //PROGRAMMEREN_EVENT_H
