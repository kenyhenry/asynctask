#pragma once  

#include <mutex>
#include <uuid/uuid.h>
#include <iostream>

template<typename T>
class Task{
    public:
    uuid_string_t uuid;
    int exec_time;
    T type;

    public:
    Task() : exec_time{0}{};
    Task(Task const& t){
        type = t.type;
        std::cout << (int)type << std::endl;
        strcpy(uuid, t.uuid); 
    };

    virtual void execute() = 0;
};