#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <string>
#include <ctime>
#include <iostream>
#include <cstdlib>
#include <sqlite3.h> 
#include "hash-library/keccak.h"



using namespace std;

string datos = "";

static int callback(void *data, int argc, char **argv, char **azColName){
   int i;
   fprintf(stderr, "%s: ", (const char*)data);
   string probar = "";
   for(i = 0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
      //lmgtfy.com
      datos = datos + (argv[i] ? argv[i] : "NULL");
      
      
   }
   cout << probar << endl;
   printf("\n");
   return 0;
}

void CrearBd(string name){

sqlite3 *db;
char *zErrMsg = 0;
int rc;
string sql;
rc = sqlite3_open(("/home/administrador/Desktop/EVMC-host/TrieExample/"+name+".db").c_str(), &db);

if( rc ) {
	fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	return;
} else {
	fprintf(stderr, "Opened database successfully\n");
	}

/* Create SQL statement */
sql = "CREATE TABLE STORAGE("  \
      "KEY BLOB(32) PRIMARY KEY     NOT NULL," \
      "VALUE          BLOB(32)  );";
rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &zErrMsg);
if( rc != SQLITE_OK ){
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
} else {
    fprintf(stdout, "Table created successfully\n");
   }
sqlite3_close(db);
}

void consultar(){

   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   string sql;
   const char* data = "Callback function called";

   /* Open database */
   rc = sqlite3_open("test3.db", &db);
   
   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return;
   } else {
      fprintf(stderr, "Opened database successfully\n");
   }

      /* Create SQL statement */
   sql = "SELECT * from STORAGE order by id";


  /* Execute SQL statement */
   rc = sqlite3_exec(db, sql.c_str(), callback, (void*)data, &zErrMsg);
   
   if( rc != SQLITE_OK ) {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Operation done successfully\n");
   }
   sqlite3_close(db);
}

/*string hashBd(){

Keccak keccak;
string hash = keccak(datos.c_str(), datos.size());
return hash;

}*/

int main(){

string name;
cout << "Ingrese nombre de la base de datos" << endl;
cin >> name;
CrearBd(name);
//consultar();
//cout << endl << "El resultado es: " << datos << endl << "hash: " << hashBd() << endl;






	return 0;
}