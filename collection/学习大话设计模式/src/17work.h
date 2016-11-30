#ifndef SRC_17WORK_H_
#define SRC_17WORK_H_

#include <list>
#include "17state.h"

class Work {
public:
  Work()
    : task_finished_(false)
    , time_hour_(0) {
    set_state(new ForeNoonState);
  }

  ~Work() {
    for (State* state : states_) {
      delete state;
      std::cout << "destrcut" << std::endl;
    }
  }

  void WriteProgram() {
    state_->WriteProgram(*this);
  }

  void set_state(State* state) { 
    state_ = state;
    states_.push_back(state);
  }

  int time_hour() const { return time_hour_; }
  void set_time_hour(int time_hour) { time_hour_ = time_hour; }

  bool task_finished() const { return task_finished_; }
  void set_task_finished(bool task_finished) { task_finished_ = task_finished; }

private:
  std::list<State*> states_;
  State* state_;
  bool task_finished_;
  int time_hour_;
};

#endif  // SRC_17WORK_
