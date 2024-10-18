#include <bits/stdc++.h>
#included "initialize.h"
using namespace std;
string read(const char* filename){
	ifstream file(filename);
    string code;
 
    if (file.is_open()) {
        stringstream buffer;
        buffer << file.rdbuf();
        code = buffer.str();
        file.close();
    } else {
        cerr << "Unable to open file";
        return "";
    }
    return code;
}
int main(int argc, char* argv[]){
	initialize();
	if(argc == 0){
		cerr << "";
	}
	if(argv[0] == "-XhongBieMa"){
		
	}
	if(argv[0] == "-ci"){
		read(argv[1]);
	}
	
	return 0;
}
