#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <cassert>

using namespace std;

// ʵ��Ҫ�㣺
// 1��ʹ��ԭ�͹�������������һ��ϵͳ��ԭ����Ŀ���̶�ʱ�����Զ�̬�Ĵ��������١�
// 2��ʵ�ֿ�¡��������.NET�п���ʹ��Object���MemberwiseClone()������ʵ�ֶ����ǳ������ͨ�����л��ķ�ʽ��ʵ���������C++�о��ǿ������캯�������á�
// 3��Prototypeģʽͬ�����ڸ���������ʹ���ߺ;������ͣ��ױ��ࣩ֮�����Ϲ�ϵ����ͬ��Ҫ����Щ���ױ��ࡱӵ���ȶ��Ľӿڡ�

// Ч����
// 1�����Կͻ������˾���Ĳ�Ʒ�࣬��˼����˿ͻ�֪�������ֵ���Ŀ��
// 2�� Prototypeģʽ����ͻ�ֻͨ��ע��ԭ��ʵ���Ϳ��Խ�һ�������Ʒ�ಢ�뵽ϵͳ�У��ͻ�����������ʱ�̽�����ɾ��ԭ�͡�
// 3�����������๹�죬Prototypeģʽ�ǿ�¡һ��ԭ�Ͷ��������󹤳���������һ��������������Ҫһ��������Ʒ��ƽ�е�Creater���Ρ�
// 4��Portotypeģʽ���и�һ��Ӧ�������̬�����¹��ܵ�����������Prototype�Ķ����Խϸߣ����Ժ����׶�̬�����¹��ܶ���Ӱ����ϵͳ��
// 5����Ʒ�಻��Ҫ�ǵ����κ�����ȷ���ĵȼ��ṹ����ΪPrototypeģʽ�������κεĵȼ��ṹ
// 6��Prototypeģʽ������Ҫȱ�����ÿһ��������䱸һ����¡���������������¡������Ҫ����Ĺ��ܽ���ͨ�̿��ǣ����ȫ�µ�����˵���Ǻ��ѣ��������е�����и���ʱ����һ���Ǽ����׵��¡�

// �����ԣ�
// 1. ��һ��ϵͳӦ�ö��������Ĳ�Ʒ���������ɺͱ�ʾʱ����Ҫʹ��ԭ��ģʽ
// 2. ��Ҫʵ����������������ʱ��ָ��ʱ����ͨ����̬װ��
// 3. Ϊ�˱��ⴴ��һ�����Ʒ����ƽ�еĹ�������ʱ
// 4. ��һ�����ʵ��ֻ���м�����ͬ״̬����е�һ��ʱ��������Ӧ��Ŀ��ԭ�Ͳ���¡���ǿ��ܱ�ÿ���ú��ʵ�״̬�ֹ�ʵ�������������һЩ��

// Prototypeģʽ��Builderģʽ��AbstractFactoryģʽ����ͨ��һ���ࣨ����ʵ������ר�Ÿ������Ĵ����������������󣩣�
// ����֮��������ǣ�Builderģʽ���ڸ��Ӷ����һ��������������ֱ�ӷ��ض��󣩣�AbstractFactoryģʽ���ڲ�������໥������Ķ��󣬶�Prototypeģʽ���ڴ��������Լ��������ࡣ

// ʵ����Clone�������ǵ���c++�Ŀ����������������µĶ�����ȿ�����
 
class Resume {
public:
  Resume(char* name, int age) {
    if (name == NULL) {
      name_ = new char[1];
      name_[0] = '\0';
    } else {
      name_ = new char[strlen(name) + 1];
      strcpy(name_, name);
    }
    age_ = age;
  }

  Resume(const Resume& rhs) {
    name_ = new char[strlen(rhs.name_) + 1];
    strcpy(name_, rhs.name_);
    age_ = rhs.age_;
  }

  virtual ~Resume() {
    if (name_ != NULL) {
      delete name_;
      name_ = NULL;
      age_ = 0;
    }
  }

  virtual Resume* Clone() const = 0;
  
  void Show() {
    cout << name_ << " : " << age_ << endl;
  }

protected:
  char* name_;
  int age_;
};

class ResumeA : public Resume {
public:
  ResumeA(char* name, int age)
    : Resume(name, age) {
  }

  ResumeA(const ResumeA& rhs)
    : Resume(rhs) {
  }
  
  Resume* Clone() const override {
    return new ResumeA(*this);
  }
};

class ResumeB : public Resume {
public:
  ResumeB(char* name, int age)
    : Resume(name, age) {
  }

  ResumeB(const ResumeB& rhs)
    : Resume(rhs) {
  }

  Resume* Clone() const override {
    return new ResumeB(*this);
  }
};


class ResumeManager {
public:
  ResumeManager() {
  }

  ~ResumeManager() {
    for (Resume* resume : resumes_) {
      delete resume;
    }
    resumes_.clear();
  }

  void Add(Resume* resume) {
    resumes_.push_back(resume);
  }

  Resume* Get(int index) const {
    assert(index >= 0);
    assert(index < resumes_.size());
    return resumes_[index];
  }

  void Remove(int index) {
    delete resumes_[index];
    resumes_.erase(resumes_.begin() + index);
  }

  size_t Size() const {
    return resumes_.size();
  }

private:
  vector<Resume*> resumes_;
};

int main11() {
  ResumeManager resume_manager;

  Resume* r1 = new ResumeA("A", 14);
  Resume* r2 = new ResumeB("B", 15);

  resume_manager.Add(r1);
  resume_manager.Add(r2);

  resume_manager.Get(0)->Show();
  resume_manager.Get(1)->Show();

  Resume* r3 = resume_manager.Get(0)->Clone();
  Resume* r4 = resume_manager.Get(1)->Clone();

  //ɾ��r1,r2  
  resume_manager.Remove(0);
  resume_manager.Remove(0);  // ע��ɾ����Ԫ�ظ����ͻ�ı䡣

  //������Զ�r3,r4��Ӱ��  
  r3->Show();
  r4->Show();

  delete r3;
  delete r4;

  return 0;
}
