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

class Compare_task{
    public:
    template <typename T>
    bool operator()(Task<T> const& i1, Task<T> const& i2){
        return (i1.exec_time > i2.exec_time);
    }
};

template<class T>
class TaskManager {
    private:
    bool _starting;

    std::mutex _mutex;
    std::mutex _prog_mutex;
    std::thread _thread;
    std::thread _prog_thread;

    std::vector<Reader<T>*> _readers;
    std::queue<std::unique_ptr<Task<T>>> _tasks;
    std::priority_queue<Task<T>, std::vector<Task<T>>, Compare_task> _prog_tasks;
    std::vector<std::string> _disabled_task;

    void thread(){
        while(_starting){
            while(!_tasks.empty()){
                //process task
                _mutex.lock();
                //second send to readers event read
                if(!_readers.empty()){
                    for(Reader<T>* r : _readers){
                        r->read(_tasks.front().get());
                    }
                }
                _tasks.front().release();
                _tasks.pop();
                _mutex.unlock();
            }
        }
    }
    
    void thread_prog(){
        while(_starting){
            // priorise taskProg
            while(!_prog_tasks.empty()){
                // check for disable task to pop
                for(std::string uuid_disabled : _disabled_task){
                    if(!strcmp(_prog_tasks.top().uuid, uuid_disabled.c_str())){
                        std::cout << "task disable pop " << std::endl;
                        _prog_mutex.lock();
                        _prog_tasks.pop();
                        _prog_mutex.unlock();
                    }
                }

                // check if taskProg is ended
                if(_prog_tasks.top().exec_time > (_prog_tasks.top().to - _prog_tasks.top().every)){
                    std::time_t now = std::time(nullptr);
                    std::cout << "delete task prog " << (int)_prog_tasks.top().type << std::endl;
                    _prog_mutex.lock();
                    _prog_tasks.pop();
                    _prog_mutex.unlock();
                }

                // execute task
                std::time_t now = std::time(nullptr);
                if(_prog_tasks.top().exec_time <= now) {
                    
                    _mutex.lock();
                    _tasks.emplace(std::make_unique<Task<T>>(clone_task(_prog_tasks.top())));
                    _mutex.unlock();
                    
                    _prog_mutex.lock();
                    Task<T> t2 = clone_task(_prog_tasks.top());
                    _prog_tasks.pop();
                    t2.exec_time += t2.every;
                    _prog_tasks.push(t2);
                    _prog_mutex.unlock();
                }
            }
        }
    }

    public:
    TaskManager() : _starting(false), _thread{}, _prog_thread{}{};
        
    ~TaskManager(){}
    
    void addReader(Reader<T> *reader){
        _readers.push_back(reader);
    }

    template <typename U, typename ...Args>
    void addTask(Args... args){
        _mutex.lock();
        auto t = create_task<U>(std::forward<Args>(args)...);
        _tasks.emplace(std::move(t));
        _mutex.unlock();
    }

    // no args provide for task prog
    template <typename U>
    std::string addTaskProg(int every, 
                            int from, 
                            int to){
        uuid_t uuid;
        uuid_generate(uuid);
        uuid_string_t uuid_string;
        uuid_unparse(uuid, uuid_string);

        // create new task
        auto tp = create_simple_task<U>();
        strcpy(tp.uuid, uuid_string);
        tp.from = from;
        tp.to = to;
        tp.every = every;
        tp.exec_time = from;

        _prog_tasks.emplace(tp);

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

