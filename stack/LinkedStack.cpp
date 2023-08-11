#include <cstdlib>
#include <string>

class RuntimeException {
private:
  std::string errorMsg;

public:
  RuntimeException(const std::string &err) { errorMsg = err; }
  const std::string getError() { return errorMsg; }
};

class StackFull : public RuntimeException {
public:
  StackFull(const std::string &err) : RuntimeException(err){};
};

class StackEmpty : public RuntimeException {
public:
  StackEmpty(const std::string &err) : RuntimeException(err){};
};

template <typename E> class SNode {
private:
  E elem;
  SNode<E> *next;
  SNode<E> *prev;

  template <typename F> friend class SinglyLinkedList;
};

template <typename E> class SinglyLinkedList {
public:
  SinglyLinkedList();
  ~SinglyLinkedList();
  bool empty() const;
  const E &front() const;
  const E &back() const;
  void addFront(const E &e);
  void addBack(const E &e);
  void removeFront();
  void removeBack();

protected:
  void add(SNode<E> *v, const E &e);
  void remove(SNode<E> *v);

private:
  SNode<E> *header;
  SNode<E> *trailer;
};

template <typename E> SinglyLinkedList<E>::SinglyLinkedList() {
  header = new SNode<E>;
  trailer = new SNode<E>;
  header->next = trailer;
  trailer->prev = header;
}

template <typename E> SinglyLinkedList<E>::~SinglyLinkedList() {
  while (!empty())
    removeFront();
  delete header;
  delete trailer;
}

template <typename E> bool SinglyLinkedList<E>::empty() const {
  return header->next == trailer;
}

template <typename E> const E &SinglyLinkedList<E>::front() const {
  return header->next->elem;
}

template <typename E> const E &SinglyLinkedList<E>::back() const {
  return trailer->prev->elem;
}

template <typename E> void SinglyLinkedList<E>::add(SNode<E> *v, const E &e) {
  SNode<E> *u = new SNode<E>;
  u->elem = e;
  u->next = v;
  u->prev = v->prev;
  v->prev->next = v->prev = u;
}

template <typename E> void SinglyLinkedList<E>::addFront(const E &e) {
  add(header->next, e);
}
template <typename E> void SinglyLinkedList<E>::addBack(const E &e) {
  add(trailer, e);
}

template <typename E> void SinglyLinkedList<E>::remove(SNode<E> *v) {
  SNode<E> *u = v->prev;
  SNode<E> *w = v->next;
  u->next = w;
  w->prev = u;
  delete v;
};

template <typename E> void SinglyLinkedList<E>::removeFront() {
  remove(header->next);
}
template <typename E> void SinglyLinkedList<E>::removeBack() {
  remove(trailer->prev);
}

template <typename E> class LinkedStack {
public:
  LinkedStack();
  int size() const;
  bool empty() const;
  const E &top() const throw(StackEmpty);
  void push(const E &e);
  void pop() throw(StackEmpty);

private:
  SinglyLinkedList<E> S;
  int n;
};

template <typename E> LinkedStack<E>::LinkedStack() : S(), n(0){};
template <typename E> int LinkedStack<E>::size() const { return n; }
template <typename E> bool LinkedStack<E>::empty() const { return n == 0; }

template <typename E> const E &LinkedStack<E>::top() const throw(StackEmpty) {
  if (empty())
    throw StackEmpty("Top of empty stack");
  return S.front();
}

template <typename E> void LinkedStack<E>::push(const E &e) {
  ++n;
  S.addFront(e);
}

template <typename E> void LinkedStack<E>::pop() throw(StackEmpty) {
  if (empty())
    throw StackEmpty("Pop from empty stack");
  --n;
  S.removeFront();
}

int main() { return EXIT_SUCCESS; }
