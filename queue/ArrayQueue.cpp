#include <cstdlib>
#include <string>

class RuntimeException {
private:
  std::string errorMsg;

public:
  RuntimeException(const std::string &err) { errorMsg = err; };
  const std::string getError() const { return errorMsg; };
};

class QueueEmpty : public RuntimeException {
public:
  QueueEmpty(const std::string &err) : RuntimeException(err){};
};

class QueueFull : public RuntimeException {
public:
  QueueFull(const std::string &err) : RuntimeException(err){};
};

template <typename E> class ArrayQueue {
  enum { DEF_CAPACITY = 100 };

public:
  ArrayQueue(int cap = DEF_CAPACITY);
  int size() const;
  bool empty() const;
  const E &front() const throw(QueueEmpty);
  void enqueue(const E &e);
  void dequeue() throw(QueueEmpty);

private:
  E *Q;
  int capacity;
  int f;
  int r;
  int n;
};

template <typename E>
ArrayQueue<E>::ArrayQueue(int cap)
    : Q(new E[cap]), capacity(cap), f(0), r(0), n(0){};

template <typename E> int ArrayQueue<E>::size() const { return n; }
template <typename E> bool ArrayQueue<E>::empty() const { return n == 0; }

template <typename E> const E &ArrayQueue<E>::front() const throw(QueueEmpty) {
  if (empty())
    throw QueueEmpty("Front of empty queue");
  return Q[f];
}

template <typename E> void ArrayQueue<E>::dequeue() throw(QueueEmpty) {
  if (empty())
    throw QueueEmpty("Dequeue from empty queue.");

  f = (f + 1) % capacity;
  n = n - 1;
}

template <typename E> void ArrayQueue<E>::enqueue(const E &e) {
  if (size() == capacity)
    throw QueueFull("Enqueue to full queue.");
  Q[r] = e;
  r = (r + 1) % capacity;
  n = n + 1;
};

int main() { return EXIT_SUCCESS; }
