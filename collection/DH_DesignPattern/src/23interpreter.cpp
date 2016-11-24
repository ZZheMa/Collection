#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

// �����ԣ�
// ����������¿��Կ���ʹ�ý�����ģʽ��
// (1) ���Խ�һ����Ҫ����ִ�е������еľ��ӱ�ʾΪһ�������﷨����
// (2)  һЩ�ظ����ֵ����������һ�ּ򵥵����������б�
// (3) һ�����Ե��ķ���Ϊ�򵥡�

class PlayContext {
public:
  string& text() { return text_; }

private:
  string text_;
};

class Expression {
public:
  void Interpret(PlayContext& play_context) {
    string& text = play_context.text();

    if (text.empty()) {
      return;
    } else {
      string key = text.substr(0, 1);
      text = text.substr(2);
      size_t pos = text.find(" ");
      string value = text.substr(0, pos);
      text = text.substr(pos + 1);
      Excecute(key, value);
    }
  }

  virtual void Excecute(const string& key, const string& value) = 0;
};

class Note : public Expression {
public:
  void Excecute(const string& key, const string& value) override {
    string note;
    switch (key[0]) {
      case 'C':
        note = "1";
        break;
      case 'D':
        note = "2";
        break;
      case 'E':
        note = "3";
        break;
      case 'F':
        note = "4";
        break;
      case 'G':
        note = "5";
        break;
      case 'A':
        note = "6";
        break;
      case 'B':
        note = "7";
        break;
      default:
        note = "error";
        break;
    }
    cout << note << " ";
  }
};

class Scale : public Expression {
public:
  void Excecute(const string& key, const string& value) override {
    string scale;
    switch (value[0]) {
      case '1':
        scale = "����";
        break;
      case '2':
        scale = "����";
        break;
      case '3':
        scale = "����";
        break;
      default:
        scale = "error";
        break;
    }
    cout << scale << " ";
  }
};

int main23() {
  PlayContext play_context;
  string& text = play_context.text();
  text = "O 2 E 3 G 5 G 5 ";
 
  Expression* expression = NULL;

  while (!text.empty()) {
    string key = text.substr(0, 1);
    switch (key[0]) {
      case 'O':
        expression = new Scale();
        break;
      case 'C':
      case 'D':
      case 'E':
      case 'F':
      case 'G':
      case 'A':
      case 'B':
      case 'P':
        expression = new Note();
        break;
      default:
        break;
    }
    if (NULL != expression) {
      expression->Interpret(play_context);
    }
  }

  return 0;
}