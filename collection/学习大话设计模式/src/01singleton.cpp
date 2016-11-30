#include <iostream>
#include <string>

using namespace std;

// http://www.jellythink.com/archives/82
// ���ڣ����ܿ���һ������ϵͳ�����������ڵĲ����������ģ��������һ����־���ܣ�
// ��ʵ�ʿ��������У���ר����һ����־ģ�飬����д��־��������ϵͳ���κεط���
// ���Ƕ��п���Ҫ������־ģ���еĺ���������д��־����ô����ι���һ����־ģ���ʵ���أ�
// �ѵ���ÿ��newһ����־ģ��ʵ����д����־����delete����Ҫ������������ô�ɵġ�
// ��C++�У����Թ���һ����־ģ���ȫ�ֱ�������ô���κεط��Ͷ��������ˣ��ǵģ�����
// ���ǣ������ڵĿ������ŵ�C++����淶�ǲ���Google�ı���淶�ġ�
// ȫ�ֱ�������Ŀ�����ܲ��þͲ��õģ�����һ����ʱը������һ������ȫ�������ر����ڶ��̳߳����У�
// ���кܶ�Ĳ���Ԥ���ԣ�ͬʱ��ʹ��ȫ�ֱ�����Ҳ�������������ķ�װԭ��
// ���ԣ��ڴ�������������Java��C#�У���û�д����ȫ�ֱ�������ô����������Ľ�������־���⣬����Ҫ�������ģʽ�еĵ���ģʽ��
// ��Ϊ����ģʽ����GOF�ġ����ģʽ���ɸ��������������Ļ�������������˵�ģ�
// ��֤һ����ֻ��һ��ʵ�������ṩһ����������ȫ�ַ��ʵ㡣���ȣ���Ҫ��֤һ����ֻ��һ��ʵ����
// �����У�Ҫ����һ��ʵ�����ͱ��������Ĺ��캯������ˣ�Ϊ�˷�ֹ���ⲿ������Ĺ��캯��������ʵ����
// ��Ҫ�����캯���ķ���Ȩ�ޱ��Ϊprotected��private�������Ҫ�ṩҪ��ȫ�ַ��ʵ㣬����Ҫ�����ж���һ��static������
// ���������ڲ�Ψһ�����ʵ������˼�����ף�ʹ��UML��ͼ��ʾ���¡�

//------------------------------------------------------------------------

// ����ʽ���������ʱ������˳�ʼ��
class Singleton1 {
public:
  static Singleton1* GetInstance() {
    return instance_;
  }

  static void DestroyInstance() {
    if (instance_ != NULL) {
      delete instance_;
      instance_ = NULL;
    }
  }

  void Test() {
    cout << ++i << endl;
  }

private:
  Singleton1() : i(0) {}

private:
  static Singleton1* instance_;
  int i;
};

Singleton1* Singleton1::instance_ = new Singleton1();

// ����ʽ�������ʱ����ʼ��
class Singleton2 {
public:
  static Singleton2* GetInstance() {
    if (instance_ == NULL) {
      instance_ = new Singleton2();
    }
    return instance_;
  }

  static void DestroyInstance() {
    if (instance_ != NULL) {
      delete instance_;
      instance_ = NULL;
    }
  }

  void Test() {
    cout << ++i << endl;
  }

private:
  Singleton2() : i(0) {
  }

private:
  static Singleton2* instance_;
  int i;
};

Singleton2* Singleton2::instance_ = NULL;

int main01() {
  Singleton1* s11 = Singleton1::GetInstance();
  s11->Test();
  Singleton1* s12 = Singleton1::GetInstance();
  s12->Test();

  Singleton2* s21 = Singleton2::GetInstance();
  s21->Test();
  Singleton2* s22 = Singleton2::GetInstance();
  s22->Test();

  if (s11 == s12) {
    cout << "true" << endl;
  }

  if (s21 == s22) {
    cout << "true" << endl;
  }

  Singleton1::DestroyInstance();
  Singleton2::DestroyInstance();

  return 0;
}