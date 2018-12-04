#include <sstream>
#include <string>
#include <fstream>
#include <iostream>

int main(){

    int count = 24/10;
    printf("%d\n",count);

//    using namespace std;
//    istringstream iss("17001439 67");    //this code portion split up a string into different strings using spaces
//    string s;
//    while ( getline( iss, s, ' ' ) ) {
//        int x = stoi(s.c_str());
//        printf( "`%d'\n", x );
//    }

//    FILE* fp = fopen("subjdata.txt", "r");    //reading from a text file
//    if (fp == NULL)
//        exit(EXIT_FAILURE);
//
//    char* line = NULL;
//    size_t len = 0;
//    while ((getline(&line, &len, fp)) != -1) {
//        // using printf() in all tests for consistency
//        printf("%s", line);
//
//    }
//    fclose(fp);
//    if (line)
//        free(line);
//
//    std::cout << "\n\ncount is - " << count;

    return 0;
}