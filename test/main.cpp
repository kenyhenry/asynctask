#include <unistd.h>
#include "taskmanager.hpp"
#include "task_test.hpp"
#include "reader_test.hpp"

int main(){

    //init
    Reader<TaskId> *reader = new ReaderTest();
    TaskManager<TaskId>* taskbox = new TaskManager<TaskId>();
    taskbox->addReader(reader);

    // simple test task add
    taskbox->addTask(new ExtractorOn());

    // test task prog
    std::time_t now = std::time(nullptr);

    // begin loop threads
    taskbox->start();
    int x = 0;
    while(1){
        std::cout << "test " << x << std::endl;
        sleep(1);
        ++x;

        // test to stop taskbox when needed (working)
        if(x == 20)
            taskbox->stop();
    }
    return 0;
}
