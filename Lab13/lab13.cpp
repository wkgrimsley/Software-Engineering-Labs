#include <iostream>
#include <vector>
using namespace std;

bool fail_lecture (const vector<int>& attendance_records){
    int absent_count=0;
    for (int i=1; i<attendance_records.size(); ++i){
        absent_count += attendance_records[i]==0;
    }
    cout << "actual absent_count: ";
    cout <<  absent_count << endl;
    return absent_count >=3;
} 

bool fail_lecture_fixed(const vector<int>& attendance_records){
    int absent_count=0;
    for (int i=0; i<attendance_records.size(); ++i){
        absent_count += attendance_records[i]==0;
    }
    cout << "expected absent_count: ";
    cout <<  absent_count << endl;
    return absent_count >=3;
}    

int main() {
    vector<int> attendance_records = {0, 1, 1, 1, 0, 0, 1, 0, 1, 1};

    cout << "Attendance records: ";
    for (int v : attendance_records) cout << v << " ";
    cout << endl;

    bool actual_output = fail_lecture(attendance_records);
    bool expected_output = fail_lecture_fixed(attendance_records);

    cout << "Expected output: " << (expected_output ? "true" : "false") << endl;
    cout << "Actual output:   " << (actual_output ? "true" : "false") << endl;

    return 0;
}
