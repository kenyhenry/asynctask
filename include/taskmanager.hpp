#pragma once

#include <iostream>
#include <queue>
#include <mutex>
#include <thread>
#include <unistd.h>
#include <uuid/uuid.h>
#include "reader.hpp"
#include "task.hpp"
#include "utils.hpp"

template<typename T>
class TaskManager {
    private:
    bool _starting;

    std::mutex _mutex;
    std::thread _thread;

    std::vector<Reader<T>*> _readers;
    std::queue<Task<T>*> _tasks;

    void thread(){
        while(_starting){
            while(!_tasks.empty()){
                //process task
                _mutex.lock();
                for(Reader<T>* r : _readers){
                    r->read(_tasks.front());
                }
                _tasks.pop();
                _mutex.unlock();
            }
        }
    }

    public:
    TaskManager() : _starting(false), _thread{}{};
        
    ~TaskManager(){}
    
    void addReader(Reader<T> *reader){
        _readers.push_back(reader);
    }

    void addTask(Task<T>* task){
        _mutex.lock();
        _tasks.emplace(task);
        _mutex.unlock();
    }

    void start(){
        _starting = true;
        _mutex.lock();
        _thread = std::thread(&TaskManager::thread, this);
        _thread.detach();
        _mutex.unlock();
    }
    
    void stop(){
         _mutex.lock();
        _starting = false;
        _mutex.unlock();
    }
};