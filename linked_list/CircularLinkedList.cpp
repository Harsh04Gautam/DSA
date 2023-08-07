#include <cstdlib>

template <typename E> class CNode {
  E elem;
  CNode<E> *next;

  template <typename F> friend class CircularLinkedList;
};

template <typename E> class CircularLinkedList {
public:
  CircularLinkedList();
  ~CircularLinkedList();
  bool empty() const;
  const E &front() const;
  const E &back() const;
  void advance();
  void add(const E &e);
  void remove();

private:
  CNode<E> *cursor;
};

template <typename E>
CircularLinkedList<E>::CircularLinkedList() : cursor(NULL) {}

template <typename E> bool CircularLinkedList<E>::empty() const {
  return cursor == NULL;
}

template <typename E> CircularLinkedList<E>::~CircularLinkedList() {
  while (!empty())
    remove();
}

template <typename E> const E &CircularLinkedList<E>::front() const {
  return cursor->next->elem;
}

template <typename E> const E &CircularLinkedList<E>::back() const {
  return cursor->elem;
}

template <typename E> void CircularLinkedList<E>::advance() {
  cursor = cursor->next;
}

template <typename E> void CircularLinkedList<E>::add(const E &e) {
  CNode<E> *v = new CNode<E>;
  v->elem = e;
  if (cursor == NULL) {
    v->next = v;
    cursor = v;
  } else {
    v->next = cursor->next;
    cursor->next = v;
  }
}

template <typename E> void CircularLinkedList<E>::remove() {
  CNode<E> *old = cursor->next;
  if (old == cursor)
    cursor = NULL;
  else
    cursor->next = old->next;
  delete old;
}

int main() { return EXIT_SUCCESS; }
