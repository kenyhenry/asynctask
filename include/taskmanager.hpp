#pragma once

#include <iostream>
#include <queue>
#include <mutex>
#include <thread>
#include <unistd.h>
#include <uuid/uuid.h>
#include "task.hpp"
#include "utils.hpp"

template <typename V>
using TaskType = typename std::decay<decltype(V::type)>::type;

class Compare_task{
    public:
    template <typename T>
    bool operator()(Task<T>* i1, Task<T>* i2){
        return (i1->exec_time > i2->exec_time);
    }
};

template<typename T>
class TaskManager {
    private:
    bool _starting;

    std::mutex _mutex;
    std::thread _thread;
    std::thread _prog_thread;

    std::queue<Task<T>*> _tasks;
    std::priority_queue<Task<T>*, std::vector<Task<T>*>, Compare_task> _prog_tasks;
    std::vector<std::string> _disabled_task;

    void thread(){
        while(_starting){
            while(!_tasks.empty()){
                //process task
                _mutex.lock();
                _tasks.front()->execute();
                _tasks.pop();
                _mutex.unlock();
            }
        }
    }
    
    void thread_prog(){
        while(_starting){
            while(!_prog_tasks.empty()){
                std::time_t now = std::time(nullptr);
                for(std::string uuid_disabled : _disabled_task){
                    if(!strcmp(_prog_tasks.top()->uuid, uuid_disabled.c_str())){
                        delete _prog_tasks.top();
                        _prog_tasks.pop();
                    }
                }
                if(_prog_tasks.top()->exec_time <= now) {
                    _mutex.lock();
                    _tasks.emplace(_prog_tasks.top());
                    _mutex.unlock();
                    _prog_tasks.pop();
                }
            }
        }
    }

    public:
    TaskManager() : _starting(false), _thread{}, _prog_thread{}{};
        
    ~TaskManager(){}

    void addTask(Task<T>* task){
        _mutex.lock();
        _tasks.emplace(task);
        _mutex.unlock();
    }

    std::string addTaskProg(Task<T> templateTaskOn, 
                     Task<T> templateTaskOff, 
                     int every, 
                     int during, 
                     int from, 
                     int to){
        uuid_t uuid;
        uuid_generate(uuid);
        uuid_string_t uuid_string;
        uuid_unparse(uuid, uuid_string);

        for(int x = from; x <= to; x += every){  
            // create new task
            Task<T>* taskOn = new Task<T>(templateTaskOn);
            Task<T>* taskOff = new Task<T>(templateTaskOff);
            // fill with uuid
            strcpy(taskOn->uuid, uuid_string); 
            strcpy(taskOff->uuid, uuid_string); 
            // set time execution for taskOn & taskOff
            taskOn->exec_time = x;
            taskOff->exec_time = x + during;
            // place in priority queue
            _prog_tasks.emplace(taskOn);
            _prog_tasks.emplace(taskOff);
            // to avoid last command send is On state
            if(x + during > to){
                Task<T>* lastTaskOff = new Task<T>(templateTaskOff);
                strcpy(lastTaskOff->uuid, uuid_string); 
                lastTaskOff->exec_time = to;
                _prog_tasks.emplace(lastTaskOff);
            }
        }

        return uuid_string;
    }

    std::string addTaskProg(Task<T> templateTaskOn, 
                     Task<T> templateTaskOff, 
                     int from, 
                     int to){
        uuid_t uuid;
        uuid_generate(uuid);
        uuid_string_t uuid_string;
        uuid_unparse(uuid, uuid_string);
        // create new task
        Task<T>* taskOn = new Task<T>(templateTaskOn);
        Task<T>* taskOff = new Task<T>(templateTaskOff);
        // fill with uuid
        strcpy(taskOn->uuid, uuid_string); 
        strcpy(taskOff->uuid, uuid_string); 
        // set time execution for taskOn & taskOff
        taskOn->exec_time = from;
        taskOff->exec_time = to;
        // place in priority queue
        _prog_tasks.emplace(taskOn);
        _prog_tasks.emplace(taskOff);
        
        return uuid_string;
    }

    void disableTaskProg(std::string uuidToDisable){
        _disabled_task.push_back(uuidToDisable);
    }
    
    void start(){
        _starting = true;
        _mutex.lock();
        _thread = std::thread(&TaskManager::thread, this);
        _prog_thread = std::thread(&TaskManager::thread_prog, this);
        _thread.detach();
        _mutex.unlock();
    }
    
    void stop(){
         _mutex.lock();
        _starting = false;
        _mutex.unlock();
    }
};