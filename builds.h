#pragma once
#include<iostream>
#include<map>
#include <vector>
#include "node.h"

using namespace std;

Node* build_node(ifstream& in);

void build(Node* root);

void coder(ofstream& out, ifstream& in);

void decoder(ofstream& text, ifstream& file, Node* root);
