#pragma once 

#include <iostream>
#include "reader.hpp"
#include "task_test.hpp"
#include <unistd.h>

class ReaderTest : public Reader<TaskId>{

    public: 
    ReaderTest(){};
    void read(Task<TaskId>* task) override{
        // std::cout << "address = " << std::hex << task << std::endl;
        // std::cout << "uuid = " << task->uuid << std::endl;
        // std::cout  << "read type = " << (int)task->type << std::endl;
        switch(task->type){
            case TaskId::redLightOn:{
                auto& t = open_task<RedLightOn>(*task);
                std::cout << "redLightOn x = " << t.x << std::endl;
                break;
            }
            case TaskId::redLightOff:{
                auto& t = open_task<RedLightOff>(*task);
                std::cout << "redLightOff" << std::endl;
                break;
            }
            case TaskId::blueLightOn:{
                auto& t = open_task<BlueLightOn>(*task);
                std::cout << "blueLightOn" << std::endl;
                break;
            }
            case TaskId::blueLightOff:{
                auto& t = open_task<BlueLightOff>(*task);
                std::cout << "blueLightOff" << std::endl;
                break;
            }
            case TaskId::extractorOn:{
                auto& t = open_task<ExtractorOn>(*task);
                std::cout << "extractorOn" << std::endl;
                break;
            }
            case TaskId::extractorOff:{
                auto& t = open_task<ExtractorOff>(*task);
                std::cout << "extractorOff" << std::endl;
                break;
            }
            case TaskId::waterOn:{
                auto& t = open_task<WaterOn>(*task);
                std::cout << "waterOn" << std::endl;
                break;
            }
            case TaskId::waterOff:{
                auto& t = open_task<WaterOff>(*task);
                std::cout << "waterOff" << std::endl;
                break;
            }
            
            default:
                std::cout << "type not known" << std::endl;
        }
    };
};