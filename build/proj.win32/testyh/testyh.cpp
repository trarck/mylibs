// testyh.cpp : 定义控制台应用程序的入口点。
//

#include <stdio.h>
#include <tchar.h>
#include <yh/yh.h>

#include "yh/securesqlite3/sqlite3.h"

USING_NS_YH;
typedef yh::ds::LinkedList<int> MyList;

typedef std::vector<int> MyListA;

static MyList gl;

void funa()
{
	for (MyList::iterator iter=gl.begin();iter!=gl.end();++iter)
	{
		printf("a:%d",*iter);
		if (*iter==4)
		{
			iter=gl.erase(iter);
			--iter;
			//break;
		}
	}
}

void funb()
{
	for (MyList::iterator iter=gl.begin();iter!=gl.end();++iter)
	{
		printf("b:%d",*iter);
		if (*iter==5)
		{
			iter=gl.erase(iter);
			--iter;
		}
	}
}

void testList()
{
	for (int i = 1; i < 10; i++)
	{
		gl.push_back(i);
	}

	//int j=0;
	//for (MyList::Iterator iter=l.begin();iter!=l.end();++iter)
	//{
	//	
	//	if (*iter==4)
	//	{
	//		MyList::Iterator tmp=iter;
	//		iter=l.erase(iter);
	//		l.erase(tmp+1);
	//		//l.erase(iter+2);
	//	}
	//	j++;
	//	printf("%d",*iter);
	//}
	//printf("\n");
	//for (MyList::Iterator iter=l.begin();iter!=l.end();++iter)
	//{
	//	printf("%d",*iter);
	//}

	//MyList copy=gl;

	for (MyList::reverse_iterator iter = gl.rbegin(); iter != gl.rend(); ++iter)
	{
		printf("%d", *iter);
		//MyList::iterator next=iter+1;
		if (*iter == 4)
		{

			//funa();
			//
			//funb();
		}

		//iter=next;
	}

	printf("\n");

	for (MyList::iterator iter = gl.begin(); iter != gl.end(); ++iter)
	{
		printf("%d", *iter);
	}
}


void testSecSqlite()
{
	int result = 0;

	//    sqlite3 *db=NULL;
	//    
	//    result=sqlite3_open("test.db",&db);
	//    result=sqlite3_key(db,"abcd",3); //使用密码，第一次为设置密码
	//    //result=sqlite3_rekey(db,NULL,0); //清空密码
	//    result=sqlite3_exec(db,"PRAGMA synchronous = OFF",0,0,0);    //提高性能
	//    result=sqlite3_exec(db,"PRAGMA cache_size = 8000",0,0,0); //加大缓存
	//    result=sqlite3_exec(db,"PRAGMA count_changes = 1",0,0,0); //返回改变记录数
	//    result=sqlite3_exec(db,"PRAGMA case_sensitive_like = 1",0,0,0); //支持中文LIKE查询
	//    
	//    result=sqlite3_exec(db,"CREATE TABLE [MyTable] ([ID] INTEGER PRIMARY KEY NOT NULL,[MyText] TEXT NULL)",0,0,0);
	//    result=sqlite3_exec(db,"INSERT INTO MyTable (MyText) VALUES ('测试!')",0,0,0);
	//    
	//    result=sqlite3_close(db);


	sqlite3 *database = NULL;
	char* error;

	sqlite3_open("test.db", &database);

	result = sqlite3_key(database, "abcd", 4);

	//    result=sqlite3_rekey(database,"abcd",4);

	printf("set key result:%d\n", result);

	char sql[100];
	sqlite3_stmt *statement;

	//create table
	//check have table
	sqlite3_prepare_v2(database, "SELECT count(*) FROM sqlite_master WHERE type = 'table' AND name = 'MyTable'", -1, &statement, NULL);
	if (sqlite3_step(statement) == SQLITE_ROW) {
		int tableCount = sqlite3_column_int(statement, 0);
		printf("Have MyTable %s\n", tableCount > 0 ? "true" : "false");

		if (tableCount == 0) {
			result = sqlite3_exec(database, "create table MyTable(id integer primary key autoincrement,name varchar(100))", NULL, NULL, &error);
			if (result != SQLITE_OK) {
				printf(error);
				sqlite3_close(database);
				database = NULL;
				return;
			}
		}
	}

	sqlite3_exec(database, "insert into MyTable(name) values('aaa')", NULL, NULL, &error);

	sprintf(sql, "select * from %s", "MyTable");
	
	int res = sqlite3_prepare_v2(database, sql, -1, &statement, NULL);

	printf("sqlite3_prepare_v2 result:%d\n", res);

	int column_count = sqlite3_column_count(statement);
	printf("select %d columns:\n", column_count);
	int i;
	for (i = 0; i < column_count; ++i) {
		printf("%s\t", sqlite3_column_name(statement, i));
	}
	printf("\n");
	printf("show Record:\n");
	while (sqlite3_step(statement) == SQLITE_ROW) {
		for (i = 0; i < column_count; ++i) {
			printf("%s\t", sqlite3_column_text(statement, i));
		}
		printf("\n");
	}
	
	sqlite3_exec(database, sql, NULL, NULL, &error);

	sqlite3_close(database);
	database = NULL;
}


int _tmain(int argc, _TCHAR* argv[])
{
    YHDEBUG("hello world");
	testSecSqlite();
	
    
    getchar();
    return 0;
}

