#include "SqliteDriver.h"
#include "Statement.h"

#ifndef SQLITE_DETERMINISTIC
#define SQLITE_DETERMINISTIC 0x800
#endif //SQLITE_DETERMINISTIC

USING_NS_YH;

NS_YH_SQLITE_BEGIN

SqliteDriver::SqliteDriver()
:m_db(NULL)
,m_dbPath("")
{
    
}

SqliteDriver::~SqliteDriver()
{
    //if not close,then close connect
    close();
}

bool SqliteDriver::init()
{
    return true;
}

bool SqliteDriver::connect(const std::string& dbPath,const int flag)
{
	int ret = sqlite3_open_v2(dbPath.c_str(), &m_db, flag, NULL);
	if(SQLITE_OK != ret)
	{
		//show error
		const char* strerr = sqlite3_errmsg(m_db);
		YHERROR(strerr);
		sqlite3_close(m_db); // close is required even in case of error on opening
		return false;
	}
	return true;
}

bool SqliteDriver::connect(const std::string& dbPath, const std::string& password ,const int flag)
{
	int ret = sqlite3_open_v2(dbPath.c_str(), &m_db, flag, NULL);
	if(SQLITE_OK == ret)
	{
		#ifdef SQLITE_HAS_CODEC
		ret = sqlite3_key(m_db, password.c_str(), password.length());
		if (SQLITE_OK == ret) {
			return true;
		}
		#endif //SQLITE_HAS_CODEC
	}

	//show error
	const char* strerr = sqlite3_errmsg(m_db);
	YHERROR(strerr);
	sqlite3_close(m_db); // close is required even in case of error on opening
	return false;
}

void SqliteDriver::close()
{
    if (m_db) {
        int ret = sqlite3_close(m_db);
		if (ret != SQLITE_OK)
		{
			YHERROR("close error:%d,%s",ret, sqlite3_errmsg(m_db));
		}
        m_db=NULL;
    }
}

int SqliteDriver::execute(
	const char* query,		/* SQL to be evaluated */
	int(*callback)(void*, int, char**, char**),	 /* Callback function */
	void * callbackFirstData,                                    /* 1st argument to callback */
	char **errmsg                              /* Error msg written here */
)
{
	int ret = sqlite3_exec(m_db, query, callback, callbackFirstData, errmsg);

	check(ret);

	// Return the number of rows modified by those SQL statements (INSERT, UPDATE or DELETE)
	return sqlite3_changes(m_db);
}

Column SqliteDriver::fetchFirstColumn(const char* sqlStr)
{
    Statement queryStmt(*this, sqlStr);
    (void)queryStmt.executeStep(); // Can return false if no result, which will throw next line in getColumn()
    return queryStmt.getColumn(0);
}

bool SqliteDriver::tableExists(const std::string& tableName)
{
    Statement queryStmt(*this, "SELECT count(*) FROM sqlite_master WHERE type='table' AND name=?");
    queryStmt.bind(1, tableName);
    (void)queryStmt.executeStep(); // Cannot return false, as the above query always return a result
    int result = queryStmt.getColumn(0);
    return (1 == result);
}

void SqliteDriver::check(const int ret) const
{
    if (SQLITE_OK != ret)
    {
		YHERROR("SqliteDriver::check err:%s",sqlite3_errmsg(m_db));
    }
}

void SqliteDriver::createFunction(const char*    funcName,
                           int                  arg,
                           bool                 deterministic,
                           void*                app,
                           void               (*func)(sqlite3_context *, int, sqlite3_value **),
                           void               (*step)(sqlite3_context *, int, sqlite3_value **),
                           void               (*final)(sqlite3_context *),
                           void               (*destroy)(void *))
{
    int TextRep = SQLITE_UTF8;
    // optimization if deterministic function (e.g. of nondeterministic function random())
    if (deterministic) {
        TextRep = TextRep|SQLITE_DETERMINISTIC;
    }
    
    int ret = sqlite3_create_function_v2(m_db, funcName, arg, TextRep,
                                         app, func, step, final, destroy);
    
    check(ret);
}

NS_YH_SQLITE_END