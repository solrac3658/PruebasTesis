#include <iostream>
#include <stdio.h> 
#include <unistd.h> 
#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <dirent.h>
#include <string>
#include <string.h>



using namespace std;


void deleteDirectory(string directory){

    DIR *                    dir;
    struct dirent *          dp;
    string                   file_name;

    dir = opendir(directory.c_str());
    
    while ((dp = readdir(dir)) != NULL) {
        if (strcmp(dp->d_name, ".") && strcmp(dp->d_name, "..")) {
            
            file_name = dp->d_name;
            file_name=directory+"/"+file_name;
            if (remove(file_name.c_str()) !=0)   // Remove the directory
                cerr << "Error1: " << strerror(errno) << endl;
        }
    }
    if (rmdir("ContractdbNodo.db") == -1)   // Remove the directory
        cerr << "Error: " << strerror(errno) << endl;
}

int main(int argc, char const *argv[])
{
    deleteDirectory("ContractdbNodo.db");
    return 0;
}