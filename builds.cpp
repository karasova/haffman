#include<iostream>
#include "builds.h"
#include<list>
#include"sort.h"
#include<fstream>

vector <bool> code;
map <char, vector <bool>> table;

Node* build_node(ifstream& in) {
	map<char, int> gur;
	while (!in.eof()) {
		char in_char = in.get();
		gur[in_char]++;
	}

	list<Node*> heapNode;
	for (map<char, int>::iterator it = gur.begin(); it != gur.end(); it++) {
		Node* p = new Node;
		p->w = it->second;
		p->c = it->first;
		heapNode.push_back(p);
	}

	while (heapNode.size() != 1) {
		heapNode.sort(sort());
		Node* sonl = heapNode.front();
		heapNode.pop_front();
		Node* sonr = heapNode.front();
		heapNode.pop_front();
		Node* parent = new Node(sonl, sonr);
		heapNode.push_back(parent);
	}
	return heapNode.front();
}

void build(Node* root) {
	if (root->left != NULL) {
		code.push_back(0);
		build(root->left);
	}
	if (root->right != NULL) {
		code.push_back(1);
		build(root->right);
	}
	if (root->right == NULL && root->left == NULL)
		table[root->c] = code;

	if (code.size() != 0)
		code.pop_back();
}

void coder(ofstream& out, ifstream& in) {
	in.clear();
	in.seekg(0);

	int count = 0;
	char buf = 0;
	while (!in.eof()) {
		char c = in.get();
		vector <bool> x = table[c];
		for (int n = 0; n < x.size(); n++) {
			buf = buf | x[n] << (7 - count);
			count++;
			if (count == 8) {
				count = 0;
				buf = 0;
			}
		}
	}
	if (count == 0)
		count = 8;
	out << count;
	count = 0;
	buf = 0;

	in.clear();
	in.seekg(0);
	while (!in.eof()) {
		char c = in.get();
		vector <bool> x = table[c];
		for (int n = 0; n < x.size(); n++) {
			buf = buf | x[n] << (7 - count);
			count++;
			if (count == 8) {
				count = 0;
				out << buf;
				buf = 0;
			}
		}
	}
	if (count != 0) {
		out << buf;
	}
	out.close();

}

void decoder(ofstream& text, ifstream& file, Node* root) {
	Node *p = root;
	int count = 0;
	char byte;
	byte = file.get();
	int bytes = 0;
	while (!file.eof()) {
		byte = file.get();
		bytes++;
	}
	cout << bytes << endl;
	file.clear();
	file.seekg(0);

	int end_bites;
	end_bites = file.get() - 48;
	cout << end_bites;
	byte = file.get();

	int taken_bytes = 1, sign = 0;
	while (!file.eof()) {
		if (taken_bytes == bytes - 1) {
			sign = 1;
		}
		bool b = byte & (1 << (7 - count));
		if (b == 1)
			p = p->right;
		else
			p = p->left;
		if (p->left == NULL && p->right == NULL) {
			text << p->c;
			p = root;
		}
		if (end_bites == 1)
			if (sign == 1 && count == end_bites-1) {
				break;
			}
		count++;
		if (sign == 1 && count == end_bites - 1) {
			break;
		}

		if (count == 8) {
			count = 0;
			byte = file.get();
			taken_bytes++;
		}
	}
}
