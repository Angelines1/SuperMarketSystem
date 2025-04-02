#include <iostream>
#include <string>
#include "Link.h"
using namespace std;

// �����������ͷ����нڵ�
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

// ���캯����ʼ���ڵ�
Link_part::Link_part()
{
    this->next = nullptr;
}

// �����������ҵ�����ĩβ�ڵ�
Link_part* find_NULL(Link_part* head)
{
    if (head == nullptr)
        return nullptr;
    Link_part* current = head;
    while (current->next != nullptr)
        current = current->next;
    return current;
}

// �����������ҵ�ָ��NO�ڵ��ǰ��
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

// ��ʼ���������ù��캯�������
Link_list::Link_list()
{
    head = nullptr;
    Long = 0;
}

// ��ӽڵ㵽����ĩβ
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

// ɾ��ָ��NO�Ľڵ�
void Link_list::Link_delete(string NO)
{
    if (head == nullptr)
        return;

    // ����ͷ�ڵ�
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

// ���Ҳ���ʾ�ڵ���Ϣ
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

// ��ʾ���нڵ���Ϣ
void Link_list::Link_show()
{
    Link_part* part = head;
    while (part != nullptr) 
    {
        part->it.show_it();
        part = part->next;
    }
}

// ���½ڵ���Ϣ���������������
void Link_list::Link_updata(item it)
{
    
}





