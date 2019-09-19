#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <string>
#include <ctime>
#include <iostream>
#include <cstdlib>
#include <leveldb/db.h>

using namespace std;
using namespace leveldb;

void CrearBd(string cuenta){
    
    string name = "Prueba.db";
    DB* db;
    Options options;
    options.create_if_missing = true;
    Status s = DB::Open(options, name, &db);
    assert(s.ok());


}

int main(){

/*string Prueba;
cout << "Ingrese el nombre" << endl;
cin >> Prueba;*/

//CrearBd("Prueba");
string valor, aux;
DB* db;
Options options;
//options.create_if_missing = true;
Status s = DB::Open(options, "Contract.db", &db);
assert(s.ok());
//if (s.ok()) s = db->Put(WriteOptions(), "1015", "Preeba");
//if (s.ok()) s = db->Put(WriteOptions(), "15151", "Final");
//s = db->Get(ReadOptions(), "1010", &valor);
//s = db->Get(ReadOptions(), "1011", &aux);

//cout << "AHORA imprime " << valor << "  " << aux <<endl;
leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
for (it->SeekToFirst(); it->Valid(); it->Next()) {
  cout << it->key().ToString() << ": "  << it->value().ToString() << endl << endl;
}
assert(it->status().ok());  // Check for any errors found during the scan
delete it;

	return 0;
}
