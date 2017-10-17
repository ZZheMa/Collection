#include <iostream>
#include <string>
#include <list>
#include <cassert>

int main02() {
  //const char* kStrArray[100] = {
  //  "1",
  //  "2"
  //};

  const char* kStrArray[100] = { NULL };

  for (int i = 0; i < 99; ++i) {
    if (kStrArray[i] == NULL) {
      std::cout << "NULL" << std::endl;
      continue;
    }

    std::cout << kStrArray[i] << std::endl;
  }

  kStrArray[0] = "1";
  std::cout << kStrArray[0] << std::endl;

  //kStrArray[0][1] = 'a';  // error C3892: 'kStrArray' : you cannot assign to a variable that is const.

  const char** kStrArrayPtr = NULL;  // const ����ǰ�棬Ҳ���ǣ�**p���ǲ��ܸı�ġ�

  //char* const * kStrArrayPtr = NULL;  // (*p)�ǲ��ܸı�ġ�
  //char** const kStrArrayPtr = NULL;  // p�ǲ��ܸı�ġ�

  kStrArrayPtr = kStrArray;

  kStrArrayPtr[0] = "2";
  std::cout << kStrArray[0] << std::endl;

  return 0;
}
