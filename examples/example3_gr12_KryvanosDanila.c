#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int main(int argc, char* argv[]) {
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char *sql;

   rc = sqlite3_open("test.db", &db);
   
   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   } else {
      fprintf(stderr, "Opened database successfully\n");
   }

   /* Create SQL statement */
   sql = "INSERT INTO Patient (ID,NAME,SURNAME,AGE,DEPARTMENT,DIAGNOSIS) "  \
         "VALUES (1, 'John', 'Doe', 35, 'Cardiology', 'Myocardial Infarction'); " \
         "INSERT INTO COMPANY (ID,NAME,SURNAME,AGE,DEPARTMENT,DIAGNOSIS) "  \
         "VALUES (2, 'Jane', 'Smith', 42, 'Oncology', 'Breast Cancer'); "     \
         "INSERT INTO COMPANY (ID,NAME,SURNAME,AGE,DEPARTMENT,DIAGNOSIS)" \
         "VALUES (3, 'James', 'Johnson', 26, 'Pediatrics', 'Influenza');" \
         "INSERT INTO COMPANY (ID,NAME,SURNAME,AGE,DEPARTMENT,DIAGNOSIS)" \
         "VALUES (4, 'Emily', 'Davis', 51, 'Gastroenterology', 'Gastritis');";

   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Records created successfully\n");
   }
   sqlite3_close(db);
   return 0;
}