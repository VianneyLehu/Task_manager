
#include <tlhelp32.h>
#include <vector>


template <typename T>
class Snapshot{
    public:
        virtual std::vector<T> GenerateSnapshot(std::vector<T> SnapshotList) = 0;
        virtual void DisplaySnapshot(const std::vector<T>&snapshotList) = 0;
};



class ProcessSnapshot : public Snapshot <PROCESSENTRY32> {
    public: 
        std::vector<PROCESSENTRY32> GenerateSnapshot(std::vector<PROCESSENTRY32> processList) override;
        void DisplaySnapshot(const std::vector<PROCESSENTRY32>& processList) override;
};

class ModuleSnapshot : public Snapshot <MODULEENTRY32> {
    public: 
        std::vector<MODULEENTRY32> GenerateSnapshot(std::vector<MODULEENTRY32> ModuleList) override;
        void DisplaySnapshot(const std::vector<MODULEENTRY32>& ModuleList) override;
};
class ThreadSnapshot : public Snapshot <THREADENTRY32> {
    public: 
        std::vector<THREADENTRY32> GenerateSnapshot(std::vector<THREADENTRY32> ThreadList) override;
        void DisplaySnapshot(const std::vector<THREADENTRY32>& ThreadList) override;
};





std::vector<PROCESSENTRY32> GenerateProcessSnap(std::vector <PROCESSENTRY32> processList);

std::vector<MODULEENTRY32> GenerateModuleSnap(std::vector <MODULEENTRY32> moduleList);

std::vector<THREADENTRY32> GenerateThreadSnap(std::vector <THREADENTRY32> threadList);




void DisplayProcess(std::vector<PROCESSENTRY32> processList);

void DisplayModule(std::vector<MODULEENTRY32> processList);

void DisplayThread(std::vector<THREADENTRY32> processList);