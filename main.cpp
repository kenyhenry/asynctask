#include <unistd.h>
#include "taskmanager.hpp"
#include "task_test.hpp"
#include "reader_test.hpp"
#include "utils.hpp"

int main(){

    Reader<TaskId> *reader = new ReaderTest();
    TaskManager<TaskId>* taskManager = new TaskManager<TaskId>();
    taskManager->addReader(reader);

    RedLightOn redOn;
    RedLightOff redOff;

    BlueLightOn blueOn;
    BlueLightOff blueOff;

    ExtractorOn exOn;
    ExtractorOff exOff;

    WaterOn watOn;
    WaterOff watOff;

    taskManager->addTask(std::make_shared<RedLightOn>(redOn));
    taskManager->addTask(std::make_shared<RedLightOff>(redOff));
    taskManager->addTask(std::make_shared<BlueLightOn>(blueOn));
    taskManager->addTask(std::make_shared<BlueLightOff>(blueOff));
    taskManager->addTask(std::make_shared<ExtractorOn>(exOn));
    taskManager->addTask(std::make_shared<ExtractorOff>(exOff));
    taskManager->addTask(std::make_shared<WaterOn>(watOn));
    taskManager->addTask(std::make_shared<WaterOff>(watOff));

    taskManager->start();
    int x = 0;
    while(1){
    std::cout << "test " << x << std::endl;
    sleep(1);
    ++x;
    //taskManager->stop();
    if(x == 5)
        taskManager->addTask(std::make_shared<RedLightOn>(redOn));
    }
    return 0;
}
