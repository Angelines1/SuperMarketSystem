#include<iostream>
#include"items.h"
using namespace std;

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
	cout << "���:" << NO << endl;
	cout << "����:" << name << endl;
	cout << "��������:" << f_day << endl;
	cout << "������:" << day_long << endl;
	cout << "�۸�:" << money << endl;
	cout << "����:" << number << endl;	
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