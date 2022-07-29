#pragma once

#include <iostream>
#include <queue>
#include <mutex>
#include <thread>
#include "reader.hpp"
#include "task.hpp"

template<typename T>
class TaskManager {
    private:
    std::vector<Reader<T>*> _readers;
    std::queue<std::shared_ptr<Task<T>>> _tasks;
    bool _starting;
    std::mutex _mutex;
    std::thread _thread;

    //construct & desctruct
    public:
    TaskManager() : _starting(false), _thread{}{};
        
    ~TaskManager(){}
    
    void addReader(Reader<T> *reader){
        _readers.push_back(reader);
    }

    //task management
    public:    
    void addTask(std::shared_ptr<Task<T>> task){
        _tasks.push(task);
    }
    
    void start(){
        if(std::try_lock(_mutex))
            _thread = std::thread(thread());
        _starting = true;
    }
    
    void stop(){
         std::try_lock(_mutex);
        _starting = false;
    }
    
    void thread(){
         while(!_tasks.empty() && _starting){
            //process task
            for(Reader<T>* r : _readers)
                r->read(_tasks.front());
            _tasks.pop();
        }
    }
};