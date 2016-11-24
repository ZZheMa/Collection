#include "17state.h"
#include <iostream>
#include "17work.h"

using namespace std;

// ���ã���һ�����������״̬�ı�ʱ����ı�����Ϊ����������������Ǹı������ࡣ

// �������м���״̬ʱ����ͬ״̬ʱ�в�ͬ�ı��֣�Ϊ�˱��⸴�ӵ�ifelse�߼�����ÿ��״̬���߼�������װ���Լ���ʵ���У�����д���߼������Ĵ��롣

// ��ʵ���ǽ�������Ϊ���󻯣�command�ǽ�������Ϊ���󻯡�

// ��һ���������Ϊȡ��������״̬������������������ʱ�̸���״̬�ı�������Ϊʱ���Ϳ��Կ���ʹ��״̬ģʽ��

// work���Լ�������state��ͨ��state�������ж����ı�work��state��
// ÿ��state����һ����֧����֧�ͷ�֧�����������Ǹ��������ˡ�Ȼ����ܹ������������ж�����

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
