# SuperMarketSystem
A School Homework

目前数据是有两种存在的方式，第一种是缓存，关闭程序后会刷新，第二种是文件，关闭程序后不会刷新；
下面讲解整个结构

Problem 1:

    item ：一个类，类中有一个构造函数 里面的信息有：编号 名称 生产日期 保质期（天） 价格 数量

Problem 2:

    Link_list ：一个类（跟结构体有类似的地方），它是一个链表，用来临时存储数据；
    创造一个链表：
    代码示例： Link_list mylist;  注：一个链表刚实例化出来时是空！就是里面没有内容
    该类中有以下函数：
     	void Link_add(item it);
		void Link_delete(string NO);
		void Link_updata(item it);
		void Link_show();
		void Link_find(string NO);

    void Link_add(item it):
        往一个链表中加入一个物品

        代码示例：mylist.Link_add(item("111", "11", "1", 1, 1, 1));

        mylist是我们实例化的一个链表对象，我们可以在后面加一个.来调用其中的类函数，这里就是调用的
        Link_add(item it);这个函数，这个函数有一个item类参数，添加时需要给item添加信息。
    
    void Link_delete(string NO):
        删除链表中的一个物品

        代码示例: mylist.Link_delete("111");

        目前·只能按编号查找并删除，传入编号就好了，会自己删除对应的物品。

    void Link_show()
        显示对应链表的所有存储信息

        代码示例 mylist.Link_show();

        直接展示，没什么好说的。

    void Link_find(string NO)
        按编号查询物品，会直接展示对应的物品。

        代码示例：mylist.Link_find("111");

        很简单，不做多解释。


Problem 3:

    file_set ：一个进行文件操作的类。

    	void fset(Link_list* list,string filename);
		void fget(Link_list* list,string filename);

    使用前要先创造一个流对象。

    代码示例：file_set myfile;

    void fset(Link_list* list,string filename)
    这个函数可以将链表中的数据存储到文件中，参数有两个，list类的一个指针，以及要保存为文件的名字。

    代码示例：myfile.fset(&mylist,"data.txt:");

    保存出的文件为txt文本文件，一定要加后缀，这里我们保存的为文本文件，并不是二进制文件。若事先已经存在
    "data.txt"文件，会先将data.txt文件删除，再创造一个新的data.txt文件。原data.txt文件中的内容不会
    保留。

    void fget(Link_list* list,string filename)
    这个函数可以将文件中的信息解析到链表中，其中链表必须为空！！！！！！

    代码示例：mylist.fset(&mylist,"data.txt");

