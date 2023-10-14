#include <cstdlib>
#include <iostream>

class RuntimeException {
private:
  std::string errorMsg;

public:
  RuntimeException(const std::string &err) { errorMsg = err; };
  const std::string &getError() const { return errorMsg; };
};

class IndexOutOfBounds : public RuntimeException {
public:
  IndexOutOfBounds(const std::string &err) : RuntimeException(err){};
};

template <typename E> class ArrayVector {
public:
  ArrayVector();
  int size() const;
  bool empty() const;
  E &operator[](int i);
  E &at(int i) throw(IndexOutOfBounds);
  void erase(int i);
  void insert(int i, const E &e);
  void reserve(int N);

private:
  int capacity;
  int n;
  E *A;
};

template <typename E>
ArrayVector<E>::ArrayVector() : capacity(0), n(0), A(NULL){};
template <typename E> int ArrayVector<E>::size() const { return n; }
template <typename E> bool ArrayVector<E>::empty() const { return size() == 0; }
template <typename E> E &ArrayVector<E>::operator[](int i) { return A[i]; }
template <typename E> E &ArrayVector<E>::at(int i) throw(IndexOutOfBounds) {
  if (i < 0 || i >= n)
    throw IndexOutOfBounds("illegal index in function at()");
  return A[i];
}
template <typename E> void ArrayVector<E>::erase(int i) {
  for (int j = i + 1; j < n; j++)
    A[j - 1] = A[j];
  n--;
}

template <typename E> void ArrayVector<E>::reserve(int N) {
  if (capacity >= N)
    return;
  E *B = new E[N];
  for (int j = 0; j < n; j++)
    B[j] = A[j];
  if (A != NULL)
    delete[] A;
  A = B;
  capacity = N;
}

template <typename E> void ArrayVector<E>::insert(int i, const E &e) {
  if (n >= capacity)
    reserve(std::max(1, 2 * capacity));
  for (int j = 0; j >= i; j--)
    A[j + 1] = A[j];
  A[i] = e;
  n++;
}

int main() { return EXIT_SUCCESS; }
