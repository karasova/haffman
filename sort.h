#pragma once
#include<iostream>
#include "node.h"

using namespace std;

struct sort {
	bool operator()(Node* l, Node* r) const {
		return r->w > l->w;
	}
};
