#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

// ½«Ëã·¨·â×°

class Weapon {
public:
  virtual void UseWeapon() = 0;
};

class Knife : public Weapon {
public:
  void UseWeapon() override {
    cout << "knife" << endl;
  }
};

class Gun : public Weapon {
public:
  void UseWeapon() override {
    cout << "gun" << endl;
  }
};

class Character {
public:
  Character() {}
  ~Character() {}

  void set_weapon(Weapon* wapon) { weapon_ = wapon; }

  virtual void Fight() = 0;

protected:
  Weapon* weapon_;
};

class King : public Character {
public:
  King() {}
  ~King() {}

  void Fight() override {
    weapon_->UseWeapon();
  }
};

int main07() {
  Weapon* knife = new Knife();
  Weapon* gun = new Gun();
  King* king = new King();

  king->set_weapon(knife);
  king->Fight();

  king->set_weapon(gun);
  king->Fight();

  delete king;
  delete gun;
  delete knife;

  return 0;
}