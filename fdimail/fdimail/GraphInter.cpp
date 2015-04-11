#include "GraphInter.h"

GraphInter* GraphInter::inter = nullptr;

GraphInter::GraphInter()
{
}


GraphInter::~GraphInter()
{
}

GraphInter* GraphInter::get()
{
	return inter;
}

void GraphInter::load()
{
	if (inter = nullptr) inter = new GraphInter;
}