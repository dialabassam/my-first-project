#include <iostream>
#include <string>
#include <cmath> 
using namespace std;

struct Student {
    string name;
    int id;
    int marks[3];
};

void inputStudent(Student &s, int number);
void displayStudent(const Student &s, int number);
int calculateTotal(const Student &s);
double calculateAverage(const Student &s);
int findMin(const Student *s);
int findMax(const Student &s);
double findMedian(const Student &s);
double findStandardDeviation(const Student &s);
void showChoice(Student* all, int n, int index, Student &s, int total, double average, char grade, int minimum, int maximum);
void analyzeQuizzes(Student* s, int n);
int bestStudent(Student* s, int n);
int bestQuiz(Student* s, int n);
void sortStudentMarks(Student &s);
void displaySortMarks(Student &s);
char calculateGrade(double avg);
bool isPass(double avg);
void printStudentList(Student* s, int n); 
int studentRank(Student* s, int n, int index);
double improvementPercent(const Student &s);  
int scoreDifference(const Student &s);

int main() {

    int NUM_STUDENTS;
    cout<<"     **  STUDENT PERFORMANCE SYSTEM  **   \n";
    cout << "\n===========================================\n";
    cout << "     WELCOME TO STUDENT MARKS PROGRAM\n";
    cout << "===========================================\n";
    cout << "Enter number of students: ";
    cin >> NUM_STUDENTS;

    Student* students = new Student[NUM_STUDENTS];

    for (int i = 0; i < NUM_STUDENTS; i++) {
        inputStudent(students[i], i + 1);
    }

    printStudentList(students, NUM_STUDENTS);

    int choice;
    do {
        cout << "\n\n=========== MAIN MENU ===========\n";
        for (int i = 0; i < NUM_STUDENTS; i++)
            cout << i + 1 << " - Show Student " << i + 1 << "\n";

        cout << NUM_STUDENTS + 1 << " - Exit Program\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice >= 1 && choice <= NUM_STUDENTS) {

            int index = choice - 1;
            displayStudent(students[index], choice);

            int total = calculateTotal(students[index]);
            double average = calculateAverage(students[index]);
            char grade = calculateGrade(average);
            int minimum = findMin(&students[index]);
            int maximum = findMax(students[index]);

            showChoice(students, NUM_STUDENTS, index, students[index], total, average, grade, minimum, maximum);
        }
        else if (choice == NUM_STUDENTS + 1) {
            cout << "\nExiting program...\n\n";
            analyzeQuizzes(students, NUM_STUDENTS);
        }
        else {
            cout << "\nInvalid option! Try again.\n";
        }

    } while (choice != NUM_STUDENTS + 1);

    delete[] students;
    return 0;
}

void inputStudent(Student &s, int number) {
    cout << "\n=== Student " << number << " ===" << endl;

    cin.ignore();
    cout << "Enter student name: ";
    getline(cin, s.name);

    cout << "Enter student ID: ";
    cin >> s.id;

    cout << "Enter marks for three degrees:\n";
    for (int i = 0; i < 3; i++) {
        cout << "-  degree (out of 30) " << i + 1 << ": ";
        cin >> s.marks[i];
    }
}

void displayStudent(const Student &s, int number) {
    cout << "\nStudent " << number << ":" << endl;
    cout << "Name: " << s.name << endl;
    cout << "Student ID: " << s.id << endl;
    cout << "Marks:\n";
    for (int i = 0; i < 3; i++) {
        cout << "  degree " << i + 1 << ": " << s.marks[i] << endl;
    }
}

int calculateTotal(const Student &s) {
    return s.marks[0] + s.marks[1] + s.marks[2];
}

double calculateAverage(const Student &s) {
    return calculateTotal(s) / 3.0;
}

int findMin(const Student *s) {
    int mn = s->marks[0];
    for (int i = 1; i < 3; i++)
        if (s->marks[i] < mn) mn = s->marks[i];
    return mn;
}

int findMax(const Student &s) {
    int mx = s.marks[0];
    for (int i = 1; i < 3; i++)
        if (s.marks[i] > mx) mx = s.marks[i];
    return mx;
}

double findMedian(const Student &s) {
    int temp[3] = {s.marks[0], s.marks[1], s.marks[2]};
    for(int i = 0; i < 2; i++)
        for(int j = i+1; j < 3; j++)
            if(temp[j] < temp[i])
                swap(temp[i], temp[j]);
    return temp[1];
}

double findStandardDeviation(const Student &s) {
    double avg = calculateAverage(s);
    double sum = 0;
    for (int i = 0; i < 3; i++)
        sum += pow(s.marks[i] - avg, 2);

    return sqrt(sum / 3.0);
}

double improvementPercent(const Student &s) {
    if (s.marks[0] == 0) return 0;
    return ((s.marks[2] - s.marks[0]) / (double)s.marks[0]) * 100.0;
}

int scoreDifference(const Student &s) {
    int mn = min(s.marks[0], min(s.marks[1], s.marks[2]));
    int mx = max(s.marks[0], max(s.marks[1], s.marks[2]));
    return mx - mn;
}

int studentRank(Student* s, int n, int index) {
    int score = calculateTotal(s[index]);
    int rank = 1;

    for (int i = 0; i < n; i++)
        if (calculateTotal(s[i]) > score)
            rank++;

    return rank;
}


void showChoice(Student* all, int n, int index, Student &s, int total, double average, char grade, int minimum, int maximum) {

    char choice;
    char again;

    do {
        cout << "\nChoose the operation you want:\n";
        cout <<"-----------------------------------\n";
        cout << "A  -  Average\n";
        cout << "T  -  Total\n";
        cout << "M  -  Minimum\n";
        cout << "X  -  Maximum\n";
        cout << "D  -  Median\n";
        cout << "N  -  Standard Deviation\n";
        cout << "S  -  Sort Marks\n";
        cout << "G  -  Grade\n";
        cout << "P  -  Pass/Fail\n";
        cout << "K  -  Rank\n";
        cout << "I  -  Improvement Percentage\n";
        cout << "F  -  Score Difference\n";
        cout << "L  -  List All\n";
        cout << "E  -  Exit to Main Menu\n";
        cout <<"-----------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;
        choice = toupper(choice);

        if (choice == 'T') cout << "Total = " << total << endl;
        else if (choice == 'A') cout << "Average = " << average << endl;
        else if (choice == 'M') cout << "Minimum = " << minimum << endl;
        else if (choice == 'X') cout << "Maximum = " << maximum << endl;
        else if (choice == 'D') cout << "Median = " << findMedian(s) << endl;
        else if (choice == 'N') cout << "Standard Deviation = " << findStandardDeviation(s) << endl;
        else if (choice == 'S') displaySortMarks(s);
        else if (choice == 'G') {
    cout << "Grade = " << grade << endl;
    cout << "\n--- Grade Details ---\n";
    if (grade == 'A') cout << "A = Excellent performance.\n";
    else if (grade == 'B') cout << "B = Very Good performance.\n";
    else if (grade == 'C') cout << "C = Good performance.\n";
    else if (grade == 'D') cout << "D = Pass (Needs improvement).\n";
    else if (grade == 'F') cout << "F = Fail (Below required level).\n";
}
        else if (choice == 'P') {
    bool pass = isPass(average);
    cout << (pass ? "PASS\n" : "FAIL\n");

    cout << "\n--- Pass/Fail Details ---\n";
    if (pass) {
        cout << "PASS = Student average is 60 or above.\n";
        cout << "Good job! You passed the course.\n";
    } else {
        cout << "FAIL = Student average is below 60.\n";
        cout << "Needs more practice and improvement.\n";
    }
}

        else if (choice == 'K') cout << "Rank = " << studentRank(all, n, index) << endl;
        else if (choice == 'I') cout << "Improvement Percentage = " << improvementPercent(s) << "%\n";
        else if (choice == 'F') cout << "Score Difference = " << scoreDifference(s) << endl;
        else if (choice == 'L') {
            cout << "\nTotal = " << total << endl;
            cout << "Average = " << average << endl;
            cout << "Median = " << findMedian(s) << endl;
            cout << "Grade = " << grade << endl;
            cout << "\n--- Grade Details ---\n";
            if (grade == 'A') cout << "A = Excellent performance.\n";
            else if (grade == 'B') cout << "B = Very Good performance.\n";
            else if (grade == 'C') cout << "C = Good performance.\n";
            else if (grade == 'D') cout << "D = Pass (Needs improvement).\n";
            else if (grade == 'F') cout << "F = Fail (Below required level).\n";
            cout << "Standard Deviation = " << findStandardDeviation(s) << endl;
            cout << "Minimum = " << minimum << endl;
            cout << "Maximum = " << maximum << endl;
            cout << "Improvement % = " << improvementPercent(s) << endl;
            cout << "Score Difference = " << scoreDifference(s) << endl;
            cout << "Rank = " << studentRank(all, n, index) << endl;
            cout << "Status: " << (isPass(average) ? "PASS" : "FAIL") << endl;
        }
        else if (choice == 'E') return;
        else cout << "Invalid choice!\n";

        cout << "\nDo you want another operation? (Y/N): ";
        cin >> again;
        again = toupper(again);

    } while (again == 'Y');
}



void displaySortMarks(Student &s) {
    sortStudentMarks(s);
    cout << "Sorted Marks (ascending): ";
    for (int i = 0; i < 3; i++)
        cout << s.marks[i] << " ";
    cout << endl;
}

void sortStudentMarks(Student &s) {
    for (int i = 0; i < 2; i++)
        for (int j = i + 1; j < 3; j++)
            if (s.marks[j] < s.marks[i])
                swap(s.marks[i], s.marks[j]);
}

void analyzeQuizzes(Student* s, int n) {

    cout << "=====================================\n";
    cout << "       FINAL PERFORMANCE REPORT\n";
    cout << "=====================================\n";

    double quizAvg[3] = {0};

    for (int i = 0; i < n; i++) {
        quizAvg[0] += s[i].marks[0];
        quizAvg[1] += s[i].marks[1];
        quizAvg[2] += s[i].marks[2];
    }

    cout << "\nAverage of Quiz 1: " << quizAvg[0] / n << endl;
    cout << "Average of Quiz 2: " << quizAvg[1] / n << endl;
    cout << "Average of Quiz 3: " << quizAvg[2] / n << endl;

    int best = bestStudent(s, n);
    cout << "\nTop Student: " << s[best].name
         << "   (Total Marks = " << calculateTotal(s[best]) << ")\n";

    int bestQ = bestQuiz(s, n);
    cout << "Quiz with Highest Class Performance: Quiz " << bestQ + 1 << endl;

    cout << "=====================================\n";
}

int bestStudent(Student* s, int n) {
    int bestIndex = 0;
    int bestScore = calculateTotal(s[0]);

    for (int i = 1; i < n; i++) {
        int total = calculateTotal(s[i]);
        if (total > bestScore) {
            bestScore = total;
            bestIndex = i;
        }
    }
    return bestIndex;
}

int bestQuiz(Student* s, int n) {
    double quizAvg[3] = {0};

    for (int i = 0; i < n; i++) {
        quizAvg[0] += s[i].marks[0];
        quizAvg[1] += s[i].marks[1];
        quizAvg[2] += s[i].marks[2];
    }

    int best = 0;
    if (quizAvg[1] > quizAvg[best]) best = 1;
    if (quizAvg[2] > quizAvg[best]) best = 2;

    return best;
}

char calculateGrade(double avg) {
    if (avg >= 90) return 'A';
    else if (avg >= 80) return 'B';
    else if (avg >= 70) return 'C';
    else if (avg >= 60) return 'D';
    else return 'F';
}

bool isPass(double avg) {
    return avg >= 60;
}

void printStudentList(Student* s, int n) {
    cout << "\n=====================================\n";
    cout << "         REGISTERED STUDENTS LIST    \n";
    cout << "=====================================\n";
    cout << "No. | Student Name       | Student ID\n";
    cout << "--------------------------------------------\n";
    for (int i = 0; i < n; i++) {
        cout << i + 1 << ".  | " 
             << s[i].name 
             << " | " << s[i].id << endl;
    }
    cout << "--------------------------------------------\n";
}
