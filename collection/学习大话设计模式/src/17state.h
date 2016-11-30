#ifndef SRC_17STATE_H_
#define SRC_17STATE_H_

#include <iostream>

using namespace std;

class Work;

class State {
public:
  virtual ~State() {
  }

  virtual void WriteProgram(Work& work) = 0;
};

class AfterNoonState : public State {
  void WriteProgram(Work& work) override;
};

class MidNoonState : public State {
public:
  void  WriteProgram(Work& work) override;
};

class ForeNoonState : public State {
public:
  void WriteProgram(Work& work) override;
};
#endif  // SRC_17STATE_
