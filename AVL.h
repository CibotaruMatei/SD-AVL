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
		key = 0;
	}

	static int getHeight(Node* x) {
		if (x == nullptr) return -1;
		else return x->height;
	}

	static int getHeightDiff(Node* x) {
		return getHeight(x->left) - getHeight(x->right);
	}

	bool childDirection() {
		if (parent->left == this) return true;
		return false;
	}

	bool search(int n) {
		Node* x = this;

		while (x != nullptr)
			if (n < x->key) x = x->left;
			else if (n > x->key) x = x->right;
			else return true;

		return false;
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
		r->left->parent = this;

		parent = r;
		r->left = this;

		r->parent = p;
		if (p != nullptr) {
			if (p->left = this) p->left = r;
			else p->right = r;
		}
	}

	void RRotate() {
		Node* p = parent, * l = left;

		left = l->right;
		l->right->parent = this;

		parent = l;
		l->right = this;

		l->parent = p;
		if (p != nullptr) {
			if (p->left = this) p->left = l;
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
						x->right->RRotate();
						x->LRotate();
					}
					else {
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
};