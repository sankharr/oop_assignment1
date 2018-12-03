#include<iostream>
#include<fstream>

using namespace std;

int main() {

    ifstream infile("subjdata.txt");
    int a,b;
    while(infile >> a >> b){
        cout << a << " - " << b;
    }

//    ifstream myReadFile;
//    myReadFile.open("subjdata.txt");
//    char output[100];
//    if (myReadFile.is_open()) {
//        while (!myReadFile.eof()) {
//
//
//            myReadFile >> output;
//            cout<<output;
//
//
//        }
//    }
//    myReadFile.close();
    return 0;
}