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

    void thread(){
        while(_starting){
            while(!_tasks.empty()){
                //process task
                for(Reader<T>* r : _readers)
                    r->read(_tasks.front());
                _tasks.pop();
            }
        }
    }

    public:
    TaskManager() : _starting(false), _thread{}{};
        
    ~TaskManager(){}
    
    void addReader(Reader<T> *reader){
        _readers.push_back(reader);
    }

    void addTask(std::shared_ptr<Task<T>> task){
        _tasks.push(task);
    }
    
    void start(){
        _starting = true;
        std::unique_lock<std::mutex> lock(_mutex);
        _thread = std::thread(&TaskManager::thread, this);
        _thread.detach();
    }
    
    void stop(){
         std::unique_lock<std::mutex> lock(_mutex);
        _starting = false;
    }
};