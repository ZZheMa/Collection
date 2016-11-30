#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

// ����۲��߶������һ�����󣬸ö��󱣴����еĶ���ĳ����������ı�ʱ��֪ͨ���еĶ���
// ��ģʽ�Ǹ�ͨ��������������ʵ�ּ������������ݵķ�����

class TextListener {
public:
  virtual void OnLineUpdate(size_t n) = 0;
};

class Text {
public:
  void Attach(TextListener* text_listener) {
    text_listeners_.push_back(text_listener);
  }

  void Detach(TextListener* text_listener) {
    list<TextListener*>::iterator it;
    it = find(text_listeners_.begin(), text_listeners_.end(), text_listener);
    if (it != text_listeners_.end()) {
      text_listeners_.erase(it);
    }
  }

  void InsertLine(size_t n) {
    cout << "Insert a line in Line " << n << endl;
    Notify(n);
  }

private:
  void Notify(size_t n) {
    for (TextListener* text_listener : text_listeners_) {
      text_listener->OnLineUpdate(n);
    }
  }

private:
  list<TextListener*> text_listeners_;
};

class TextPanel : public TextListener {
public:
  void OnLineUpdate(size_t n) override {
    cout << "Refresh the text in Line " << n << endl;
  }
};

class LineNumberPanel : public TextListener {
public:
  void OnLineUpdate(size_t n) override {
    cout << "Refresh the line number in Line " << n << endl;
  }
};

int main15() {
  Text* text = new Text;
  LineNumberPanel* line_number_panel = new LineNumberPanel;
  TextPanel* text_panel = new TextPanel;

  text->Attach(line_number_panel);
  text->Attach(text_panel);

  text->InsertLine(10);

  cout << "---------------------------------------" << endl;

  text->Detach(text_panel);
  text->InsertLine(11);

  delete text_panel;
  delete line_number_panel;
  delete text;

  return 0;
}