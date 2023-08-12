#include <cstdlib>
#include <string>

template <typename E> class CNode {
private:
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

template <typename E> CircularLinkedList<E>::~CircularLinkedList() {
  while (!empty())
    remove();
}

template <typename E> bool CircularLinkedList<E>::empty() const {
  return cursor == NULL;
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

class RuntimeException {
private:
  std::string errorMsg;

public:
  RuntimeException(const std::string &err) { errorMsg = err; }
  const std::string getError() const { return errorMsg; };
};

class QueueEmpty : public RuntimeException {
public:
  QueueEmpty(const std::string &err) : RuntimeException(err) {}
};

template <typename E> class LinkedQueue {
public:
  LinkedQueue();
  int size() const;
  bool empty() const;
  const E &front() const throw(QueueEmpty);
  void enqueue(const E &e);
  void dequeue() throw(QueueEmpty);

private:
  CircularLinkedList<E> C;
  int n;
};

template <typename E> LinkedQueue<E>::LinkedQueue() : C(), n(0) {}
template <typename E> bool LinkedQueue<E>::empty() const { return n == 0; }
template <typename E> int LinkedQueue<E>::size() const { return n; }

template <typename E> const E &LinkedQueue<E>::front() const throw(QueueEmpty) {
  if (empty())
    throw QueueEmpty("front of empty queue");

  return C.front();
}

template <typename E> void LinkedQueue<E>::enqueue(const E &e) {
  C.add(e);
  C.advance();
  n++;
}

template <typename E> void LinkedQueue<E>::dequeue() throw(QueueEmpty) {
  if (empty())
    throw QueueEmpty("dequeue of empty queue");
  C.remove();
  n--;
}

int main() { return EXIT_SUCCESS; }
