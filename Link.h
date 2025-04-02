#ifndef LINKLIST_H
#define LINKLIST_H
#include"items.h"
 
class Link_part
{
public:
	Link_part();
	item it;
	Link_part* next;
};

class Link_list
{
public:
	//构造函数
	Link_list();
	~Link_list();
	Link_part* head;
	int Long;	//长度

public:
	void Link_add(item it);
	void Link_delete(string NO);
	void Link_updata(item it);
	void Link_show();
	void Link_find(string NO);
};

#endif // !LINKLIST
