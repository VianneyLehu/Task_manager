#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <tlhelp32.h>
#include <psapi.h>
#include <vector>
#include "process.h"
#include "snapshot.h"
#include <thread>





int main(){

    /*bool save = false;
    std::vector<ProcessInfo> processes;

    while (true) {

        std::thread processThread(GenerateProcessInfo, std::ref(processes));

        std::this_thread::sleep_for(std::chrono::seconds(1));

        processThread.join();

        for (auto &process : processes) {
            process.GetProcessInfo();
        }
        if(save == false){
            save_processinfo(processes);
            save = true;
        }
        processes.clear();
    }*/
    std::vector<PROCESSENTRY32> processList;
    std::vector<MODULEENTRY32> moduleList;
    std::vector<THREADENTRY32> threadList;

    ProcessSnapshot processSnapshot;
    ModuleSnapshot moduleSnapshot;
    ThreadSnapshot threadSnapshot;

    // Generate process snapshot
    processList = processSnapshot.GenerateSnapshot(processList);

    // Generate module snapshot
    moduleList = moduleSnapshot.GenerateSnapshot(moduleList);

    // Generate thread snapshot
    threadList = threadSnapshot.GenerateSnapshot(threadList);

    // Display process snapshot
    processSnapshot.DisplaySnapshot(processList);

    // Display module snapshot
    moduleSnapshot.DisplaySnapshot(moduleList);

    // Display thread snapshot
    threadSnapshot.DisplaySnapshot(threadList);
    return 0;
}