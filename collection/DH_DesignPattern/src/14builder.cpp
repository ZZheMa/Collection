#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

// builderģʽ��һ����Ʒ�ľ��彨����̴�һ����Ʒ�����������ŵ�builder��ȥ���죬
// Ҳ���ǽ�һ������Ķಽ����ŵ�builder����ȥʵ�֣����Ĺ���ʱ���Ͳ��ø�������ֱ࣬��
// �̳�builder�Ϳ����ˣ����Ͽ���-���ԭ��
// �Ѳ�Ʒ�ŵ�builder�У���ָ���߰���˳�������幹�죬��������ˮ�߲����Ĺ�����

class Product {
public:
  Product() {
  }

  void Add(string part) {
    parts_.push_back(part);
  }

  void Show() {
    cout << "Product: ";
    for (const string& part : parts_) {
      cout << " " << part << " ";
    }
    cout << endl;
  }

private:
  vector<string> parts_;
};

class Builder {
public:
  virtual void BuildStep1() = 0;
  virtual void BuildStep2() = 0;
  virtual Product* GetResult() = 0;
};

class ConcreteBuilderA : public Builder {
public:
  ConcreteBuilderA() {
    product_ = new Product;
  }

  void BuildStep1() override {
    product_->Add("partA");
  }

  void BuildStep2() override {
    product_->Add("partB");
  }

  Product* GetResult() override {
    return product_;
  }

private:
  Product* product_;
};

class ConcreteBuilderB : public Builder {
public:
  ConcreteBuilderB() {
    product_ = new Product;
  }

  void BuildStep1() override {
    product_->Add("partX");
  }

  void BuildStep2() override {
    product_->Add("partY");
  }

  Product* GetResult() override {
    return product_;
  }

private:
  Product* product_;
};

class Director {
public:
  void Construct(Builder* builder) {
    builder->BuildStep1();
    builder->BuildStep2();
  }
};

int main14() {
  Director director;
  Builder* concrete_builder_a = new ConcreteBuilderA;
  Builder* concrete_builder_b = new ConcreteBuilderB;

  director.Construct(concrete_builder_a);
  director.Construct(concrete_builder_b);

  Product* product_a = concrete_builder_a->GetResult();
  Product* product_b = concrete_builder_b->GetResult();

  product_a->Show();
  product_b->Show();

  delete product_b;
  delete product_a;
  delete concrete_builder_b;
  delete concrete_builder_a;

  return 0;
}