#include <ndb/engine/sql/sql.hpp>
#include <ndb/model.hpp>
#include <ndb/query.hpp>
#include <ndb/line.hpp>
#include <ndb/result.hpp>
#include <ndb/error.hpp>

namespace ndb
{
    sql::sql(const std::string& identifier) :
        engine(identifier),
        _db(nullptr)
    {}

    bool sql::connect()
    {
        bool db_exist = false;
        if (engine::exist()) db_exist = true; // if file doesn t exist, create nxs model

        if (sqlite3_open(engine::path().c_str(), &_db) == SQLITE_OK)
        {
            exec("PRAGMA foreign_keys = ON;");
            if (!db_exist)
            {
                model().make(*this);
                _init = true;
            }
            return true;
        }
        return false;
    }

    void sql::close()
    {

    }

    ndb::result<sql> sql::exec(ndb::query<sql>& q) const
    {
         sqlite3_stmt* statement;
        int step = SQLITE_DONE;
        ndb::result<sql> result;

        if(sqlite3_prepare_v2(_db, q.native().c_str(), -1, &statement, nullptr) == SQLITE_OK)
        {
            // bind values
            for (size_t i = 0; i != expression<sql>::value_list_.size(); i++)
            {
                const value<sql>& v = expression<sql>::value_list_[i];
                if (v.type() == SQLITE_INTEGER) sqlite3_bind_int(statement, i + 1, v.as_int());
                if (v.type() == SQLITE_FLOAT) sqlite3_bind_double(statement, i + 1, v.as_double());
                if (v.type() == SQLITE3_TEXT) sqlite3_bind_text(statement, i + 1, v.as_string().c_str(), -1, SQLITE_STATIC);
            }
            step = sqlite3_step(statement);

            result._add_id = sqlite3_last_insert_rowid(_db);

            // select
            while (step == SQLITE_ROW)
            {
                int nb_col = sqlite3_column_count(statement);
                ndb::line<sql> line;
                for(int col = 0; col < nb_col; col++)
                {
                    const char* col_name = sqlite3_column_name(statement, col);
                    int col_type = sqlite3_column_type(statement, col);
                    sqlite3_value* col_value = sqlite3_column_value(statement, col);

                    if (col_type == SQLITE_INTEGER) line.add(col_name, value<sql>(sqlite3_value_int(col_value)));
                    if (col_type == SQLITE_FLOAT) line.add(col_name, value<sql>(sqlite3_value_double(col_value)));
                    if (col_type == SQLITE_TEXT) line.add(col_name, value<sql>(std::string(reinterpret_cast<const char*>(sqlite3_value_text(col_value)))));
                }
                result.add(line);

                step = sqlite3_step(statement);
            }
            sqlite3_finalize(statement);
        }
        std::string error = sqlite3_errmsg(_db);
        if(error != "not an error") ndb_error(error + " : " + q.native());

        q.clear();
        return result;
    }

    ndb::result<sql> sql::exec(const typename setup<sql>::expression_type& str_query) const
    {
        sqlite3_stmt* statement;
        int step = SQLITE_DONE;
        ndb::result<sql> result;

        if(sqlite3_prepare_v2(_db, str_query.c_str(), -1, &statement, 0) == SQLITE_OK)
        {
            step = sqlite3_step(statement);

            // select
            while (step == SQLITE_ROW)
            {
                int nb_col = sqlite3_column_count(statement);
                ndb::line<sql> line;
                for(int col = 0; col < nb_col; col++)
                {
                    const char* col_name = sqlite3_column_name(statement, col);
                    int col_type = sqlite3_column_type(statement, col);
                    sqlite3_value* col_value = sqlite3_column_value(statement, col);

                    if (col_type == SQLITE_INTEGER) line.add(col_name, value<sql>(sqlite3_value_int(col_value)));
                    if (col_type == SQLITE_FLOAT) line.add(col_name, value<sql>(sqlite3_value_double(col_value)));
                    if (col_type == SQLITE_TEXT) line.add(col_name, value<sql>(std::string(reinterpret_cast<const char*>(sqlite3_value_text(col_value)))));
                }
                result.add(line);

                step = sqlite3_step(statement);
            }
            sqlite3_finalize(statement);
        }

        std::string error = sqlite3_errmsg(_db);
        if(error != "not an error") ndb_error(error);

        return result;
    }

} // ndb
