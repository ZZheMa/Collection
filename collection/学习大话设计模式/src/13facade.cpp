#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

// ���ģʽ�� ��ʵ���ǻ���Ϊ����˼�룬��������󼯳�һ����ϵͳ�������ṩһ���ӿڣ������˿ͻ��˺͸��������ֱ�ӽӴ���

class Stock1 {
public:
  void Buy() {
    cout << "��Ʊ1����" << endl;
  }

  void Sell() {
    cout << "��Ʊ1����" << endl;
  }
};

class Stock2 {
public:
  void Buy() {
    cout << "��Ʊ2����" << endl;
  }

  void Sell() {
    cout << "��Ʊ2����" << endl;
  }
};

class NationDebt {
public:
  void Buy() {
    cout << "��ծ����" << endl;
  }

  void Sell() {
    cout << "��ծ����" << endl;
  }
};

class Realty {
public:
  void Buy() {
    cout << "���ز�����" << endl;
  }

  void Sell() {
    cout << "���ز�����" << endl;
  }
};

class Fund {
public:
  Fund() {
  }

  void Buy() {
    stock1_.Buy();
    stock2_.Buy();
    nation_debt_.Buy();
    realty_.Buy();
  }

  void Sell() {
    stock1_.Sell();
    stock2_.Sell();
    nation_debt_.Sell();
    realty_.Sell();
  }

private:
  Stock1 stock1_;
  Stock2 stock2_;
  NationDebt nation_debt_;
  Realty realty_;
};

int main13() {
  Fund fund;
  fund.Buy();
  cout << "------------------------------" << endl;
  fund.Sell();

  return 0;
}