#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

// Dependence Inversion Principle.
// 高层模块不应该依赖低层模块，二者都应该依赖其抽象；抽象不应该依赖细节；细节应该依赖抽象。 

// 让Computer框架和具体的厂商进行解耦合。Computer依赖抽象Cpu等，而不依赖具体的某个厂商的Cpu。
// 所以无论换成哪个厂商的Cpu都不会影响Computer框架。

class Cpu {
public:
  virtual void Work() = 0;
};

class Memory {
public:
  virtual void Work() = 0;
};

class HardDisk {
public:
  virtual void Work() = 0;
};

class Computer3 {
public:
  Computer3(Cpu* cpu, Memory* memory, HardDisk* hard_disk)
    : cpu_(cpu)
    , memory_(memory)
    , hard_disk_(hard_disk) {
  }

  ~Computer3() {
    if (cpu_ != NULL) {
      delete cpu_;
    }

    if (memory_ != NULL) {
      delete memory_;
    }

    if (hard_disk_ != NULL) {
      delete hard_disk_;
    }
  }

  void Work() {
    cpu_->Work();
    memory_->Work();
    hard_disk_->Work();
  }

private:
  Cpu* cpu_;
  Memory* memory_;
  HardDisk* hard_disk_;
};

class IntelCpu : public Cpu {
public:
  void Work() override {
    cout << "I am Intel CPU!" << endl;
  }
};

class XSHardDisk : public HardDisk {
public:
  void Work() override {
    cout << "I am XS Hard Disk!" << endl;
  }
};

class JSDMemory : public Memory {
public:
  void Work() override {
    cout << "I am JSD Memory" << endl;
  }
};

int main03() {
  Computer3 computer(new IntelCpu, new JSDMemory, new XSHardDisk);
  computer.Work();

  return 0;
}
