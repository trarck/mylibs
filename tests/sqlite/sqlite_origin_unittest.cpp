
#include <stdio.h>
#include "yh/yh.h"
#include "gtest/gtest.h"

USING_NS_YH;

class SqliteOriginTest :public testing::Test
{
protected:
	virtual void SetUp()
	{
		int ret = sqlite3_open_v2("test.db", &m_db, SQLITE_OPEN_READWRITE, NULL);
		if (ret != SQLITE_OK)
		{
			std::string s = sqlite3_errmsg(m_db);
			YHERROR("Open db error:%d,%s", ret, s.c_str());
			sqlite3_close(m_db);
			return;
		}
		sqlite3_key(m_db, "abcd", 4);
	}

	virtual void TearDown()
	{
		int ret = sqlite3_close(m_db);
		CheckError(ret);
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
		sqlite3_exec(m_db, "delete from MyTable", NULL, NULL, &error);
	}

	void CheckError(int errCode)
	{
		std::string s = sqlite3_errmsg(m_db);
		YHERROR("Open db error:%d,%s", errCode, s.c_str());
	}
	sqlite3* m_db;
};

TEST_F(SqliteOriginTest, CreateTable)
{
	int result = 0;
	char* error;

	sqlite3_stmt *statement;

	//create table
	//check have table
	sqlite3_prepare_v2(m_db, "SELECT count(*) FROM sqlite_master WHERE type = 'table' AND name = 'MyTable'", -1, &statement, NULL);
	sqlite3_step(statement);

	int tableCount = sqlite3_column_int(statement, 0);

	if (tableCount == 0) {
		result = sqlite3_exec(m_db, "create table MyTable(id integer primary key autoincrement,name varchar(100))", NULL, NULL, &error);
		EXPECT_EQ(result, SQLITE_OK);

		int res = sqlite3_prepare_v2(m_db, "select * from MyTable", -1, &statement, NULL);
		int column_count = sqlite3_column_count(statement);
		EXPECT_EQ(column_count, 2);
	}
	//must finalize statement; 
	sqlite3_finalize(statement);
}

//test read
TEST_F(SqliteOriginTest, InsertData) {

	int result = 0;
	char* error;
	sqlite3_stmt *statement;

	CreateTable();

	result=sqlite3_exec(m_db, "insert into MyTable(name) values('aaa')", NULL, NULL, &error);

	CheckError(result);

	result = sqlite3_exec(m_db, "select * from MyTable", NULL, NULL, &error);

	result = sqlite3_prepare_v2(m_db, "select * from MyTable", -1, &statement, NULL);


	result = sqlite3_step(statement);
	if (result != SQLITE_OK)
	{
		YHERROR("sqlite3_step error:%d,%s", result, sqlite3_errmsg(m_db));
	}
	TrunkTable();
	YHDEBUG("Test:%s", (const char*)sqlite3_column_text(statement, 1));
	ASSERT_STREQ((const char*)sqlite3_column_text(statement, 1), "aaa");
}

