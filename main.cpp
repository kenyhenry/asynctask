#include "taskmanager.hpp"
#include "task_test.hpp"
#include "reader_test.hpp"
#include "utils.hpp"

int main(){

    Reader<TaskId> *reader = new ReaderTest();
    TaskManager<TaskId> taskbox;
    taskbox.addReader(reader);

    RedLightOn redOn;
    RedLightOff redOff;

    BlueLightOn blueOn;
    BlueLightOff blueOff;

    ExtractorOn exOn;
    ExtractorOff exOff;

    WaterOn watOn;
    WaterOff watOff;

    taskbox.addTask(std::make_shared<RedLightOn>(redOn));
    taskbox.addTask(std::make_shared<RedLightOff>(redOff));
    taskbox.addTask(std::make_shared<BlueLightOn>(blueOn));
    taskbox.addTask(std::make_shared<BlueLightOff>(blueOff));
    taskbox.addTask(std::make_shared<ExtractorOn>(exOn));
    taskbox.addTask(std::make_shared<ExtractorOff>(exOff));
    taskbox.addTask(std::make_shared<WaterOn>(watOn));
    taskbox.addTask(std::make_shared<WaterOff>(watOff));

    taskbox.start();
    return 0;
}
