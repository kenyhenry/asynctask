#pragma once  

#include <mutex>
#include <uuid/uuid.h>
#include <iostream>

template<typename T>
class Task{
    bool _ready;

    public:
    uuid_string_t uuid;
    int exec_time;
    T type;

    public:
    Task() : _ready{false}, exec_time{0}{};

    //create new task from existing (no need)
    Task(Task const* t){
        std::cout << (int)type << std::endl;
        strcpy(uuid, t->uuid); 
    };

    bool isReady(){return _ready;};
    void ready(){_ready = true;};
};