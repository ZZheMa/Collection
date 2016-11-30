#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

// Law of Demeter

// 迪米特法则（Law of Demeter）又叫最少知识原则（Least Knowledge Principle LKP）.

// 对面向对象来说，一个软件实体应当尽可能的少的与其他实体发生相互作用。每一个软件单位对其他的单位都只有最少的知识，
// 而其局限于那些与本单位密切相关的软件单位。迪米特法则的目的在于降低类之间的耦合。由于每个类尽量减少对其他类的依赖.
// 因此，很容易使得系统的功能模块相互独立，相互之间不存在依赖关系。应用迪米特法则有可能造成的一个后果就是，
// 系统中存在的大量的中介类，这些类只所以存在完全是为了传递类之间的相互调用关系,这在一定程度上增加系统的复杂度。

// 设计模式中的门面模式（Facade）和中介模式（Mediator）都是迪米特法则的应用的例子。

int main06() {
  return 0;
}