#pragma once

#include <mutex>
#include "task.hpp"

template<typename T>
class Reader{
    public: 
        Reader(){};
        virtual void read(std::shared_ptr<Task<T>> task){};
};