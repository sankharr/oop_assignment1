#include <iomanip>
#include <iostream>
#include <sstream>
#include <zconf.h>

using namespace std;

int size; //this is declared here to be used for the details_array in "subject" struct;
int main_count = -1; //for main_array
int sub_count = 0;
int after_s = 0;
int loop_count;
int index_mark = 0;
int str_int;
string s_code;
int n_students = 0;
int main_count_increment = 0;
int sub_array_size = 10; //if you change the value here, you have to change the value in subject_struct as well.
int main_array_size = 20;
int option;

struct student{
    int student_id;
    int student_mark;
    char grade;
};

struct subject_struct{         //if this method doesnt work, you can declare a details array with a constant number of elements. so ones you exceeded that number,
    string subject_code;
    int num_students;
    struct student details_array[10];
};

struct subject_struct subject_array[20];

//class subject{
//private:
//public:
//
//};

void storingData();                     //function prototypes
void splitting_strings(string);
void gradeAllocation();
void displaySubject();

void gradeAllocation(){

    for(int main_number = 0; main_number < 20; main_number++){

        for(int sub_number = 0; sub_number < sub_array_size; sub_number++){

            int mark = subject_array[main_number].details_array[sub_number].student_mark;

            if(mark == 0)           //if there's an empty slot in the array, it will get skipped by this.
                continue;

            if(70 <= mark){
                subject_array[main_number].details_array[sub_number].grade = 'A';
            }

            else if(55 <= mark && mark < 70){
                subject_array[main_number].details_array[sub_number].grade = 'B';
            }

            else if(40 <= mark && mark < 55){
                subject_array[main_number].details_array[sub_number].grade = 'C';
            }

            else if(30 <= mark && mark < 40){
                subject_array[main_number].details_array[sub_number].grade = 'D';
            }

            else if(mark < 30){
                subject_array[main_number].details_array[sub_number].grade = 'F';
            }
        }
    }
}

void splitting_strings(string str) {

    istringstream iss(str);    //this code portion split up a string into different strings using spaces
    string s;
    while (getline(iss, s, ' ')) {

        if (s[0] == 'S') {

            sub_count = 0;
            main_count++;
            subject_array[main_count].subject_code = s;
            s_code = s;
            after_s = 1;

        }
        else if(sub_count < sub_array_size){

            stringstream geek(s);
            geek >> str_int;

            if (after_s == 1) {
                loop_count = str_int;
                subject_array[main_count].num_students = str_int;
                n_students = str_int;
                after_s = 0;
            }
            else if (index_mark == 0) {
                subject_array[main_count].details_array[sub_count].student_id = str_int;
                index_mark = 1;
            }
            else if (index_mark == 1) {
                subject_array[main_count].details_array[sub_count].student_mark = str_int;
                index_mark = 0;
                if(sub_count == (sub_array_size - 1)){
                    main_count_increment = 1;
                }
                sub_count++;

            }
        }
        else{
            stringstream geek(s);
            geek >> str_int;
            if(main_count_increment == 1 && sub_count % sub_array_size == 0){
                main_count = main_count+1;
                main_count_increment = 2;
            }

            subject_array[main_count].subject_code = s_code;
            subject_array[main_count].num_students = n_students;         //  <--------this needs to be corrected.

            if (index_mark == 0) {
                subject_array[main_count].details_array[sub_count % sub_array_size].student_id = str_int;
                index_mark = 1;
            }
            else if (index_mark == 1) {
                subject_array[main_count].details_array[sub_count % sub_array_size].student_mark = str_int;
                index_mark = 0;
                sub_count++;
                if(sub_count % sub_array_size == 0){
                    main_count_increment = 1;
                }
            }
        }

    }
}

void storingData() {

    int line_count = 1;         //for debugging purposes

    FILE* fp = fopen("subjdata.txt", "r");    //reading from a text file
    if (fp == NULL)
        exit(EXIT_FAILURE);

    char* line = NULL;
    size_t len = 0;
    while ((getline(&line, &len, fp)) != -1) {

        splitting_strings(line);
        line_count++;       //for debugging purposes

    }

    fclose(fp);
    if (line)
        free(line);

}

void displaySubject(){

    int found = 0;
    string sub_code;
    cout << "Enter the subject code - ";
    cin >> sub_code;
    cout << "\nIndex Number\tMark\tGrade\n\n";

    for(int i = 0; i < 20; i++){

        if(subject_array[i].subject_code == sub_code){
            found = 1;
            for(int j = 0; j < sub_array_size; j++){
                if(subject_array[i].details_array[j].student_id == 0)
                    continue;
                cout << "  " << subject_array[i].details_array[j].student_id << "       " << subject_array[i].details_array[j].student_mark << "       " << subject_array[i].details_array[j].grade << "\n";
            }
        }
    }

    if (found == 0){
        cout << "No results found\n";
    }

}

void displayStudent(){

    int found = 0;
    int str_int;

    string stud_id;
    cout << "Enter the Student ID - ";
    //cin >> stud_id;
    stud_id = "17000004";

    stringstream geek(stud_id);
    geek >> str_int;
    cout << "\nYear - " << "20"<< stud_id[0] << stud_id[1] << "\n\n Subject      Mark    Grade\n\n";

    for(int i = 0; i < 20; i++){

            for(int j = 0; j < sub_array_size; j++){

                if(subject_array[i].details_array[j].student_id == str_int){

                    cout << " " << subject_array[i].subject_code << "       " << subject_array[i].details_array[j].student_mark << "       " << subject_array[i].details_array[j].grade << "\n";
                    found = 1;
                }
            }
    }

    cout << "\n";

    if (found == 0){
        cout << "No results found\n";
    }

}

int main() {

    storingData();
    gradeAllocation();


    //displaySubject();
    displayStudent();

    cout << "Hello, World!" << endl;

//    do{
//
//        cout << "1.Display Subject\n";
//
//        cout << "Enter your option - ";
//        cin >> option;
//
//        switch (option){
//            case 1:
//                displaySubject();
//        }
//
//    }while(option!=5);

    return 0;
}