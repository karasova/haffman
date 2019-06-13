#include<iostream>
#include<fstream>
#include<map>
#include"node.h"
#include "builds.h"
#include <vector>

using namespace std;

int main(void) {
	ifstream in("Text.txt", ios::binary);
	ofstream out("Text_code.txt", ios::binary);
	
	Node* root = build_node(in);
	build(root);

	coder(out, in);

	ifstream file("Text_code.txt", ios::binary);
	ofstream text("Text_decode.txt", ios::binary);
	decoder(text, file, root);

	system("pause");
	return 0;
}

