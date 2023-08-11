#include <cstdlib>
template <typename E> class DNode {
private:
  E elem;
  DNode *prev;
  DNode *next;
  template <typename F> friend class DoublyLinkedList;
};

template <typename E> class DoublyLinkedList {
public:
  DoublyLinkedList();
  ~DoublyLinkedList();
  bool empty() const;
  const E &front() const;
  const E &back() const;
  void addFront(const E &e);
  void addBack(const E &e);
  void removeFront();
  void removeBack();

protected:
  void add(const DNode<E> *v, const E &e);
  void remove(DNode<E> *v);

private:
  DNode<E> *header;
  DNode<E> *trailer;
};

template <typename E> DoublyLinkedList<E>::DoublyLinkedList() {
  header = new DNode<E>;
  trailer = new DNode<E>;
  header->next = trailer;
  trailer->prev = header;
};

template <typename E> DoublyLinkedList<E>::~DoublyLinkedList() {
  while (!empty()) {
    removeFront();
  }
  delete header;
  delete trailer;
};

template <typename E> bool DoublyLinkedList<E>::empty() const {
  return header->next == trailer;
}

template <typename E> const E &DoublyLinkedList<E>::front() const {
  return header->next->elem;
}

template <typename E> const E &DoublyLinkedList<E>::back() const {
  return trailer->prev->elem;
}

template <typename E>
void DoublyLinkedList<E>::add(const DNode<E> *v, const E &e) {
  DNode<E> *u = new DNode<E>;
  u->elem = e;
  u->next = v;
  u->prev = v->prev;
  v->prev->next = v->prev = u;
}

template <typename E> void DoublyLinkedList<E>::addFront(const E &e) {
  add(header->next, e);
}

template <typename E> void DoublyLinkedList<E>::addBack(const E &e) {
  add(trailer, e);
}

template <typename E> void DoublyLinkedList<E>::remove(DNode<E> *v) {
  DNode<E> *u = v->prev;
  DNode<E> *w = v->next;
  u->next = w;
  w->prev = u;
  delete v;
}

template <typename E> void DoublyLinkedList<E>::removeFront() {
  remove(header->next);
}

template <typename E> void DoublyLinkedList<E>::removeBack() {
  remove(trailer->prev);
}

template <typename E> void listReverse(DoublyLinkedList<E> &L) {
  DoublyLinkedList<E> T;
  while (!L.empty()) {
    E e = L.front();
    L.removeFront();
    T.addFront(e);
  }
  while (!T.empty()) {
    E e = T.front();
    T.removeFront();
    L.addBack(e);
  }
}

int main() { return EXIT_SUCCESS; }
