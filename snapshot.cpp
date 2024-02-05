#include <stdio.h>
#include <iostream>
#include <vector>
#include <windows.h>
#include <tlhelp32.h>
#include <fstream>
#include "snapshot.h"





std::vector<PROCESSENTRY32> ProcessSnapshot::GenerateSnapshot(std::vector<PROCESSENTRY32> processList){

    HANDLE snapshot;
    PROCESSENTRY32 process;
    process.dwSize = sizeof(process);

    snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);

    Process32First(snapshot, &process);


    while(Process32Next(snapshot, &process)){
        (processList.push_back(process));
    }


    return processList;
}




std::vector<MODULEENTRY32> ModuleSnapshot::GenerateSnapshot(std::vector<MODULEENTRY32> ModuleList){

    HANDLE snapshot;
    MODULEENTRY32 module;
    module.dwSize = sizeof(module);

    snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE,0);

    Module32First(snapshot, &module);


    while(Module32Next(snapshot, &module)){
        (ModuleList.push_back(module));
    }


    return ModuleList;
}



std::vector<THREADENTRY32> ThreadSnapshot::GenerateSnapshot(std::vector<THREADENTRY32> threadList){

    HANDLE snapshot;
    THREADENTRY32 thread;
    thread.dwSize = sizeof(thread);

    snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD,0);

    Thread32First(snapshot, &thread);


    while(Thread32Next(snapshot, &thread)){
        (threadList.push_back(thread));
    }


    return threadList;
}




void ProcessSnapshot::DisplaySnapshot(const std::vector<PROCESSENTRY32>& processList){


    std::ofstream file("Saveprocess.txt");

    for(auto process : processList){

        std::cout <<"_______________"<<std::endl;
        std::cout <<"PID: "<<process.th32ProcessID<<std::endl;
        std::cout <<"Process name: "<< process.szExeFile<<std::endl;
        std::cout <<"Threads: "<<process.cntThreads<<std::endl;
        std::cout <<"Parent PID: "<< process.th32ParentProcessID<<std::endl;

        //save to file
        file <<"___"<<std::endl;
        file <<"PID: "<<process.th32ProcessID<<std::endl;
        file <<"Process name: "<< process.szExeFile<<std::endl;
        file <<"Threads: "<<process.cntThreads<<std::endl;
        file <<"Parent PID: "<< process.th32ParentProcessID<<std::endl;
    }

    file.close();

}


void ModuleSnapshot::DisplaySnapshot(const std::vector<MODULEENTRY32>& moduleList){

    
    std::ofstream file("Savemodule.txt");

    for(auto module: moduleList){

        std::cout <<"_______________"<<std::endl;
        std::cout <<"PID: "<<module.th32ModuleID<<std::endl;
        std::cout <<"Module name: "<< module.szModule<<std::endl;
        std::cout <<"Module path: "<< module.szExePath<<std::endl;
        std::cout <<"Module size:  "<< module.modBaseSize / (1024* 1024)<<"MB"<<std::endl;
        file <<"_______________"<<std::endl;
        file <<"PID: "<<module.th32ModuleID<<std::endl;
        file <<"Module name: "<< module.szModule<<std::endl;
        file <<"Module path: "<< module.szExePath<<std::endl;
        file <<"Module size:  "<< module.modBaseSize<<std::endl;
    }

    file.close();
}

void ThreadSnapshot::DisplaySnapshot(const std::vector<THREADENTRY32>& threadList){

    
    std::ofstream file("Savethread.txt");

    for(auto thread: threadList){

        std::cout <<"_______________"<<std::endl;
        std::cout <<"Thread ID: "<<thread.th32ThreadID<<std::endl;
        std::cout <<"Process owner ID:  "<< thread.th32OwnerProcessID<<std::endl;
        std::cout <<"Priority level : "<< thread.tpBasePri<<std::endl;
        //save to file
        file <<"_______________"<<std::endl;
        file <<"Thread ID: "<<thread.th32ThreadID<<std::endl;
        file <<"Process owner ID:  "<< thread.th32OwnerProcessID<<std::endl;
        file <<"Priority level : "<< thread.tpBasePri<<std::endl;
    }

    file.close();
}


