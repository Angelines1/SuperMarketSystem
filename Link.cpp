#include <iostream>
#include <string>
#include "Link.h"
using namespace std;

// 析构函数：释放所有节点
Link_list::~Link_list()
{
    Link_part* current = head;
    while (current != nullptr) 
    {
        Link_part* next = current->next;
        delete current;
        current = next;
    }
}

// 构造函数初始化节点
Link_part::Link_part()
{
    this->next = nullptr;
}

// 辅助函数：找到链表末尾节点
Link_part* find_NULL(Link_part* head)
{
    if (head == nullptr)
        return nullptr;
    Link_part* current = head;
    while (current->next != nullptr)
        current = current->next;
    return current;
}

// 辅助函数：找到指定NO节点的前驱
Link_part* find_NO(Link_part* head, string NO)
{
    Link_part* current = head;
    while (current->next != nullptr) 
    {
        if (current->next->it.NO == NO)
            return current;
        current = current->next;
    }
    return nullptr;
}

// 初始化链表（改用构造函数替代）
Link_list::Link_list()
{
    head = nullptr;
    Long = 0;
}

// 添加节点到链表末尾
void Link_list::Link_add(item it)
{
    Link_part* newpart = new Link_part;
    newpart->it = it;
    newpart->next = nullptr;

    if (head == nullptr) 
    {
        head = newpart;
    } 
    else 
    {
        Link_part* last = find_NULL(head);
        last->next = newpart;
    }
    Long++;
}

// 删除指定NO的节点
void Link_list::Link_delete(string NO)
{
    if (head == nullptr)
        return;

    // 处理头节点
    if (head->it.NO == NO) 
    {
        Link_part* temp = head;
        head = head->next;
        delete temp;
        Long--;
        return;
    }

    Link_part* prev = find_NO(head, NO);
    if (prev != nullptr && prev->next != nullptr) 
    {
        Link_part* temp = prev->next;
        prev->next = temp->next;
        delete temp;
        Long--;
    }
}

// 查找并显示节点信息
void Link_list::Link_find(string NO)
{
    Link_part* current = head;
    while (current != nullptr) 
    {
        if (current->it.NO == NO) 
        {
            current->it.show_it();
            return;
        }
        current = current->next;
    }
    cout << "Not found" << endl;
}

// 显示所有节点信息
void Link_list::Link_show()
{
    Link_part* part = head;
    while (part != nullptr) 
    {
        part->it.show_it();
        part = part->next;
    }
}

// 更新节点信息，若不存在则添加
void Link_list::Link_updata(item it)
{
    
}





