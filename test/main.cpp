#include <unistd.h>
#include "taskmanager.hpp"
#include "task_test.hpp"

int main(){

    //init
    TaskManager<TaskId>* taskbox = new TaskManager<TaskId>();

    // simple test task add
    taskbox->addTask(new ExtractorOn());

    // test task prog
    std::time_t now = std::time(nullptr);

    std::string uuid_red = taskbox->addTaskProg(RedLightOn(), RedLightOff(), 5, 3, now, now+20);
    std::string uuid_water = taskbox->addTaskProg(WaterOn(), WaterOff(), now, now+15);

    // begin loop threads
    taskbox->start();
    int x = 0;
    while(1){
        std::cout << "test " << x << std::endl;
        sleep(1);
        ++x;

        // disable task (not working)
        if(x == 10)
            taskbox->disableTaskProg(uuid_red);

        // test to stop taskbox when needed (working)
        if(x == 20)
            taskbox->stop();
    }
    return 0;
}
