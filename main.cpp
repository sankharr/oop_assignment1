#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

int size; //this is declared here to be used for the details_array in "subject" struct;
int main_count = -1; //for main_array
int sub_count = 0;
int after_s = 0;
int loop_count;
int index_mark = 0;
int str_int;

struct student{
    int student_id;
    int student_mark;
};

struct subject_struct{         //if this method doesnt work, you can declare a details array with a constant number of elements. so ones you exceeded that number,
    string subject_code;
    int num_students;
    struct student details_array[20];
};

struct subject_struct subject_array[20];

class subject{
private:
public:
//    void readingFromText();
//    void storingData();
//    void displaySubject();
//    void splitting_strings(string);
};

void storingData();
//void storingData();
void displaySubject();
void splitting_strings(string);

void splitting_strings(string str) {
    //using namespace std;
    istringstream iss(str);    //this code portion split up a string into different strings using spaces
    string s;
    while (getline(iss, s, ' ')) {
        //printf( "`%s'\n", s.c_str() );
        //str_int = atoi(s.c_str());

        if (s[0] == 'S') {

            sub_count = 0;
            main_count++;
            subject_array[main_count].subject_code = s;
            after_s = 1;

        }
        else{
            stringstream geek(s);
            geek >> str_int;
            if (after_s == 1) {
                loop_count = str_int;
                subject_array[main_count].num_students = str_int;
                after_s = 0;
            }
            else if (index_mark == 0) {
                subject_array[main_count].details_array[sub_count].student_id = str_int;
                index_mark = 1;
            }
            else if (index_mark == 1) {
                subject_array[main_count].details_array[sub_count].student_mark = str_int;
                index_mark = 0;
                sub_count++;
            }
        }

    }
}

void storingData() {


    //int sub_count = 0;

    FILE* fp = fopen("subjdata.txt", "r");    //reading from a text file
    if (fp == NULL)
        exit(EXIT_FAILURE);

    char* line = NULL;
    size_t len = 0;
    while ((getline(&line, &len, fp)) != -1) {
        // using printf() in all tests for consistency
        //printf("%s", line);
//        if(line[0]=='S'){
//            count = 0;
//        }
//        //else if{index_mark){
//
//        }
        splitting_strings(line);

    }
    fclose(fp);
    if (line)
        free(line);
}



//void subject::displaySubject() {
//    cin >>
//}
int main() {
    storingData();
    cout << "Hello, World!" << endl;

    return 0;
}