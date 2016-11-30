#include <iostream>
#include <string>
#include <vector>
#include <list>

#include "17work.h"

using namespace std;

void Test() {
  Work work;
  work.set_time_hour(10);
  work.WriteProgram();

  work.set_time_hour(13);
  work.WriteProgram();

  work.set_time_hour(15);
  work.WriteProgram();

  work.set_time_hour(16);
  work.set_task_finished(true);
  work.WriteProgram();
}

int main17() {
  Test();

  return 0;
}