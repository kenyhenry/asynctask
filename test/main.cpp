#include <unistd.h>
#include "taskmanager.hpp"
#include "task_test.hpp"
#include "reader_test.hpp"

int main(){

    //init
    ReaderTest *reader = new ReaderTest();
    TaskManager<TaskId> taskbox;
    taskbox.addReader(reader);

    // simple test task add
    taskbox.addTask<RedLightOn>(42);

    // test task prog
    std::time_t now = std::time(nullptr);

    std::string uuid_blue_on = taskbox.addTaskProg<BlueLightOn>(3, now, now+10);
    std::string uuid_blue_off = taskbox.addTaskProg<BlueLightOff>(5, now, now+12);
    std::string uuid_water_on = taskbox.addTaskProg<WaterOn>(10, now, now+20);
    
    // begin loop threads
    taskbox.start();
    int x = 0;
    while(1){
        std::cout << "- " << std::endl;
        sleep(1);
        ++x;

        // disable task (not working)
        if(x == 2)
            taskbox.disableTaskProg(uuid_blue_on);

        // test to stop taskbox when needed (working)
        if(x == 15)
            taskbox.stop();
    }
    return 0;
}
