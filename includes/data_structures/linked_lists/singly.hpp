#ifndef __MINI_TOOLS__DATA_STRUCTURES__LINKED_LIST__SINGLY_HPP__
#define __MINI_TOOLS__DATA_STRUCTURES__LINKED_LIST__SINGLY_HPP__

class Singly {
private:
  bool instantiated = true;
  Singly *right = nullptr;

  ~Singly() { instantiated = false; }

public:
  Singly(Singly *right_in = nullptr) : right(right_in) {}

  virtual void release() {
    right = nullptr;
  }

  virtual void destroy() {
    if (instantiated) delete this;
  }

  virtual void annihilate() {
    Singly *current = this;

    while (current) {
      Singly *buffer = current->next();
      current->destroy();
      current = buffer;
    }
  }

  virtual Singly *next() { return right; }
};

#endif __MINI_TOOLS__DATA_STRUCTURES__LINKED_LIST__SINGLY_HPP__