#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char **argv){

	string fileName = argv[1];
	string line;
	ifstream testFile;
	testFile.open(fileName);
	if(testFile.is_open()){
		while ( getline(testFile,line)){
			cout << line << '\n';
		}
	}
	testFile.close();
	return 0;
}
