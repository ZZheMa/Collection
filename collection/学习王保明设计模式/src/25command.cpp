#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

// Command模式也叫命令模式，是行为设计模式的一种。Command模式通过被称为Command的类封装了对目标对象的调用行为以及调用参数。

// 在面向对象的程序设计中，一个对象调用另一个对象，一般情况下的调用过程是：创建目标对象实例，设置调用参数，调用目标对象的方法。
// 但在有些情况下有必要使用一个专门的类对这种调用过程加以封装，我们把这种专门的类称作command类。
// 整个调用过程比较繁杂，或者存在多处这种调用。这时，使用Command类对该调用加以封装，便于功能的再利用。
// 调用前后需要对调用参数进行某些处理。调用前后需要进行某些额外处理，比如日志，缓存，记录历史操作等。

// 适用于：
// 是将一个请求封装为一个对象，从而使你可用不同的请求对客户端进行参数化；对请求排队或记录请求日志，以及支持可撤销的操作。

// command模式主要有五个角色，执行者，请求者，命令抽象，具体命令，客户端。

// 如何实现一个command模式：command模式是将行为（命令）参数化，可以将每个动作变成一个对象保存下来，所以首先从执行者Doctor下手。
// 因为是将行为参数化，所以将Doctor的所有行为动作方法，找出来TreatEye和TreatNose，然后将
// 这两个行为进行参数化，也就是将这两个方法抽象出一个命令command来。
// 然后就可以定义command，command要保存Doctor，然后执行Doctor的方法。
// 定义好command和执行者后，就需要定义一个请求者，请求者其实就是管理这些command，以及调用command执行方法的角色。

//---------------------------------------------------
// 面向接口编程，定义接口。执行者以及命令的抽象。

class Doctor {
public:
  virtual ~Doctor() {}

  virtual void TreatEye() = 0;
  virtual void TreatNose() = 0;
};

class Command {
public:
  Command(Doctor* doctor)
    : doctor_(doctor) {
  }

  virtual void Treat() = 0;

protected:
  Doctor* doctor_;
};

//---------------------------------------------------
// 具体的执行者。

class InternDoctor : public Doctor {
public:
  void TreatEye() override {
    cout << "Intern treats eye!" << endl;
  }

  void TreatNose() override {
    cout << "Intern treats nose!" << endl;
  }
};

class SpecialistDoctor : public Doctor {
public:
  void TreatEye() override {
    cout << "Specialist treats eye!" << endl;
  }

  void TreatNose() override {
    cout << "Specialist treats nose!" << endl;
  }
};

//------------------------------------------------------
// 具体的命令。

class TreatEyeCommand : public Command {
public:
  TreatEyeCommand(Doctor* doctor)
    : Command(doctor) {
  }

  void Treat() override {
    doctor_->TreatEye();
  }
};

class TreatNoseCommand : public Command {
public:
  TreatNoseCommand(Doctor* doctor)
    : Command(doctor) {
  }

  void Treat() override {
    doctor_->TreatNose();
  }
};

//------------------------------------------------------
// 接受者，也就是请求者。

class BeautyNurse {
public:
  BeautyNurse(Command* command)
    : command_(command) {
  }

  ~BeautyNurse() {
    delete command_;
    command_ = NULL;
  }

  void SubmitCase() {
    command_->Treat();
  }

private:
  Command* command_;
};

class HeadNurse {
public:
  HeadNurse() {}
  ~HeadNurse() {
    for (Command* command : commands_) {
      delete command;
    }
    commands_.clear();
  }

  void ReceiveCase(Command* command) {
    commands_.push_back(command);
  }

  void SubmitCase() {
    for (Command* command : commands_) {
      command->Treat();
    }
  }

private:
  list<Command*> commands_;
};

//------------------------------------------------------
// 客户端。

int main25() {
  Doctor* intern = new InternDoctor;
  Doctor* specialist = new SpecialistDoctor;

  cout << "Beauty nurse: " << endl;
  BeautyNurse beauty_nurse(new TreatEyeCommand(intern));
  beauty_nurse.SubmitCase();

  cout << "----------------------------" << endl;

  cout << "Head nurse: " << endl;
  HeadNurse head_nurse;
  head_nurse.ReceiveCase(new TreatEyeCommand(intern));
  head_nurse.ReceiveCase(new TreatEyeCommand(specialist));
  head_nurse.ReceiveCase(new TreatNoseCommand(intern));
  head_nurse.ReceiveCase(new TreatNoseCommand(specialist));
  head_nurse.SubmitCase();

  delete specialist;
  delete intern;

  return 0;
}
