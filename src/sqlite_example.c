#include <stdio.h>
#include <sqlite3.h> 
#include <stdlib.h>
#include "sqlite_example.h"

static int callback(void *NotUsed, int argc, char **argv, char **azColName);
int create_table(sqlite3 *db);
int insert_data(sqlite3 *db);
int select_data(sqlite3 *db);

int main(int argc, char* argv[])
{

   sqlite3 *db; // Pointer to database handler
   char * database_name = "test.db"; // Name of database file

   // Use command line argument as database file name
   if( argc == 2)
      database_name = argv[1];

   rc = sqlite3_open("test.db", &db); // Open the database, or create one if it doesnt exist

   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      exit(0);
   }else{
      fprintf(stderr, "Opened %s database successfully\n", database_name);
   }

   create_table(db);

   insert_data(db);

   select_data(db);

   sqlite3_close(db);
}

// Create a database
int create_table(sqlite3 *db){

   /* Create SQL statement */
   sql = "CREATE TABLE COMPANY("  \
         "ID INT PRIMARY KEY     NOT NULL," \
         "NAME           TEXT    NOT NULL," \
         "AGE            INT     NOT NULL," \
         "ADDRESS        CHAR(50)," \
         "SALARY         REAL );";
   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

   if( rc != SQLITE_OK ){
   fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
      return 0;
   }else{
      fprintf(stdout, "Table created successfully\n");
      return 1;
   }
}

// Insert data into the table
int insert_data(sqlite3 *db){

   /* Create SQL statement */
   sql = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
         "VALUES (1, 'Paul', 32, 'California', 20000.00 ); " \
         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
         "VALUES (2, 'Allen', 25, 'Texas', 15000.00 ); "     \
         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
         "VALUES (3, 'Teddy', 23, 'Norway', 20000.00 );" \
         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
         "VALUES (4, 'Mark', 25, 'Rich-Mond ', 65000.00 );";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
      return 0;
   }else{
      fprintf(stdout, "Records created successfully\n");
      return 1;
   }
}

int select_data(sqlite3 *db){

   /* Create SQL statement */
   const char* data = "Callback function called";
   sql = "SELECT * from COMPANY";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);

   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
      return 0;
   }else{
      fprintf(stdout, "Operation done successfully\n");
      return 1;
   }

}

// Callback to be executed after function is complete
static int callback(void *NotUsed, int argc, char **argv, char **azColName){
   
   int i;
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }

   printf("\n");
   return 0;
}