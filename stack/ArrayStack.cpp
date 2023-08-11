#include <cstdlib>
#include <string>

class RuntimeException {
private:
  std::string errorMsg;

public:
  RuntimeException(const std::string &err) { errorMsg = err; };
  const std::string getError() const { return errorMsg; };
};

class StackFull : public RuntimeException {
public:
  StackFull(const std::string &err) : RuntimeException(err) {}
};

class StackEmpty : public RuntimeException {
public:
  StackEmpty(const std::string &err) : RuntimeException(err) {}
};

template <typename E> class ArrayStack {
public:
  ArrayStack(const int cap);
  int size() const;
  bool empty() const;
  const E &top() const throw(StackEmpty);
  void push(const E &e) throw(StackFull);
  void pop() throw(StackEmpty);

private:
  E *S;
  int capacity;
  int t;
};

template <typename E>
ArrayStack<E>::ArrayStack(const int cap)
    : S(new E[cap]), capacity(cap), t(-1) {}

template <typename E> int ArrayStack<E>::size() const { return t + 1; }

template <typename E> bool ArrayStack<E>::empty() const { return t < 0; }

template <typename E> const E &ArrayStack<E>::top() const throw(StackEmpty) {
  if (empty())
    throw StackEmpty("Top of empty stack");
  return S[t];
}

template <typename E> void ArrayStack<E>::push(const E &e) throw(StackFull) {
  if (size() == capacity)
    throw StackFull("Push to full stack");
  S[++t] = e;
}

template <typename E> void ArrayStack<E>::pop() throw(StackEmpty) {
  if (empty())
    throw StackEmpty("Pop from empty stack");
  --t;
}

int main() { return EXIT_SUCCESS; }
