#include <iostream>
#include <list>
#include <algorithm>
#include <string>

using namespace std;

class TextListener {
public:
  TextListener() {}
  virtual ~TextListener() {}

  virtual void OnLineUpdate(size_t n) = 0;
};

class TextScrollWindow : public TextListener {
public:
  virtual void OnLineUpdate(size_t n) override {
    cout << "Update " << n << endl;
  }
};

class TextFile {
public:
  void AttachListener(TextListener* text_listener) {
    text_listeners_.push_back(text_listener);
  }

  void DetachListener(TextListener* text_listener) {
    list<TextListener*>::iterator iter;
    iter = find(text_listeners_.begin(), text_listeners_.end(), text_listener);
    if (iter != text_listeners_.end()) {
      text_listeners_.erase(iter);
    }
  }

  void InsertChar(size_t n) {
    cout << "Insert " << n << endl;
    UpdateLine(n);
  }

private:
  void UpdateLine(size_t n) {
    for (list<TextListener*>::iterator iter = text_listeners_.begin();
         iter != text_listeners_.end();
         iter++) {
      (*iter)->OnLineUpdate(n);
    }
  }

private:
  list<TextListener*> text_listeners_;
};

int main21() {
  TextScrollWindow* text_window = new TextScrollWindow();
  TextFile* text_file = new TextFile();
  text_file->AttachListener(text_window);
  text_file->InsertChar(15);

  return 0;
}
