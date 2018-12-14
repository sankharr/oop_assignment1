#include <iomanip>
#include <iostream>
#include <sstream>
#include <zconf.h>
#include <math.h>
#include <fstream>
#include <cstdlib>

using namespace std;

const int MAXSUBJECTS = 10;
const int MAXSTUDENTS = 100;

int size;
int main_count = -1;
int sub_count = 0;
int after_s = 0;
int loop_count;
int index_mark = 0;
int str_int;
string s_code;
int n_students = 0;
int main_count_increment = 0;
int sub_array_size = MAXSTUDENTS;
int main_array_size = MAXSUBJECTS;
int option;
float num_A = 0, num_B = 0, num_C= 0, num_D = 0, num_F = 0;
string prev1;

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
    Student details_array[MAXSTUDENTS];
public:


    void storingData();
    void splitting_strings(string);
    void gradeAllocation();
    friend void displaySubject();
    friend void displayStudent();
    void displaySummery();
    void writeFile2(string sub_code);
    void writeFile1();
    void swap(int,int,int);
    void sort();
    void quickSort(Student arr[], int, int,int);
    int partition(Student arr[],int,int,int);


};

/*
 * creating the main array which is used to store all the informations related to the subjects.
 * An element of this array contains a subject code of a particular subject, The number of students who have faced for the exam of that subject
 * & a Student type array which contains all the informations related to each student who faced the exam of that subject.
*/
Subject subject_array[MAXSUBJECTS];

//This function pauses the programme untill the user presses the enter key.
void systemPause(){
    cout << "\nPress enter key to continue........" << endl;
    getchar();
    getchar();
}

/*This function is called in the main function to sort out each details_array which contains the informations related to students.
 */
void Subject::sort(){

    int low,high,n;

    for(int k=0; k< MAXSUBJECTS; k++){

        if(subject_array[k].details_array[0].student_id == 0){      //if the student id at the 0th index of a particular array is 0, then it means that there's no array there

            return;
        }

        low = 0;
        high = subject_array[k].num_students - 1;

        quickSort(subject_array[k].details_array,low,high,k);

    }

}

//This is a recursive function which finds the partitioning key.
void Subject::quickSort(Student arr[], int low, int high, int main_number){

    if (low < high){

        int pi = partition(arr, low, high, main_number);
        quickSort(arr, low, pi - 1,main_number);
        quickSort(arr, pi + 1, high,main_number);
    }
}

/*This will consider the last element of the array as the pivot element and move it to the correct position of the array according to the index number
 * Then it will move all the elements which has lesser index numbers to the left side of pivot element, and the ones which have a higher index number will be
 * moved to right side of the array. This is done by swapping up two elements at a time */
int Subject::partition(Student arr[], int low, int high, int main_number){

    int pivot = arr[high].student_id;
    int i = (low - 1);

    for (int j = low; j <= high- 1; j++){

        if (arr[j].student_id <= pivot)
        {
            i++;
            swap(main_number,i,j);
        }
    }
    swap(main_number,i+1,high);
    return (i + 1);
}

/* This is the function which is used to swap two elements in the array */
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

//This is the function which allocates the particular grade to each mark that a student has got.
void Subject::gradeAllocation(){

    for(int main_number = 0; main_number < MAXSUBJECTS; main_number++){

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

/*Each line which is read by the storingData function will be passed to here to separate them into strings.
 * and then each string will be stored in the relevant position in the array */
void Subject::splitting_strings(string str) {

    istringstream iss(str);
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
    }
}

/*This function will read line by line from the text file which contains all the data.
 * each line will be passed to splitting_strings function as a parameter */
void Subject::storingData() {

    int line_count = 1;

    FILE* fp = fopen("subjdata.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    char* line = NULL;
    size_t len = 0;
    while ((getline(&line, &len, fp)) != -1) {

        splitting_strings(line);
        line_count++;

    }

    fclose(fp);
    if (line)
        free(line);

}

/*When the user enters a subject code of a particular subject,
 * This function will show the marks and the grades each student has got for that subject */
void displaySubject(){

    int found = -1;
    string sub_code;
    cout << "Enter the subject code - ";
    cin >> sub_code;
    cout << "\nIndex Number\tMark\tGrade\n\n";

    for(int i = 0; i < MAXSUBJECTS; i++){

        if(subject_array[i].subject_code == sub_code){
            found = 1;
            for(int j = 0; j < sub_array_size; j++){
                if(subject_array[i].details_array[j].student_id == 0)
                    continue;
                cout << "  " << subject_array[i].details_array[j].student_id << "       " << subject_array[i].details_array[j].student_mark << "       " << subject_array[i].details_array[j].grade << "\n";
            }
        }
    }

    if (found == -1){
        cout << "No results found\n\n";
    }
}

/*When the user enters a student id of a particular student,
 * This function will show all the marks and the grades that this student has got for each subject*/
void displayStudent(){

    int found = -1;
    int str_int;

    string stud_id;
    cout << "Enter the Student ID - ";
    cin >> stud_id;


    stringstream geek(stud_id);
    geek >> str_int;
    cout << "\nYear - " << "20"<< stud_id[0] << stud_id[1] << "\n\n Subject      Mark    Grade\n\n";

    for(int i = 0; i < MAXSUBJECTS; i++){

        for(int j = 0; j < sub_array_size; j++){

            if(subject_array[i].details_array[j].student_id == str_int){

                cout << " " << subject_array[i].subject_code << "       " << subject_array[i].details_array[j].student_mark << "       " << subject_array[i].details_array[j].grade << "\n";
                found = 1;
            }
        }
    }

    cout << "\n" << flush;

    if (found == -1){
        cout << "No results found\n\n";
    }

}

/*When the user enters a subject code of a particular subject,
 * This function will show the average, standard deviation and the number of grades grouped by each grade*/
void Subject::displaySummery(){

    int found_id = -1;
    int numA = 0, numB = 0, numC= 0, numD = 0, numF = 0;
    double total = 0, avg = 0, standard_deviation = 0, stdDevi_part = 0;
    double stud_mark;
    string sub_code;
    cout << "Enter the subject code - ";
    cin >> sub_code;


    for(int i = 0; i < MAXSUBJECTS; i++){            //This loop is used to calculate the total and the number of particular grades

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
    avg = total / subject_array[found_id].num_students;

    for(int i = 0; i < MAXSUBJECTS; i++){            //This loop is used to calculate the standard deviation

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

/*This function will calculate the percentage of each grade for each subject, and then it will store them in
 * a text file together with that relevant subject code and the number of students who did that subject */
void Subject::writeFile2(string sub_code){

    prev1 = sub_code;
    int found_id = -1;
    num_A = 0, num_B = 0, num_C= 0, num_D = 0, num_F = 0;

    for(int i = 0; i < MAXSUBJECTS; i++){            //This loop is used to calculate the number of particular grades

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

    if (found_id == -1){
        cout << "No results found\n";
    }
}

/*This function will loop throught the main array(subject_array) and pass one subject code at a time, to
 *the writeFile2 function to do the necessary operations.*/
void Subject::writeFile1(){

    string temp;

    for(int k = 0; k < MAXSUBJECTS; k++){
        temp = subject_array[k].subject_code;
        if(temp == prev1)
            continue;
        if(subject_array[k].num_students == 0)
            continue;
        writeFile2(temp);

    }
}

int main() {

    subject_array->storingData();
    subject_array->gradeAllocation();
    subject_array->sort();

    do{
        cout << "\nPlease note that this programme will only work in a linux operating system. I never knew that there are functions which don't work properly in Windows till the last moment.\nI didn't have much time to do changes again to make it work for Windows. Sorry for the inconvenience caused.\n\n";

        cout << "1.Display Subject\n2.Display Student\n3.Display Subject Summary\n4.Save Summaries\n5.Exit\n\nEnter your option - ";

        cin >> option;

        switch (option){

            case 1:
                displaySubject();
                systemPause();
                break;

            case 2:
                displayStudent();
                systemPause();
                break;

            case 3:
                subject_array -> displaySummery();
                systemPause();
                break;

            case 4:
                subject_array -> writeFile1();
                systemPause();
                break;

            default:
                if(option == 5)
                    cout << "GoodBye!\n";
                else{
                    cout << "Invalid Input\n\n";
                    break;
                }        }

    }while(option!=5);

    return 0;
}