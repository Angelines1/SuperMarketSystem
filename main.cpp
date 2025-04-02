#include<iostream>
#include"Link.h"
#include"items.h"
using namespace std;

int main()
{
	Link_list list;
	list.Link_add(item("1", "1", "1", 1, 1, 1));
	list.Link_show();
}