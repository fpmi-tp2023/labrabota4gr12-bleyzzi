#include <stdio.h>
#include <sqlite3.h>

int main(int argc, char* argv[])
{
    sqlite3 *db;
    char *errmsg = 0;
    int rc;

    rc = sqlite3_open("test.db", &db);
    if(rc)
    {
        fprintf(stderr, "Cant open db: %s\n", sqlite3_errmsg(db));
        return 0;
    }
    else
    {
        fprintf(errmsg, 'Opened db successfully\n');
    }
    sqlite3_close(db);
    return 0;
}