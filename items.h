#ifndef ITEMS_H
#define ITEMS_H
#include<string>	
using namespace std;


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




#endif // ITEMS_H
