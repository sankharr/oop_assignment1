#include <iomanip>
#include <iostream>
#include <sstream>
#include <zconf.h>
#include <math.h>
#include <fstream>

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
float num_A = 0, num_B = 0, num_C= 0, num_D = 0, num_F = 0;       //for writeFile function
string prev1; //for writeToFile2 function

//struct student{
//    int student_id;
//    int student_mark;
//    char grade;
//};
//
//struct subject_struct{         //if this method doesnt work, you can declare a details array with a constant number of elements. so ones you exceeded that number,
//    string subject_code;
//    int num_students;
//    struct student details_array[10];
//};

class Student{              //class declarations

private:

public:
    int student_id;
    int student_mark;
    char grade;

};

class Subject{

private:

    string subject_code;
    int num_students;
    Student details_array[10];
public:


    void storingData();
    void splitting_strings(string);
    void gradeAllocation();
    void displaySubject();
    void displayStudent();
    void displaySummery();
    void writeFile2(string sub_code);
    void writeFile1();
    void swap(int,int,int);
    void sort();
    void quickSort(Student arr[], int, int,int);     //changed the 1st passing parameter from Subject arr[] to Student arr[]. this could be a error. if this doesnt work, try Student *arr
    int partition(Student arr[],int,int,int);
};

//struct subject_struct subject_array[20];
Subject subject_array[20];       //function prototypes

void Subject::sort(){

    int low,high,n;

    for(int k=0; k< 20; k++){

        if(subject_array[k].details_array[0].student_id == 0){      //if student_id doesnt work here, change it to student mark and see

            return;                                                 //if the student id at the 0th index of a particular array is 0, then it means that there's no array there
        }

        for(n = 0; n < sub_array_size; n++){

            if(subject_array[k].details_array[n].student_id == 0){      //if student_id doesnt work here, change it to student mark and see

                break;
                //if the student id at the 0th index of a particular array is 0, then it means that there's no array there
            }
        }

        low = 0;
        high = n - 1;

        quickSort(subject_array[k].details_array,low,high,k);

    }

}

void Subject::quickSort(Student arr[], int low, int high, int main_number){

    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
           at right place */
        int pi = partition(arr, low, high, main_number);

        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1,main_number);
        quickSort(arr, pi + 1, high,main_number);
    }
}

int Subject::partition(Student arr[], int low, int high, int main_number)
{
    int pivot = arr[high].student_id;    // pivot
    int i = (low - 1);  // Index of smaller element

    for (int j = low; j <= high- 1; j++)
    {
        // If current element is smaller than or
        // equal to pivot
        if (arr[j].student_id <= pivot)
        {
            i++;    // increment index of smaller element
            swap(main_number,i,j);
        }
    }
    swap(main_number,i+1,high);
    return (i + 1);
}

void Subject::swap(int main_number,int sub_number1,int sub_number2){

    int s_id = subject_array[main_number].details_array[sub_number1].student_id;
    int s_mark = subject_array[main_number].details_array[sub_number1].student_mark;
    char grd = subject_array[main_number].details_array[sub_number1].grade;

    subject_array[main_number].details_array[sub_number1].student_id = subject_array[main_number].details_array[sub_number2].student_id;
    subject_array[main_number].details_array[sub_number1].student_mark = subject_array[main_number].details_array[sub_number2].student_mark;
    subject_array[main_number].details_array[sub_number1].grade = subject_array[main_number].details_array[sub_number2].grade;

    subject_array[main_number].details_array[sub_number2].student_id = s_id;
    subject_array[main_number].details_array[sub_number2].student_mark = s_mark;
    subject_array[main_number].details_array[sub_number2].grade = grd;
}



// A utility function to swap two elements




void Subject::gradeAllocation(){

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

void Subject::splitting_strings(string str) {

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
                                                                        //if you correct the above error, then it might affect the calculation of avg in displaySummery function
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

void Subject::storingData() {

    int line_count = 1;         //for debugging purposes

    FILE* fp = fopen("subjdata2.txt", "r");    //reading from a text file
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

void Subject::displaySubject(){

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

void Subject::displayStudent(){

    int found = 0;
    int str_int;

    string stud_id;
    cout << "Enter the Student ID - ";
    stud_id = "17000004";
    cin >> stud_id;


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

void Subject::displaySummery(){

    int found_id = -1;
    int numA = 0, numB = 0, numC= 0, numD = 0, numF = 0;
    double total = 0, avg = 0, standard_deviation = 0, stdDevi_part = 0;
    double stud_mark;
    string sub_code;
    cout << "Enter the subject code - ";
    cin >> sub_code;


    for(int i = 0; i < 20; i++){            //This loop is used to calculate the total and the number of particular grades

        if(subject_array[i].subject_code == sub_code){

            found_id = i;
            for(int j = 0; j < sub_array_size; j++){

                if(subject_array[i].details_array[j].student_id == 0)
                    continue;

                total = total + subject_array[i].details_array[j].student_mark;

                if(subject_array[i].details_array[j].grade == 'A')
                    numA++;
                else if(subject_array[i].details_array[j].grade == 'B')
                    numB++;
                else if(subject_array[i].details_array[j].grade == 'C')
                    numC++;
                else if(subject_array[i].details_array[j].grade == 'D')
                    numD++;
                else if(subject_array[i].details_array[j].grade == 'F')
                    numF++;

            }
        }
    }
    avg = total / subject_array[found_id].num_students;     //<---------------------------------------------This calculation will be incorrect if you correct the error which happens when assigning the num_students value in splitting_strings function

    for(int i = 0; i < 20; i++){            //This loop is used to calculate the standard deviation

        if(subject_array[i].subject_code == sub_code){

            found_id = i;

            for(int j = 0; j < sub_array_size; j++){

                if(subject_array[i].details_array[j].student_id == 0)
                    continue;

                stud_mark = (double)subject_array[i].details_array[j].student_mark;
                stdDevi_part += pow(stud_mark - avg, 2);

            }
        }
    }

    standard_deviation = sqrt(stdDevi_part/(double)subject_array[found_id].num_students);

    cout << "\nAverage - " << avg << "\nStandard Deviation - " << standard_deviation <<"\nNumber of 'A's - "<< numA;
    cout << "\nNumber of 'B's - "<< numB << "\nNumber of 'C's - "<< numC << "\nNumber of 'D's - "<< numD << "\nNumber of 'F's - "<< numF << "\n";

    if (found_id == -1){
        cout << "No results found\n";
    }
}

void Subject::writeFile2(string sub_code){

    prev1 = sub_code;
    int found_id = -1;
    num_A = 0, num_B = 0, num_C= 0, num_D = 0, num_F = 0;

    for(int i = 0; i < 20; i++){            //This loop is used to calculate the number of particular grades

        if(subject_array[i].subject_code == sub_code){

            found_id = i;
            for(int j = 0; j < sub_array_size; j++){

                if(subject_array[i].details_array[j].student_id == 0)
                    continue;

                if(subject_array[i].details_array[j].grade == 'A')
                    num_A++;
                else if(subject_array[i].details_array[j].grade == 'B')
                    num_B++;
                else if(subject_array[i].details_array[j].grade == 'C')
                    num_C++;
                else if(subject_array[i].details_array[j].grade == 'D')
                    num_D++;
                else if(subject_array[i].details_array[j].grade == 'F')
                    num_F++;

            }
        }
    }
    num_A = (num_A / subject_array[found_id].num_students)*100;       //calculating the grade percentages
    num_B = (num_B / subject_array[found_id].num_students)*100;
    num_C = (num_C / subject_array[found_id].num_students)*100;
    num_D = (num_D / subject_array[found_id].num_students)*100;
    num_F = (num_F / subject_array[found_id].num_students)*100;

    ofstream myfile;
    myfile.open ("summdata.txt",ios_base::app);
    myfile << subject_array[found_id].subject_code << " " << subject_array[found_id].num_students << " A " << num_A;
    myfile << "% B " << num_B << "% C " << num_C << "% D " << num_D << "% F " << num_F <<"% \n";
    myfile.close();

//    cout << subject_array[found_id].subject_code;                                                                           //for testing purposes
//    printf(" %d A %.2f% B %.2f% C %.2f% D %.2f%",subject_array[found_id].num_students,num_A,num_B,num_C,num_D);
//    printf(" F %.2f%\n",num_F);

    if (found_id == -1){
        cout << "No results found\n";
    }
}

void Subject::writeFile1(){

    string temp;


    for(int k = 0; k < 20; k++){
        temp = subject_array[k].subject_code;
        if(temp == prev1)
            continue;
        if(subject_array[k].num_students == 0)
            continue;
        writeFile2(temp);

    }

}

int main() {

//    storingData();
//    gradeAllocation();
    subject_array->storingData();
    subject_array->gradeAllocation();
    subject_array -> displaySubject();
    subject_array->sort();
    subject_array -> displaySubject();

//    subject_array->displaySubject();
//    subject_array->displayStudent();
//    subject_array->displaySummery();
//    subject_array->writeFile1();

//    displaySubject();
//    //displayStudent();
//
//    string sub_code;
//    cout << "Enter the subject code - ";
//    cin >> sub_code;
//    displaySummery(sub_code);

//    writeFile1();

    //cout << "Hello, World!" << endl;

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