#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

// Composite模式也叫组合模式，是构造型的设计模式之一。通过递归手段来构造树形的对象结构，并可以通过一个对象来访问整个对象树。

// Component（树形结构的节点抽象）
// - 为所有的对象定义统一的接口（公共属性，行为等的定义）；
// - 提供管理子节点对象的接口方法；
// - [可选]提供管理父节点对象的接口方法。

// Leaf （树形结构的叶节点）
// Component的实现子类。

// Composite（树形结构的枝节点）
// Component的实现子类。

// 适用于：
// 单个对象和组合对象的使用具有一致性。将对象组合成树形结构以表示“部分--整体”。

class IFile {
public:
  IFile(const string& name)
    : name_(name) {
  }

  virtual void Display() = 0;
  virtual bool Add(IFile* child) = 0;
  virtual list<IFile*>* GetChildren() = 0;

protected:
  string name_;
};

class Dir : public IFile {
public:
  Dir(const string& name)
    : IFile(name) {
    children_ = new list<IFile*>;
  }

  void Display() override {
    cout << name_ << endl;
  }

  bool Add(IFile* child) override {
    children_->push_back(child);
    return true;
  }

  list<IFile*>* GetChildren() override {
    return children_;
  }

private:
  list<IFile*>* children_;
};

class File :public IFile {
public:
  File(const string& name)
    : IFile(name) {
  }

  void Display() override {
    cout << name_ << endl;
  }

  bool Add(IFile* child) override {
    return false;
  }

  list<IFile*>* GetChildren() override {
    return NULL;
  }
};

void ShowFileTree(IFile* root, int depth) {
  if (root == NULL) {
    return;
  }

  cout << string(depth, '-');
  root->Display();

  list<IFile*>* children = root->GetChildren();
  for (IFile* child : *children) {
    if (child->GetChildren() == NULL) {
      cout << string(depth + 1, '-');
      child->Display();
    } else {
      ShowFileTree(child, depth + 1);
    }
  }
}

int main21() {
  IFile* dir = new Dir("Dir");
  IFile* dir1 = new Dir("Dir1");
  IFile* dir2 = new Dir("Dir2");
  IFile* file = new File("file");

  IFile* dir3 = new Dir("Dir3");
  IFile* file2 = new File("file2");
  IFile* file3 = new File("file3");

  IFile* file4 = new File("file4");
  IFile* file5 = new File("file5");

  dir->Add(dir1);
  dir->Add(dir2);
  dir->Add(file);

  dir1->Add(dir3);
  dir1->Add(file2);
  dir1->Add(file3);

  dir3->Add(file4);
  dir3->Add(file5);

  ShowFileTree(dir, 0);

  delete dir;
  delete dir1;
  delete dir2;
  delete dir3;

  delete file;
  delete file2;
  delete file3;
  delete file4;
  delete file5;

  return 0;
}
