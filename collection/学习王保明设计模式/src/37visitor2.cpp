#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

// 桥接模式是将行为抽象和行为实现分离。
// 访问者模式将数据结构和行为进行分离。

// visitor就是行为，BlogList就是数据结构。Blog的行为没有在自己的类里面具体实现，而是通过Accept接收访问者来交给访问者实现行为,
// 并且将自己的引用传给访问者，访问者以此得到Blog的数据。

// 实现思路：向对象结构类中添加元素，然后定义多种访问者，使用对象结构类去接受访问者即可。

//----------------------------------------------------
// 用户可以通过电脑上的Web方式（访问者）或者手机Wap方式（访问者）去访问博客，每篇博客是一个元素，然后博客列表是一个对象结构类。
class Visitor;

class BlogElement {
public:
  BlogElement(const string& name)
    : name_(name) {
  }
  virtual ~BlogElement() {}

  string name() const { return name_; }

  virtual void Accept(Visitor* visitor) = 0;

protected:
  string name_;
};

class Visitor {
public:
  virtual void VisitBlog(BlogElement* blog) = 0;
};

//----------------------------------------------------

class WebVisitor : public Visitor {
public:
  void VisitBlog(BlogElement* blog) override {
    cout << "通过web浏览： " << blog->name() << endl;
  }
};

class WapVisitor : public Visitor {
  void VisitBlog(BlogElement* blog) override {
    cout << "通过wap浏览： " << blog->name() << endl;
  }
};

//-----------------------------------------------------

class Blog : public BlogElement {
public:
  Blog(const string& name)
    : BlogElement(name) {
  }

  void Accept(Visitor* visitor) override {
    visitor->VisitBlog(this);
  }
};

class BlogList : public BlogElement {
public:
  BlogList(const string& name)
    : BlogElement(name) {
  }

  ~BlogList() {
    for (Blog* blog : blogs_) {
      delete blog;
    }
    blogs_.clear();
  }

  void AddBlog(Blog* blog) {
    blogs_.push_back(blog);
  }

  void Accept(Visitor* visitor) override {
    for (Blog* blog : blogs_) {
      blog->Accept(visitor);
    }
  }

private:
  list<Blog*> blogs_;
};

//------------------------------------------------------

int main37() {
  Visitor* web_visitor = new WebVisitor;
  Visitor* wap_visitor = new WapVisitor;

  BlogList blog_list("BlogList");
  blog_list.AddBlog(new Blog("BlogA"));
  blog_list.AddBlog(new Blog("BlogB"));
  blog_list.AddBlog(new Blog("BlogC"));
  blog_list.AddBlog(new Blog("BlogD"));

  blog_list.Accept(wap_visitor);
  blog_list.Accept(web_visitor);

  delete wap_visitor;
  delete web_visitor;

  return 0;
}
