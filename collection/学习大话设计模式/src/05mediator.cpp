#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

class Country;

// Mediator: United Nations
class UnitedNations {
public:
  virtual void TransmitMessage(const string& message, Country* country) = 0;
};

// Country
class Country {
public:
  Country(UnitedNations* mediator)
    : mediator_(mediator) {
  }

  virtual void SendMessage(const string& message) = 0;
  virtual void GetMessage(const string& message) = 0;

protected:
  UnitedNations* mediator_;
};

// USA
class USA : public Country {
public:
  USA(UnitedNations* mediator)
    : Country(mediator) {
  }

  void SendMessage(const string& message) override {
    mediator_->TransmitMessage(message, this);
  }

  void GetMessage(const string& message) override {
    cout << "USA received: " << message << endl;
  }
};

// Iraq
class Iraq : public Country {
public:
  Iraq(UnitedNations* mediator)
    : Country(mediator) {
  }

  void SendMessage(const string& message) override {
    mediator_->TransmitMessage(message, this);
  }

  void GetMessage(const string& message) override {
    cout << "Iraq received: " << message << endl;
  }
};

// UNSecurityCouncil 
class UNSecurityCouncil : public UnitedNations {
public:
  UNSecurityCouncil()
    : usa_(NULL)
    , iraq_(NULL) {
  }

  void set_usa(USA* usa) { usa_ = usa; }
  void set_iraq(Iraq* iraq) { iraq_ = iraq; }

  void TransmitMessage(const string& message, Country* country) override {
    if (country == usa_) {
      iraq_->GetMessage(message);
    } 
    if (country == iraq_) {
      usa_->GetMessage(message);
    }
  }

private:
  USA* usa_;
  Iraq* iraq_;
};

int main05() {
  UNSecurityCouncil* mediator = new UNSecurityCouncil();
  USA* usa = new USA(mediator);
  Iraq* iraq = new Iraq(mediator);
  mediator->set_iraq(iraq);
  mediator->set_usa(usa);
  usa->SendMessage("What's wrong with you?");
  iraq->SendMessage("It's none of your business!");
  delete iraq;
  delete usa;
  delete mediator;

  return 0;
}