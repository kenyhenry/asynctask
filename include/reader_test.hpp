#pragma once 

#include <iostream>
#include "reader.hpp"
#include "task_test.hpp"

class ReaderTest : public Reader<TaskId>{
    public: 
        ReaderTest(){};
        void read(std::shared_ptr<Task<TaskId>> task) override{            
            switch(task.get()->type){
                case TaskId::redLightOn:{
                    RedLightOn* c = static_cast<RedLightOn*>(task.get());
                    std::cout << c->x << std::endl;
                    std::cout << c->str << "\n" << std::endl;
                    break;
                }

                case TaskId::redLightOff:{
                    RedLightOff* c = static_cast<RedLightOff*>(task.get());
                    std::cout << c->y << std::endl;
                    std::cout << c->d << std::endl;
                    std::cout << c->str << "\n" << std::endl;
                    break;
                }

                case TaskId::blueLightOn:{
                    BlueLightOn* c = static_cast<BlueLightOn*>(task.get());
                    std::cout << c->y << std::endl;
                    std::cout << c->str << "\n" << std::endl;
                    break;
                }

                case TaskId::blueLightOff:{
                    BlueLightOff* c = static_cast<BlueLightOff*>(task.get());
                    std::cout << c->y << std::endl;
                    std::cout << c->str << "\n" << std::endl;
                    break;
                }

                case TaskId::extractorOn:{
                    ExtractorOn* c = static_cast<ExtractorOn*>(task.get());
                    std::cout << c->y << std::endl;
                    std::cout << c->str << "\n" << std::endl;
                    break;
                }
                case TaskId::extractorOff:{
                    ExtractorOff* c = static_cast<ExtractorOff*>(task.get());
                    std::cout << c->z << std::endl;
                    std::cout << c->str << "\n" << std::endl;
                    break;
                }

                case TaskId::waterOn:{
                    WaterOn* c = static_cast<WaterOn*>(task.get());
                    std::cout << c->y << std::endl;
                    std::cout << c->str << "\n" << std::endl;
                    break;
                }

                case TaskId::waterOff:{
                    WaterOff* c = static_cast<WaterOff*>(task.get());
                    std::cout << c->y << std::endl;
                    std::cout << c->str << "\n" << std::endl;
                    break;
                }
                
                default:
                    std::cout << "type not known" << std::endl;

            }
        };
};