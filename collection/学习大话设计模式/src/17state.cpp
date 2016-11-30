#include "17state.h"
#include <iostream>
#include "17work.h"

using namespace std;

// 作用：当一个对象的内在状态改变时允许改变其行为，这个对象看起来像是改变了其类。

// 当对象有几种状态时，不同状态时有不同的表现，为了避免复杂的ifelse逻辑，将每个状态的逻辑单独封装在自己的实现中，容易写出逻辑清晰的代码。

// 其实就是将条件行为对象化，command是将命令行为对象化。

// 当一个对象的行为取决于它的状态，并且它必须在运行时刻根据状态改变它的行为时，就可以考虑使用状态模式。

// work把自己传给了state，通过state的条件判断来改变work的state。
// 每个state都有一个分支，分支和分支连起来，就是个决策树了。然后就能构成整个条件判断树。

void AfterNoonState::WriteProgram(Work& work) {
  if (work.task_finished()) {
    cout << "finished" << endl;
  } else {
    cout << "work overtime" << endl;
  }
}

void  MidNoonState::WriteProgram(Work& work) {
  if (work.time_hour() < 14) {
    cout << "midnoonstate" << endl;
  } else {
    work.set_state(new AfterNoonState);
    work.WriteProgram();
  }
}

void ForeNoonState::WriteProgram(Work& work) {
  if (work.time_hour() < 12) {
    cout << "forenoonstate" << endl;
  } else {
    work.set_state(new MidNoonState);
    work.WriteProgram();
  }
}
