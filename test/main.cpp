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

    // std::string uuid_red = taskbox.addTaskProg(new RedLightOn(), new RedLightOff(), 5, 3, now, now+20);
    // std::string uuid_water = taskbox.addTaskProg(new WaterOn(),new WaterOff(), now, now+15);

    // begin loop threads
    taskbox.start();
    int x = 0;
    while(1){
        std::cout << "test " << x << std::endl;
        sleep(1);
        ++x;

        // disable task (not working)
        // if(x == 10)
            // taskbox.disableTaskProg(uuid_red);

        // test to stop taskbox when needed (working)
        if(x == 20)
            taskbox.stop();
    }
    return 0;
}
