#include "process.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

//Getter
DWORD ProcessInfo::GetPID() const {
    return pid;
}

const std::string& ProcessInfo::GetName() const{
    return name;
}

DWORD ProcessInfo::GetMemoryUsageMB() const {
    return memoryusageMB;
}



//Setter 
void ProcessInfo::SetPID(DWORD p){
    pid = p;
}

void ProcessInfo::SetSetName(std::string n){
    name = n;
}


void ProcessInfo::SetMemoryUsageMB(DWORD m){
    memoryusageMB = m;
}

void ProcessInfo::GetProcessInfo(){
    std::cout<<"PID: "<<pid<<"\n";
    std::cout<<"name: "<<name<<"\n";
    std::cout<<"Memory usage: "<<memoryusageMB<<" MB"<<"\n";

}


void GenerateProcessInfo(std::vector<ProcessInfo> &P){

    DWORD processList[1024], nbProcesses, sizeProcesslist;

    if(!EnumProcesses(processList, sizeof(processList), &sizeProcesslist)){

    }else{
        nbProcesses = sizeProcesslist / sizeof(DWORD);
        for(DWORD i = 0; i < nbProcesses; i++){
            DWORD pid = processList[i];
            ProcessInfo PI;

            PI.SetPID(pid);
            HANDLE hprocess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
            if(hprocess != NULL){

                PI.SetSetName(GetNameByHandle(hprocess));  

                PI.SetMemoryUsageMB(GetMemoryUsageByHandle(hprocess));

            }
            P.push_back(PI);

            CloseHandle(hprocess);
        

        }

    }


}



std::string GetNameByHandle(HANDLE hprocess){
    HMODULE hmodule;
    DWORD sizeModule;
    char name[1024];
    if(EnumProcessModules(hprocess, &hmodule, sizeof(hmodule), &sizeModule)!= NULL){
        DWORD nbmodules = sizeModule / sizeof(DWORD);
        GetModuleBaseNameA(hprocess, hmodule,(LPSTR) name, sizeof(name));
    }
    std::string str(name);
    return str;
}

DWORD GetMemoryUsageByHandle(HANDLE hprocess){
    PROCESS_MEMORY_COUNTERS pmc;
    if(GetProcessMemoryInfo(hprocess, &pmc, sizeof(pmc)) != NULL){
        return (pmc.WorkingSetSize/ (1024 * 1024));
    }
}



void save_processinfo(std::vector<ProcessInfo>& P){
    std::ofstream  file("process.txt");
    for (auto &process : P) {
    
        file <<"PID: "<<process.GetPID()<<"\n";
        file<<"name: "<<process.GetName()<<"\n";
        file<<"Memory usage: "<<process.GetMemoryUsageMB()<<" MB"<<"\n";
    }
    file.close();

}
 


