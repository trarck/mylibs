
#include <stdio.h>
#include "yh/yh.h"
#include "gtest/gtest.h"

USING_NS_YH;
class SqliteTest:public testing::Test
{
protected:
	virtual void SetUp()
	{
		sqlite3_open("sqlite/test.db", &m_db);

		sqlite3_key(m_db, "abcd", 4);
	}

	virtual void TearDown()
	{
		sqlite3_close(m_db);
	}

	virtual void CreateTable()
	{
		sqlite3_stmt *statement;
		char* error;
		//create table
		//check have table
		sqlite3_prepare_v2(m_db, "SELECT count(*) FROM sqlite_master WHERE type = 'table' AND name = 'MyTable'", -1, &statement, NULL);
		if (sqlite3_step(statement) == SQLITE_ROW) {
			int tableCount = sqlite3_column_int(statement, 0);

			if (tableCount == 0) {
				sqlite3_exec(m_db, "create table MyTable(id integer primary key autoincrement,name varchar(100))", NULL, NULL, &error);				
			}
		}
	}

	virtual void TrunkTable()
	{
		char* error;
		sqlite3_exec(m_db, "delete * from MyTable", NULL, NULL, &error);
	}
	sqlite3* m_db;
};

//sqlite 不支持并发操作，估计这是是多线程跑Test
TEST_F(SqliteTest,CreateTable)
{
	int result = 0;
	char* error;

	sqlite3_stmt *statement;

	//create table
	//check have table
	sqlite3_prepare_v2(m_db, "SELECT count(*) FROM sqlite_master WHERE type = 'table' AND name = 'MyTable'", -1, &statement, NULL);
	EXPECT_EQ(sqlite3_step(statement), SQLITE_ROW);
	
	int tableCount = sqlite3_column_int(statement, 0);

	if (tableCount == 0) {
		result = sqlite3_exec(m_db, "create table MyTable(id integer primary key autoincrement,name varchar(100))", NULL, NULL, &error);
		EXPECT_EQ(result, SQLITE_OK);

		int res = sqlite3_prepare_v2(m_db, "select * from MyTable", -1, &statement, NULL);
		int column_count = sqlite3_column_count(statement);
		EXPECT_EQ(column_count, 2);
	}	
}

//test read
TEST_F(SqliteTest, InsertData) {

	int result = 0;
	char* error;
	sqlite3_stmt *statement;

	CreateTable();

	result=sqlite3_exec(m_db, "insert into MyTable(name) values('aaa')", NULL, NULL, &error);


	result = sqlite3_prepare_v2(m_db, "select * from MyTable", -1, &statement, NULL);


	result = sqlite3_step(statement);
	ASSERT_STREQ((const char*)sqlite3_column_text(statement, 1), "aaa");

	TrunkTable();
}

