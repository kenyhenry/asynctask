#pragma once 

template <typename T>
T* clone(T obj){return new T();}

#include <memory>
#include "task.hpp"
#include "wrapper.hpp"

template<typename T, typename ...Args>
std::unique_ptr<Wrapper<T>> wrap_task(Args... args){
    return std::make_unique<Wrapper<T>>(Wrapper<T>(std::forward<Args>(args)...));
};

template<typename T, typename ...Args>
std::unique_ptr<Task<TaskType<T>>> create_task(Args... args){
    return wrap_task<T>(std::forward<Args>(args)...);
};

template<typename T, typename ...Args>
Wrapper<T> wrap_simple_task(Args... args){
    return Wrapper<T>(std::forward<Args>(args)...);
};

template<typename T, typename ...Args>
Task<TaskType<T>> create_simple_task(Args... args){
    return wrap_simple_task<T>(std::forward<Args>(args)...);
};

template<typename T, typename ...Args>
Task<T> clone_task(Task<T> t1){
    Task<T> t2 = t1;
    return t2;
};

template<typename T, typename U>
Wrapper<T>& cast_task(Task<U>& task){
    return static_cast<Wrapper<T>&>(task);
};

template<typename T, typename U>
T& open_task(Task<U>& task){
    return cast_task<T>(task).element;
};