#include <cstdlib>

template <typename E> class SNode {
private:
  E elem;
  SNode *next;
  template <typename F> friend class SinglyLinkedList;
};

template <typename E> class SinglyLinkedList {
public:
  SinglyLinkedList();
  ~SinglyLinkedList();
  bool empty() const;
  const E &front() const;
  void addFront(const E &v);
  void removeFront();

private:
  SNode<E> *head;
};

template <typename E> SinglyLinkedList<E>::SinglyLinkedList() : head(NULL) {}
template <typename E> bool SinglyLinkedList<E>::empty() const {
  return head == NULL;
}

template <typename E> const E &SinglyLinkedList<E>::front() const {
  return head->elem;
}

template <typename E> SinglyLinkedList<E>::~SinglyLinkedList() {
  while (!empty())
    removeFront();
}

template <typename E> void SinglyLinkedList<E>::addFront(const E &e) {
  SNode<E> *v = new SNode<E>;
  v->elem = e;
  v->next = head;
  head = v;
}

template <typename E> void SinglyLinkedList<E>::removeFront() {
  SNode<E> *old = head;
  head = old->next;
  delete old;
}

int main() { return EXIT_SUCCESS; }
