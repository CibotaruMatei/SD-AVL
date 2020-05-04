#pragma once
#include <memory>
#include <cmath>

class Node {
private:
	Node * parent, * left, * right;
	int key, height;
public:
	Node(int n) {
		parent = left = right = nullptr;
		height = 0;
		key = n;
	}

	int getKey() { return key; }

	static int getHeight(Node* x) {
		if (x == nullptr) return -1;
		else return x->height;
	}

	static int getHeightDiff(Node* x) {
		return getHeight(x->left) - getHeight(x->right);
	}

	Node* getLeft() { return left; }

	Node* getRight() { return right; }

	Node* getParent() { return parent; }

	bool childDirection() {
		if (parent->left == this) return true;
		return false;
	}

	bool isRoot() { return parent == nullptr; }

	Node* search(int n) {
		Node* x = this;

		while (x != nullptr)
			if (n < x->key) x = x->left;
			else if (n > x->key) x = x->right;
			else return x;

		return nullptr;
	}

	void insert(int n) {
		Node* newptr = nullptr;
		
		if (n < key) {
			if (left) left->insert(n);
			else newptr = left = new Node(n);
		}
		else {
			if(right != nullptr) right->insert(n);
			else newptr = right = new Node(n);
		}

		if (newptr != nullptr) {
			newptr->parent = this;
			this->upHeight();
			this->balance();
		}
	}

	void LRotate() {
		Node* p = parent, * r = right;
		
		right = r->left;
		if(right != nullptr) r->left->parent = this;

		parent = r;
		r->left = this;

		r->parent = p;
		if (p != nullptr) {
			if (childDirection() > 0) p->left = r;
			else p->right = r;
		}
	}

	void RRotate() {
		Node* p = parent, * l = left;

		left = l->right;
		if (left != nullptr) l->right->parent = this;

		parent = l;
		l->right = this;

		l->parent = p;
		if (p != nullptr) {
			if (childDirection() > 0) p->left = l;
			else p->right = l;
		}
	}

	void balance() {
		Node* x = this;
		while (x != nullptr) {
			int hdif = getHeightDiff(x);
			if (abs(hdif) > 1) {
				if (hdif > 0) {
					hdif = getHeightDiff(x->left);
					if (hdif < 0) {
						x->RRotate();
					}
					else {
						x->left->LRotate();
						x->RRotate();
					}
				}
				else {
					hdif = getHeightDiff(x->right);
					if (hdif < 0) {
						x->LRotate();
					}
					else {
						x->right->RRotate();
						x->LRotate();
					}
				}

				this->upHeight();
			}

			x = x->parent;
		}
	}

	void upHeight() {
		Node* x = this;

		while (x != nullptr) {
			int lh = getHeight(left), rh = getHeight(right);

			height = lh > rh ? lh + 1 : rh + 1;

			x = x->parent;
		}
	}

	Node* succesor() {
		Node* x = this;
		
		if (right != nullptr) {
			x = x->right;
			while (x->left != nullptr) x = x->left;
			return x;
		}

		while (x->parent != nullptr) {
			if (x->childDirection()) return x->parent;
			x = x->parent;
		}
		
		return nullptr;
	}

	Node* predecessor() {
		Node* x = this;

		if (left != nullptr) {
			x = x->left;
			while (x->right != nullptr) x = x->right;
			return x;
		}

		while (x->parent != nullptr) {
			if (!x->childDirection()) return x->parent;
			x = x->parent;
		}

		return nullptr;
	}

	bool remove(int n) {
		Node* x = search(n);

		while (x != nullptr) {
			if (x->left == nullptr && x->right == nullptr) {
				if (!x->isRoot()) {
					if (x->childDirection()) x->parent->left = nullptr;
					else x->parent->right = nullptr;
				}
				delete x;
				return true;
			}
			else if (x->left != nullptr && x->right != nullptr) {
				Node* s = x->succesor();
				x->key = s->key;
				s->key = n;
				x = s;
			}
			else {
				Node* c;
				
				if (x->left == nullptr) c = x->right;
				else c = x->left;

				if (!x->isRoot()) {
					if (x->childDirection()) x->parent->left = c;
					else x->parent->right = c;
				}
				c->parent = x->parent;

				delete x;
				return true;
			}
		}

		return false;
	}
};

static class AVL {
private:
	Node* root;
public:
	AVL() {
		root = nullptr;
	}

	int getMin() {
		Node* x = root;
		while (x->getLeft() != nullptr) x = x->getLeft();
		return x->getKey();
	}

	int getMax() {
		Node* x = root;
		while (x->getRight() != nullptr) x = x->getRight();
		return x->getKey();
	}

	//1
	void insert(int n) {
		if (root == nullptr) root = new Node(n);
		else root->insert(n);
		while (root->getParent() != nullptr) root = root->getParent();
	}

	//2
	bool remove(int n) {
		if (root->remove(n)) {
			Node* x = root;
			while (abs(Node::getHeightDiff(x)) > 1) {
				if (Node::getHeightDiff(x) > 0) x = x->getLeft();
				else x = x->getRight();
			}
			x->balance();
		}
		else return false;
	}

	//3
	Node* find(int n) {
		return root->search(n);
	}

	//4
	Node* predecessor(int n) {
		Node* x = root->search(n);
		int min = getMin();

		if (x != nullptr) return x->predecessor();
		else {
			n--;
			while (x == nullptr && n >= min) {
				x = root->search(n);
				n--;
			}
		}

		return x;
	}

	//5
	Node* successor(int n) {
		Node* x = root->search(n);
		int max = getMax();

		if (x != nullptr) return x->succesor();
		else {
			n++;
			while (x == nullptr && n <= max) {
				x = root->search(n);
				n++;
			}
		}

		return x;
	}

	//6
	void print(std::ostream& os, int start, int end) {
		Node* s = root->search(start);
		while (s == nullptr) {
			start++;
			s = root->search(start);
		}
		while (s != nullptr && s->getKey() <= end) {
			os << s->getKey() << " ";
			s = s->succesor();
		}
		os << "\n";
	}
};