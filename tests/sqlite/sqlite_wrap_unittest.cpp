#include <stdio.h>
#include "yh/yh.h"
#include "gtest/gtest.h"
#include "yh/sqlite/SqliteDriver.h"
#include "yh/sqlite/Statement.h"

USING_NS_YH_SQLITE;

class SqliteWrapTest :public testing::Test
{
protected:
	SqliteDriver* m_sqliteDriver;

	virtual void SetUp()
	{
		m_sqliteDriver = new SqliteDriver();
		m_sqliteDriver->init();
		m_sqliteDriver->connect("test2.db", "abcd",SQLITE_OPEN_READWRITE);
	}

	virtual void TearDown()
	{
		if (m_sqliteDriver != NULL)
		{
			m_sqliteDriver->close();
			delete m_sqliteDriver;
		}
	}

	virtual void CreateTable()
	{
		Statement stmt(*m_sqliteDriver, "SELECT count(*) FROM sqlite_master WHERE type = 'table' AND name = 'MyTable'");

		if (stmt.executeStep())
		{
			Column col = stmt.getColumn(0);
			int tableCount = col.getInt();
			if (tableCount == 0)
			{
				m_sqliteDriver->execute("create table MyTable(id integer primary key autoincrement,name varchar(100))");
			}
		}
	}

	virtual void TrunkTable()
	{
		m_sqliteDriver->execute("delete  from MyTable");
	}

	void CheckError(int errCode)
	{
		std::string s = m_sqliteDriver->errmsg();
		YHERROR("CheckError:%d,%s", errCode, s.c_str());
	}
};

//test create
TEST_F(SqliteWrapTest, CreateTable)
{
	int result;
	Statement stmt(*m_sqliteDriver, "SELECT count(*) FROM sqlite_master WHERE type = 'table' AND name = 'MyTable'");

	if (stmt.execute())
	{
		Column col = stmt.getColumn(0);
		int tableCount = col.getInt();
		if (tableCount == 0)
		{
			result = m_sqliteDriver->execute("create table MyTable(id integer primary key autoincrement,name varchar(100))");
			EXPECT_EQ(result, SQLITE_OK);

			Statement stmt(*m_sqliteDriver, "select * from MyTable");
			int column_count = stmt.getColumnCount();
			EXPECT_EQ(column_count, 2);
		}
	}
}

//test read
TEST_F(SqliteWrapTest, InsertData) {

	CreateTable();

	m_sqliteDriver->execute("insert into MyTable(name) values('aaa')");

	Statement stmt(*m_sqliteDriver, "select * from MyTable");

	if (stmt.executeStep())
	{
		ASSERT_STREQ(stmt.getColumn(1).getText(), "aaa");
	}

	TrunkTable();
}

