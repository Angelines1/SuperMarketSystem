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
	cout << "编号:" << NO << endl;
	cout << "名称:" << name << endl;
	cout << "生产日期:" << f_day << endl;
	cout << "保质期:" << day_long << endl;
	cout << "价格:" << money << endl;
	cout << "数量:" << number << endl;	
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