#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

// 外观模式： 其实就是化零为整的思想，将多个对象集成一个子系统，对外提供一个接口，减少了客户端和各个对象的直接接触。

class Stock1 {
public:
  void Buy() {
    cout << "股票1买了" << endl;
  }

  void Sell() {
    cout << "股票1卖了" << endl;
  }
};

class Stock2 {
public:
  void Buy() {
    cout << "股票2买了" << endl;
  }

  void Sell() {
    cout << "股票2卖了" << endl;
  }
};

class NationDebt {
public:
  void Buy() {
    cout << "国债买了" << endl;
  }

  void Sell() {
    cout << "国债卖了" << endl;
  }
};

class Realty {
public:
  void Buy() {
    cout << "房地产买了" << endl;
  }

  void Sell() {
    cout << "房地产卖了" << endl;
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