#pragma once 

#include <iostream>
#include "reader.hpp"
#include "task_test.hpp"
#include <unistd.h>

class ReaderTest : public Reader<TaskId>{
    public: 
        ReaderTest(){};
        void read(Task<TaskId> *task) override{
            std::cout  << "read type = " << (int)task->type << std::endl;
            switch(task->type){
                case TaskId::redLightOn:{
                    std::cout << "redLightOn" << std::endl;
                    break;
                }

                case TaskId::redLightOff:{
                    std::cout << "redLightOff" << std::endl;
                    break;
                }

                case TaskId::blueLightOn:{
                    std::cout << "blueLightOn" << std::endl;
                    break;
                }

                case TaskId::blueLightOff:{
                    std::cout << "blueLightOff" << std::endl;
                    break;
                }

                case TaskId::extractorOn:{
                    std::cout << "extractorOn" << std::endl;
                    break;
                }
                case TaskId::extractorOff:{
                    std::cout << "extractorOff" << std::endl;
                    break;
                }

                case TaskId::waterOn:{
                    std::cout << "waterOn" << std::endl;
                    break;
                }

                case TaskId::waterOff:{
                    std::cout << "waterOff" << std::endl;
                    break;
                }
                
                default:
                    std::cout << "type not known" << std::endl;
            }
            task->ready();
            delete task;
        };
};