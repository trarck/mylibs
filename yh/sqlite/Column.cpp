#include "Column.h"

#include <iostream>


NS_YH_SQLITE_BEGIN

// Encapsulation of a Column in a row of the result pointed by the prepared Statement.
Column::Column(Statement::Ptr& stmtPtr, int index) : // nothrow
    m_stmtPtr    (stmtPtr),
    m_index      (index)
{
}

// Finalize and unregister the SQL query from the SQLite Database Connection.
Column::~Column(void)  // nothrow
{
    // the finalization will be done by the destructor of the last shared pointer
}

// Return the named assigned to this result column (potentially aliased)
const char * Column::getName(void) const  // nothrow
{
    return sqlite3_column_name(m_stmtPtr, m_index);
}

#ifdef SQLITE_ENABLE_COLUMN_METADATA
// Return the name of the table column that is the origin of this result column
const char * Column::getOriginName(void) const  // nothrow
{
    return sqlite3_column_origin_name(m_stmtPtr, m_index);
}
#endif

// Return the integer value of the column specified by its index starting at 0
int Column::getInt(void) const  // nothrow
{
    return sqlite3_column_int(m_stmtPtr, m_index);
}

// Return the 64bits integer value of the column specified by its index starting at 0
sqlite3_int64 Column::getInt64(void) const  // nothrow
{
    return sqlite3_column_int64(m_stmtPtr, m_index);
}

// Return the double value of the column specified by its index starting at 0
double Column::getDouble(void) const  // nothrow
{
    return sqlite3_column_double(m_stmtPtr, m_index);
}

// Return a pointer to the text value (NULL terminated string) of the column specified by its index starting at 0
const char* Column::getText(void) const  // nothrow
{
    return (const char*)sqlite3_column_text(m_stmtPtr, m_index);
}

// Return a pointer to the text value (NULL terminated string) of the column specified by its index starting at 0
const void* Column::getBlob(void) const  // nothrow
{
    return sqlite3_column_blob(m_stmtPtr, m_index);
}

// Return the type of the value of the column
int Column::getType(void) const  // nothrow
{
    return sqlite3_column_type(m_stmtPtr, m_index);
}

// Return the number of bytes used by the text value of the column
int Column::getBytes(void) const  // nothrow
{
    return sqlite3_column_bytes(m_stmtPtr, m_index);
}

// Standard std::ostream inserter
std::ostream& operator<<(std::ostream& stream, const Column& column)
{
    stream << column.getText();
    return stream;
}

NS_YH_SQLITE_END
