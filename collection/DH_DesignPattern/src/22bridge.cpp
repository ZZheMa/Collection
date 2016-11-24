#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

// ������Ӳ�û�����ֳ����Ž�ģʽ����ɫ�����ǺͲ���ģʽ��������ơ�

// 1.�����ϣ���ڳ��������ʵ�ֲ���֮����һ���̶��İ󶨹�ϵ��Ҳ���Ǽ̳й�ϵ��
// ������Ǵ��������̶ֹ��İ󶨹�ϵ���Ժ󣬾Ϳ��Է�����ڳ��󲿷��л���ͬ��ʵ�ֲ��֣�
// 2.���ϣ����ĳ����Լ�����ʵ�ֶ�Ӧ�ÿ���ͨ����������ķ����������䣻�����ʹ���Ž�ģʽ��ʹ�ü̳�ȥʵ��ʱ��
// �ڳ����������һ�����������ڶ�Ӧ��ʵ������Ҳ��Ҫ����Ӧ�ĸĶ�������ʵ�ֲ���������ϵ�Ҫ��
// 3.���Ҫ���һ�������ʵ�ֲ��ֵ��޸ĶԿͻ�������Ӱ�죬���ͻ��Ĵ��벻��Ҫ���±��롣
// 4.�����Կͻ���ȫ���س����ʵ�ֲ��֣�
// 5.���һ�������ж���仯���ص�ʱ��ͨ��������Щ�仯���أ�����������ʵ�֣��޸�Ϊ��������
// 6.���ĳ���仯�����ڶ�������й���ʱ�����Գ��������仯���أ�Ȼ��ʵ����Щ��ͬ�ı仯���ء�

class HandsetSoft {
public:
  virtual void Run() = 0;
};

class HandsetGame : public HandsetSoft {
public:
  void Run() override {
    cout << "Game" << endl;
  }
};

class HandsetAddressList : public HandsetSoft {
public:
  void Run() override {
    cout << "Address List" << endl;
  }
};

class HandsetBrand {
public:
  HandsetBrand(HandsetSoft* soft)
    : soft_(soft) {
  }

  void Run() {
    soft_->Run();
  }

protected:
  HandsetSoft* soft_;
};

class HandsetBrandN : public HandsetBrand {
public:
  HandsetBrandN(HandsetSoft* soft)
    : HandsetBrand(soft) {
  }
};

class HandsetBrandM : public HandsetBrand {
public:
  HandsetBrandM(HandsetSoft* soft)
    : HandsetBrand(soft) {
  }
};

int main22() {
  HandsetGame* game = new HandsetGame;
  HandsetAddressList* address_list = new HandsetAddressList;

  HandsetBrandM* brand_m1 = new HandsetBrandM(game);
  brand_m1->Run();

  HandsetBrandM* brand_m2 = new HandsetBrandM(address_list);
  brand_m2->Run();

  HandsetBrandN* brand_n1 = new HandsetBrandN(game);
  brand_n1->Run();

  HandsetBrandN* brand_n2 = new HandsetBrandN(address_list);
  brand_n2->Run();

  delete brand_n2;
  delete brand_n1;
  delete brand_m2;
  delete brand_m1;
  delete address_list;
  delete game;

  return 0;
}
