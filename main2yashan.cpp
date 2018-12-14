#include<iostream>
#include<string>
#include<fstream>
#include <cmath>
#include <sstream>

using namespace std;

int MAXSTUDENTS = 100;

class Student{
private:
	string left[100];
	int mid[100];
	char grades[100];
public:
	void storeData();
	void gradeAllocate();
	void displaySubject();
	void displaySummary();
	void saveSummary();
	void displayStudent();
	void swap(int num1, int num2);
	void sort();
	int partition(int low, int high);
	void quickSort(int low,int high);
};

Student main_arrays;

void Student::swap(int num1, int num2) {

	string sid = main_arrays.left[num1];
	int marks = main_arrays.mid[num1];
	char grd = main_arrays.grades[num1];

	main_arrays.left[num1] = main_arrays.left[num2];
	main_arrays.mid[num1] = main_arrays.mid[num2];
	main_arrays.grades[num1] = main_arrays.grades[num2];

	main_arrays.left[num2] = sid;
	main_arrays.mid[num2] = marks;
	main_arrays.grades[num2] = grd;
}

int Student::partition(int low, int high){

	int str_int1;
	stringstream geek(main_arrays.left[high]);		//string to int conversion
	geek >> str_int1;

	int pivot = str_int1;    // pivot
	int i = (low - 1);  // Index of smaller element

	for (int j = low; j <= high- 1; j++)
	{
		int str_int2;
		stringstream geek(main_arrays.left[j]);		//string to int conversion
		geek >> str_int2;
		// If current element is smaller than or
		// equal to pivot
		if (str_int2 <= pivot)
		{
			i++;    // increment index of smaller element
			swap(i,j);
		}
	}
	swap(i+1,high);
	return (i + 1);
}

void Student::quickSort(int low,int high){

	if (low < high)
	{
		/* pi is partitioning index, arr[p] is now
           at right place */
		int pi = partition(low, high);

		// Separately sort elements before
		// partition and after partition
		quickSort(low, pi - 1);
		quickSort(pi + 1, high);
	}

}

void Student::sort(){

	int low,high,n;
	int loop_count;

	for(int index = 0; index < 100; index++){

		char temp = main_arrays.left[index][0];

		if(temp=='S'){

			loop_count = main_arrays.mid[index];
            for(int j = index + 1; j < index + loop_count + 1; j++){

                //int mark = main_arrays.mid[j];
                quickSort(j,index + loop_count);


            }

            index = index + loop_count;

		}

	}
}


void Student::storeData(){

	string s;
	int n;

	ifstream inFile;
	inFile.open("subjdata2.txt");

	if(inFile.fail()){
		cerr <<"Erro while opening file\n";
		exit;
	}
	while(!inFile.eof()){

		for(int i=0;i<MAXSTUDENTS;i++){
			inFile >> main_arrays.left[i] >> main_arrays.mid[i];
		}

	}
}

void Student::gradeAllocate(){

	int loop_count;

	for(int index = 0; index < 100; index++){

		char temp = main_arrays.left[index][0];

		if(temp=='S'){

			loop_count = main_arrays.mid[index];

		}

		for(int j = index + 1; j < index + loop_count + 1; j++){

			int mark = main_arrays.mid[j];

			if(mark == 0)
				continue;

			if(70 <= mark){
				main_arrays.grades[j] = 'A';
			}

			else if(55 <= mark && mark < 70){
				main_arrays.grades[j] = 'B';
			}

			else if(40 <= mark && mark < 55){
				main_arrays.grades[j] = 'C';
			}

			else if(30 <= mark && mark < 40){
				main_arrays.grades[j] = 'D';
			}

			else if(mark < 30){
				main_arrays.grades[j] = 'F';
			}

		}

		index = index + loop_count;

	}

}

void Student::displaySubject(){

	int i;
	string s_code;
	int found = -1;

	//s_code = "SCS1203";

	cout << "Enter the subject code - ";
	cin >> s_code;

	for(i = 0; i < MAXSTUDENTS; i++){		//finding the subject code from the 'left' sub array of 'Main_arrays'

		if(main_arrays.left[i]==s_code){
			found = i;
			break;
		}
	}

	int num_students = main_arrays.mid[i];

	cout << "Student ID   Marks    Grade\n";

	for(int j = i+1; j < i + num_students + 1; j++){

		cout << " " << main_arrays.left[j] << "     " << main_arrays.mid[j] << " 		" << main_arrays.grades[j] << "\n";

	}

	if(found == -1){
		cout << "No results found!\n";
	}

}

void Student::displayStudent(){

	string s_id;
	string s_code;

	s_id = "17000020";

//	cout << "Enter the Student ID - ";
//	cin >> s_id;

	int loop_count;

	cout << "Subject Code	Marks	Grade\n";

	for(int index = 0; index < 100; index++){

		char f_char = main_arrays.left[index][0];

		if(f_char=='S'){

			s_code = main_arrays.left[index];
			loop_count = main_arrays.mid[index];

		}

		for(int j = index + 1; j < index + loop_count + 1; j++){

			if(s_id == main_arrays.left[j]){
				cout << "   " << s_code << " 		  " << main_arrays.mid[j] << " 	  " << main_arrays.grades[j] << "\n";
				break;
			}


		}

		index = index + loop_count;

	}

}

void Student::displaySummary(){

	string s_id;
	string s_code;
	int found = -1;

	double total = 0, avg = 0, standard_deviation = 0,stud_mark = 0,stdDevi_part = 0;
	int numA = 0,numB = 0,numC = 0,numD = 0, numF = 0;

	s_code = "SCS1203";

//	cout << "Enter the Subject Code - ";
//	cin >> s_code;

	int loop_count;

	for(int index = 0; index < 100; index++){

		if(main_arrays.left[index] == s_code){

			loop_count = main_arrays.mid[index];
			found = index;

            for(int j = index + 1; j < index + loop_count + 1; j++){ //this loop is used here to calculate the average and the total

                total += main_arrays.mid[j];

                if(main_arrays.grades[j] == 'A')
                    numA++;
                else if(main_arrays.grades[j] == 'B')
                    numB++;
                else if(main_arrays.grades[j] == 'C')
                    numC++;
                else if(main_arrays.grades[j] == 'D')
                    numD++;
                else if(main_arrays.grades[j] == 'F')
                    numF++;

            }

            avg = total / loop_count;

            for(int j = index + 1; j < index + loop_count + 1; j++){

                stud_mark = (double)main_arrays.mid[j];
                stdDevi_part += pow(stud_mark - avg, 2);

            }

            standard_deviation = sqrt(stdDevi_part/(double)loop_count);

            cout << "\nAverage - " << avg << "\nStandard Deviation - " << standard_deviation <<"\nNumber of 'A's - "<< numA;
            cout << "\nNumber of 'B's - "<< numB << "\nNumber of 'C's - "<< numC << "\nNumber of 'D's - "<< numD << "\nNumber of 'F's - "<< numF << "\n";

            if(found != -1)
                break;

		}

		index = index + loop_count;
	}
}

void Student::saveSummary() {

    string s_id;

    int found = -1;

    double total = 0, avg = 0, standard_deviation = 0, stud_mark = 0, stdDevi_part = 0;
    double numA = 0, numB = 0, numC = 0, numD = 0, numF = 0;

    //s_code = "SCS1203";

//	cout << "Enter the Subject Code - ";
//	cin >> s_code;

    int loop_count;

    for (int index = 0; index < 100; index++) {

        string s_code;
        double numA = 0, numB = 0, numC = 0, numD = 0, numF = 0;

        if (main_arrays.left[index][0] == 'S') {

            s_code = main_arrays.left[index];
            loop_count = main_arrays.mid[index];
            found = index;

            for (int j = index + 1; j < index + loop_count + 1; j++) { //this loop is used here to calculate the average and the total

                total += main_arrays.mid[j];

                if (main_arrays.grades[j] == 'A')
                    numA++;
                else if (main_arrays.grades[j] == 'B')
                    numB++;
                else if (main_arrays.grades[j] == 'C')
                    numC++;
                else if (main_arrays.grades[j] == 'D')
                    numD++;
                else if (main_arrays.grades[j] == 'F')
                    numF++;

            }

            numA = (numA / loop_count) * 100;       //calculating the grade percentages
            numB = (numB / loop_count) * 100;
            numC = (numC / loop_count) * 100;
            numD = (numD / loop_count) * 100;
            numF = (numF / loop_count) * 100;

            ofstream myfile;
            myfile.open("summdata.txt", ios_base::app);
            myfile << s_code << " " << loop_count << " A " << numA;
            myfile << "% B " << numB << "% C " << numC << "% D " << numD << "% F " << numF << "% \n";
            myfile.close();


        }

        if (found == -1) {
            cout << "No results found\n";
        }

        index = index + loop_count;

    }
}


int main(){

	main_arrays.storeData();
	main_arrays.gradeAllocate();
	main_arrays.sort();

	main_arrays.displaySubject();
	main_arrays.displayStudent();
	main_arrays.displaySummary();
	main_arrays.saveSummary();
	cout << "Hello bitches!\n";

	return 0;
}






