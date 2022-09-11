#pragma once

#include "task.hpp"

template <typename T>
class Wrapper : public Task<TaskType<T>>{
    public:
    T element;
    template <typename ...Args>
    Wrapper(Args&&... args) : Task<TaskType<T>>{T::type},
                              element{std::forward<Args>(args)...} {};
};