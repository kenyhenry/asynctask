#pragma once  

#include <mutex>
#include <uuid/uuid.h>
#include <iostream>

template <typename T>
using TaskType = typename std::decay<decltype(T::type)>::type;

template<typename T>
class Task{
    public:
    uuid_string_t uuid;
    int exec_time;
    T type;

    public:
    Task(T taskType) : type{taskType}, exec_time{0}, uuid{"NULL"} {};

    //create new task from existing (no need)
    Task(Task const* t){
        strcpy(uuid, t->uuid); 
    };
};