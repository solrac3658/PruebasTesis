#include <iostream>   ////// Compilaar  g++ -o mc mainComprimir.cpp zip.cpp -std=c++11 -I . -DPARTIO_USE_ZLIB `pkg-config zlib --libs` -l leveldb
#include <cstdio>
#include <string>
#include <cstdlib>
#include <cstdint>
#include <dirent.h>
#include <cstring>
#include <unistd.h>
#include <vector>
#include <sys/stat.h> 
#include <sys/types.h> 
#include <fstream>
#include <leveldb/db.h>

#include "ZIP.h"


using namespace std;
using Partio::ZipFileWriter;
using Partio::ZipFileReader;

void readCompleteFileToStream(std::ostream * o, const char * path) {

	FILE * f = fopen(path, "rb");

	if (f == NULL) {
		cerr << "FILE IS NULL!" << endl;
		exit(1);
	}

	do {
		uint8_t b = fgetc(f);
		if (feof(f))
			break;
		*o << b;
	} while (!feof(f));

	fclose(f);
}


void CrearDirectorio(){


    if (mkdir("ContractdbNodo.db", 0777) == -1) 
        cerr << "Error :  " << strerror(errno) << endl; 
    else
        cout << "Directory created"; 
}

void ActulizarContractdb(){

	string valorOld = "vacio", clave, valorNew;
	leveldb::DB* dbNew;
	leveldb::DB* dbOld;
	leveldb::Options options;
	leveldb::Status s = leveldb::DB::Open(options, "ContractdbNodo.db", &dbNew);
	assert(s.ok());
	s = leveldb::DB::Open(options, "Contract.db", &dbOld);
	assert(s.ok());
	
	leveldb::Iterator* it = dbNew->NewIterator(leveldb::ReadOptions());

	for (it->SeekToFirst(); it->Valid(); it->Next()) {
  	
  		clave = it->key().ToString();
  		valorNew =  it->value().ToString();
  		s = dbOld->Get(leveldb::ReadOptions(), clave, &valorOld);

  		if (valorOld=="vacio")
  			s = dbOld->Put(leveldb::WriteOptions(), clave, valorNew);

  		valorOld="vacio";	
	}
}

int main(){
	std::vector<std::string> filenames;
	ZipFileWriter *          zip = new ZipFileWriter("contractdbNew.zip");
	std::ostream  *          o;
	DIR *                    dir;
	struct dirent *          dp;
	char *                   file_name;
	char                     fullpath[PATH_MAX];
	ofstream 				 myfile;
	int 					 c;
	std::istream * 			 i;
	char 					 byte;


	dir = opendir("Contract.db");
	
	while ((dp = readdir(dir)) != NULL) {
		if (strcmp(dp->d_name, ".") && strcmp(dp->d_name, "..")) {
	        
	        file_name = dp->d_name;
	        memset(fullpath, '\0', sizeof(char) * PATH_MAX);
	        sprintf(fullpath, "%s/%s", "Contract.db", file_name);
	        o = zip->Add_File(file_name);
	        readCompleteFileToStream(o, fullpath);
	        delete o;
      }
	}

	closedir(dir);
  	delete zip;
	ZipFileReader zip2("contractdbNew.zip");
	zip2.Get_File_List(filenames);
  	CrearDirectorio();

  	for (string h : filenames) {

  		 i  = zip2.Get_File(h);
  		 h="ContractdbNodo.db/"+h;
         myfile.open(h);
         while (!i->eof()){
   			 c = i->peek();
   			 if (c == EOF)
				 break;
			 i->read(&byte, 1);
   	    	 myfile << byte;
  		}
  		myfile.close(); 	
  	}

  	ActulizarContractdb();
  	
	return 0;
}
