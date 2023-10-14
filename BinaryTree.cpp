#include <cstdlib>
#include <list>

template <typename E> class Node {
private:
  E elt;
  Node<E> *par;
  Node<E> *left;
  Node<E> *right;
  Node() : elt(), par(NULL), left(NULL), right(NULL) {}

  template <typename F> friend class Position;
  template <typename F> friend class LinkedBinaryTree;
};

template <typename E> class Position {
private:
  Node<E> *v;

public:
  Position(Node<E> *_v = NULL) : v(_v){};
  E &operator*() { return v->elt; };
  Position left() const { return Position(v->left); }
  Position right() const { return Position(v->right); }
  Position parent() const { return Position(v->par); }
  bool isRoot() const { return v->par == NULL; }
  bool isExternal() const { return v->left == NULL && v->right == NULL; }

  template <typename F> friend class LinkedBinaryTree;
};

template <typename E> class LinkedBinaryTree {
public:
  LinkedBinaryTree();
  int size() const;
  bool empty() const;
  Position<E> root() const;
  std::list<Position<E>> positions() const;
  void addRoot();
  void expandExternal(const Position<E> &p);
  Position<E> removeAboveExternal(const Position<E> &p);

protected:
  void preorder(Node<E> *v, std::list<Position<E>> &pl) const;

private:
  Node<E> *_root;
  int n;
};

template <typename E>
LinkedBinaryTree<E>::LinkedBinaryTree() : _root(NULL), n(0){};

template <typename E> int LinkedBinaryTree<E>::size() const { return n; }

template <typename E> bool LinkedBinaryTree<E>::empty() const {
  return size() == 0;
}

template <typename E> Position<E> LinkedBinaryTree<E>::root() const {
  return Position<E>(_root);
};

template <typename E> void LinkedBinaryTree<E>::addRoot() {
  _root = new Node<E>;
  n = 1;
};

template <typename E>
void LinkedBinaryTree<E>::expandExternal(const Position<E> &p) {
  Node<E> *v = p.v;
  v->left = new Node<E>;
  v->left->par = v;
  v->right = new Node<E>;
  v->right->par = v;
  n += 2;
}

template <typename E>
Position<E> LinkedBinaryTree<E>::removeAboveExternal(const Position<E> &p) {
  Node<E> *w = p.v;
  Node<E> *v = w->par;
  Node<E> *sib = (w == v->left ? v->right : v->left);
  if (v == _root) {
    _root = sib;
    sib->par = NULL;
  } else {
    Node<E> *gpar = v->par;
    if (v == gpar->left)
      gpar->left = sib;
    else
      gpar->right = sib;
    sib->par = gpar;
  }
  delete w;
  delete v;
  n -= 2;
  return Position<E>(sib);
};

template <typename E>
std::list<Position<E>> LinkedBinaryTree<E>::positions() const {
  std::list<Position<E>> pl;
  preorder(_root, pl);
  return std::list<Position<E>>(pl);
};

template <typename E>
void LinkedBinaryTree<E>::preorder(Node<E> *v,
                                   std::list<Position<E>> &pl) const {
  pl.push_back(Position<E>(v));
  if (v->left != NULL)
    preorder(v->left, pl);
  if (v->right != NULL)
    preorder(v->right, pl);
};
