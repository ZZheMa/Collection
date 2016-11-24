#include <iostream>
#include <string>
#include <list>

using namespace std;

class Barbecuer {
public:
  void BakeMutton() {
    cout << "Bake mutton" << endl;
  }

  void BakeChickenWing() {
    cout << "Bake chicken wing" << endl;
  }
};

class Command {
public:
  Command(Barbecuer barbecuer, string order)
    : barbecuer_(barbecuer)
    , order_(order){
  }

  string order() { return order_; }

  virtual ~Command() {
  }

  virtual void ExecuteCommand() = 0;

protected:
  Barbecuer barbecuer_;
  string order_;
};

class BakeMuttonCommand : public Command {
public:
  BakeMuttonCommand(Barbecuer barbecuer)
    : Command(barbecuer, "mutton") {
  }

  void ExecuteCommand() override {
    barbecuer_.BakeMutton();
  }
};

class BakeChickenWingCommand : public Command {
public:
  BakeChickenWingCommand(Barbecuer barbecuer)
    : Command(barbecuer, "chicken wing") {
  }

  void ExecuteCommand() override {
    barbecuer_.BakeChickenWing();
  }
};

class Waiter {
public:
  Waiter() {}

  ~Waiter() {
    for (Command* command : OrderList) {
      delete command;
    }
    OrderList.clear();
  }

  void SetOrder(Command* command) {
    if (command->order() == "mutton" && mutton_count_ == 0) {
      cout << "The mutton has been sold up!" << endl;
    } else if (command->order() == "chicken wing" && chicken_wing_count_ == 0) {
      cout << "The chicken wing has been sold up!" << endl;
    } else {
      if (command->order() == "mutton") {
        mutton_count_--;
      } else {
        chicken_wing_count_--;
      }

      OrderList.push_back(command);
      cout << "Add order : " << command->order() << endl;
    }
  }

  void CancelOrder(Command* command) {
    list<Command*>::iterator it = find(OrderList.begin(), OrderList.end(), command);
    if (it == OrderList.end()) {
      return;
    }
    cout << "Delete order : " << command->order() << endl;
    delete command;
    OrderList.erase(it);
  }

  void Notify() {
    for (Command* Command : OrderList) {
      Command->ExecuteCommand();
    }
  }

private:
  static int mutton_count_;
  static int chicken_wing_count_;

private:
  list<Command*> OrderList;
};

int Waiter::mutton_count_ = 2;
int Waiter::chicken_wing_count_ = 2;

int main02() {
  Barbecuer barbecuer;
  Waiter waiter;
  waiter.SetOrder(new BakeChickenWingCommand(barbecuer));
  waiter.SetOrder(new BakeChickenWingCommand(barbecuer));
  waiter.SetOrder(new BakeChickenWingCommand(barbecuer));
  waiter.SetOrder(new BakeMuttonCommand(barbecuer));
  waiter.SetOrder(new BakeMuttonCommand(barbecuer));
  waiter.SetOrder(new BakeMuttonCommand(barbecuer));
  waiter.Notify();
  return 0;
}