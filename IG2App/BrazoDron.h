#pragma once
#include "EntidadIG.h"
using namespace std;
class BrazoDron : public EntidadIG
{
	string aspaName;
public:
	void girarAspa();
	BrazoDron(SceneNode* node, string fname);
	~BrazoDron() {};
};

