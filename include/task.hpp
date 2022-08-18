#pragma once  

#include <mutex>
#include <uuid/uuid.h>
#include <iostream>

template<typename T>
class Task{
    private:
    bool _ready;

    public:
    uuid_string_t uuid;
    int exec_time;
    T type;

    public:
    Task() : _ready{false}, exec_time{0}{};
    Task(Task const& t){
        type = t.type;
        std::cout << (int)type << std::endl;
        strcpy(uuid, t.uuid); 
    };
    bool isReady(){return _ready;};
    void ready(){_ready = true;};
};