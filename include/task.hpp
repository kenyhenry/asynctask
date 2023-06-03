#pragma once

#include <mutex>
#include <uuid/uuid.h>
#include <iostream>

template <typename T>
using TaskType = typename std::decay<decltype(T::type)>::type;

template<typename T>
class Task{
    public:
    T type;

    // data for planned or program task
    uuid_string_t uuid;
    int exec_time;
    int from;
    int to;
    int every;

    public:
    Task(T taskType) : type(taskType){};
};