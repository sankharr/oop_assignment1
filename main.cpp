#include <iomanip>
#include <iostream>

using namespace std;

int size; //this is declared here to be used for the details_array in "subject" struct;

struct student{
    int student_id;
    int student_mark;
};

struct subject_struct{         //if this method doesnt work, you can declare a details array with a constant number of elements. so ones you exceeded that number,
    int subject_code;
    struct student *details_array;
};

class subject{
private:
public:
    void readTextFile();
    void displaySubject();
};

void subject::readTextFile() {}

void subject::displaySubject() {
    cin >>
}
int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}