#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

// RequestType

enum RequestType {
  RT_ASK_FOR_LEAVE = 0,
  RT_RAISE_SALARY,
  RT_NONE
};

// Request

class Request {
public:
  Request(RequestType request_type, const string& content, int count)
    : request_type_(request_type)
    , content_(content)
    , count_(count) {
  }

  RequestType request_type() const { return request_type_; }
  string content() const { return content_; }
  int count() const { return count_; }

private:
  RequestType request_type_;
  string content_;
  int count_;
};

// Manager

class Manager {
public:
  Manager(const string& name)
    : name_(name)
    , superier_(NULL) {
  }

  virtual ~Manager() {}

  virtual void HandleRequest(const Request& request) = 0;

  void set_superier(Manager* superier) { superier_ = superier; }

protected:
  string name_;
  Manager* superier_;
};

// CommonManager

class CommonManager : public Manager {
public:
  CommonManager(const string& name)
    : Manager(name) {
  }

  void HandleRequest(const Request& request) override {
    if (request.request_type() == RT_ASK_FOR_LEAVE && request.count() <= 3) {
      cout << name_ << ": " << request.content() << request.count() << " days. Approve!" << endl;
    } else {
      if (superier_ != NULL) {
        superier_->HandleRequest(request);
      }
    }
  }
};

// Majordomo

class Majordomo : public Manager {
public:
  Majordomo(const string& name)
    : Manager(name) {
  }

  void HandleRequest(const Request& request) override {
    if (request.request_type() == RT_ASK_FOR_LEAVE) {
      cout << name_ << ": " << request.content() << request.count() << " days. Approve!" << endl;
    } else if (request.request_type() == RT_RAISE_SALARY && request.count() <= 500) {
      cout << name_ << ": " << request.content() << request.count() << " yuan. Approve!" << endl;
    } else {
      if (superier_ != NULL) {
        superier_->HandleRequest(request);
      }
    }
  }
};

// GeneralManager

class GeneralManager : public Manager {
public:
  GeneralManager(const string& name)
    : Manager(name) {
  }

  void HandleRequest(const Request& request) override {
    if (request.request_type() == RT_ASK_FOR_LEAVE) {
      cout << name_ << ": " << request.content() << request.count() << " days. Approve!" << endl;
    } else if (request.request_type() == RT_RAISE_SALARY && request.count() <= 2000) {
      cout << name_ << ": " << request.content() << request.count() << " yuan. Approve!" << endl;
    } else if (request.request_type() == RT_RAISE_SALARY && request.count() > 2000) {
      cout << name_ << ": " << request.content() << request.count() << " yuan. Reject!" << endl;
    } else {
      if (superier_ != NULL) {
        superier_->HandleRequest(request);
      }
    }
  }
};

int main03() {
  CommonManager* common_manager = new CommonManager("Zhang San");
  Majordomo* majordomo = new Majordomo("Li si");
  GeneralManager* general_manager = new GeneralManager("Wang wu");
  common_manager->set_superier(majordomo);
  majordomo->set_superier(general_manager);

  Request request1(RT_ASK_FOR_LEAVE, "Xiao Cai asked for leave for ", 2);
  common_manager->HandleRequest(request1);
  cout << "--------------------------------------------------------------" << endl;

  Request request2(RT_ASK_FOR_LEAVE, "Xiao Cai asked for leave for ", 5);
  common_manager->HandleRequest(request2);
  cout << "--------------------------------------------------------------" << endl;

  Request request3(RT_RAISE_SALARY, "Xiao Cai asked for raise salary ", 300);
  common_manager->HandleRequest(request3);
  cout << "--------------------------------------------------------------" << endl;

  Request request4(RT_RAISE_SALARY, "Xiao Cai asked for raise salary ", 1000);
  common_manager->HandleRequest(request4);
  cout << "--------------------------------------------------------------" << endl;

  Request request5(RT_RAISE_SALARY, "Xiao Cai asked for raise salary ", 5000);
  common_manager->HandleRequest(request5);
  cout << "--------------------------------------------------------------" << endl;

  delete general_manager;
  delete majordomo;
  delete common_manager;

  return 0;
}