#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<filesystem>
using namespace std;

	//类的声明
	class item
	{
	public:
		item() {};
		item(string NO, string name, string fday, double daylong, double money, double number);

	public:
		string NO;
		string name;
		string f_day;
		double day_long;
		double money;
		double number;
		void show_it();
		void item_updata_name(string newname);
		void item_updata_fday(string newfday);
		void item_updata_daylong(double newdaylong);
		void item_updata_money(double newmoney);
		void item_updata_number(double newnumber);

	};
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
	class file_set
	{
	public:
		void fset(Link_list* list);
		Link_list* fget(Link_list* list,string filename);
	};
	class Windows_set
	{
	public:

	};

	//类的实现
	item::item(string NO, string name, string fday, double daylong, double money, double number)
	{
		this->NO = NO;
		this->name = name;
		this->f_day = fday;
		this->day_long = daylong;
		this->money = money;
		this->number = number;
	}
	void item::show_it()
	{
		cout << "编号:" << NO << endl;
		cout << "名称:" << name << endl;
		cout << "生产日期:" << f_day << endl;
		cout << "保质期:" << day_long << endl;
		cout << "价格:" << money << endl;
		cout << "数量:" << number << endl;
		cout << endl;
	}
	void item::item_updata_name(string newname)
	{
		name = newname;
	}
	void item::item_updata_fday(string newfday)
	{
		f_day = newfday;
	}
	void item::item_updata_daylong(double newdaylong)
	{
		day_long = newdaylong;
	}
	void item::item_updata_money(double newmoney)
	{
		money = newmoney;
	}
	void item::item_updata_number(double newnumber)
	{
		number = newnumber;
	}
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
	Link_part::Link_part()
	{
		this->next = nullptr;
	}
	Link_part* find_NULL(Link_part* head)
	{
		if (head == nullptr)
			return nullptr;
		Link_part* current = head;
		while (current->next != nullptr)
			current = current->next;
		return current;
	}
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
	Link_list::Link_list()
	{
		head = nullptr;
		Long = 0;
	}
	void Link_list::Link_add(item it)
	{
		Link_part* newpart = new Link_part;
		newpart->it = it;
		newpart->next = NULL;
		if (head == NULL)
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
	void Link_list::Link_show()
	{
		Link_part* part = head;
		while (part != nullptr)
		{
			part->it.show_it();
			part = part->next;
		}
	}
	void Link_list::Link_updata(item it)
	{

	}
	void file_set::fset(Link_list* list)
	{
		_FILESYSTEM_::remove("data.txt");
		fstream fs;
		//
		if (!fs.is_open()) 
		{
			cerr << "无法打开文件！" << endl;
			return;
		}
		//
		fs.open("data.txt", ios::out);
		Link_part* current = list->head;
		while (current != NULL) 
		{
			fs  << current->it.NO << " "
				<< current->it.name << " "
				<< current->it.f_day << " "
				<< current->it.day_long << " "
				<< current->it.money << " "
				<< current->it.number << endl;
			current = current->next;
		}
		fs.close();
	}
	Link_list* file_set::fget(Link_list* list,string filename)
	{	
		//
		if (list->head != NULL)
		{
			cout << "给予的链表必须为空" << endl;
		}
		//
		else
		{	
			cout<<"打开";
			fstream fs;
			if (!fs.is_open()) 
			{
				cerr << "无法打开文件！" << endl;
				return;
			}
			fs.open(filename, ios::in);
			string information;
			while (getline(fs, information))
			{
				istringstream iss(information);
				string NO, name, f_day;	
				double day_long, money, number;
				iss >> NO >> name >> f_day >> day_long >> money >> number;
				list->Link_add(item(NO, name, f_day, day_long, money, number));
			}
			fs.close();
		}		
	}

int main()
{
	Link_list list;
	Link_list list2;
	list.Link_add(item("111", "11", "1", 1, 1, 1));
	list.Link_add(item("222", "22", "2", 2, 2, 2));
	list.Link_add(item("333", "33", "3", 3, 3, 3));
	list.Link_add(item("444", "44", "4", 4, 4, 4));
	file_set fs;
	list.Link_delete("333");
	fs.fset(&list);
	fs.fget(&list2, "data.txt");
	list2.Link_show();
}
