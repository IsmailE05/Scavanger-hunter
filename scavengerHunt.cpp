#include <iostream>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <thread> // Include for sleep_for
#include <random>
using namespace std;
using namespace std::chrono;

vector<int> getDigits(int num, int base) {
    vector<int> digits;
    if (num == 0) return { 0 }; // Ensure 0 is handled properly
    while (num > 0) {
        digits.push_back(num % base);
        num /= base;
    }
    reverse(digits.begin(), digits.end());
    return digits;
}
// Naive method: Recursively multiply digits until a single digit remains
unordered_map<int, int> naiveMemo;
int multiplicativePersistenceNaive(int num, int base, int& steps) {
    // If the result is already memoized, use it
    if (naiveMemo.count(num)) {
        steps += naiveMemo[num]; // Use stored step count
        return num;              // Return the final reduced digit
    }

    vector<int> digits = getDigits(num, base);
    if (digits.size() == 1) return num; // Already a single digit

    int product = 1;
    for (int d : digits) product *= d;

    steps++;

    // Recursive call with memoization
    int result = multiplicativePersistenceNaive(product, base, steps);
    naiveMemo[num] = steps; // Store the correct step count

    return result;
}// Optimized method with memoization
unordered_map<int, int> memo;
int multiplicativePersistenceOptimized(int num, int base, int& steps) {
    if (num < base) return num;  // Single-digit numbers return themselves

    if (memo.count(num)) {
        steps += memo[num];  // Use stored step count
        return num;          // Return the final reduced digit
    }

    vector<int> digits = getDigits(num, base);
    int product = 1;

    for (int d : digits) {
        product *= d;
    }

    steps++;  // Count the step before recursion

    int result = multiplicativePersistenceOptimized(product, base, steps);
    memo[num] = steps;  // Store the correct step count
    return result;
}

int main() {
    int base = 2;
    int num = 0;
    int minSteps = -1;
    int timeinc = 1; 
    int result;
    int results2;
        int steps = 0;
  
    //auto startTime = high_resolution_clock::now();
    //auto endTime = startTime + minutes(30); // Total runtime of 30 minutes

    //while (high_resolution_clock::now() < endTime) {
    //    int steps = 0;
    //    memo.clear(); // Reset memo for fresh calculations

    //    int result = multiplicativePersistenceOptimized(num, base, steps);

    //    // Update minSteps **before** printing
    //    if (steps > minSteps) {
    //        minSteps = steps;
    //        cout << "New smallest number with " << steps << " steps: " << num << " in base " << base << endl;
    //    }

    //    num++; // Increment number

    //    // Debug print statements to monitor progress
    //    auto elapsedTime = duration_cast<minutes>(high_resolution_clock::now() - startTime).count();
    //    /* cout << "Current base: " << base << ", num: " << num << ", minSteps: " << minSteps << ", timeinc: " << timeinc << ", elapsed time: " << elapsedTime << " minutes" << endl;*/

    // //    // Check elapsed time to move to the next base
    //    if (elapsedTime >= timeinc) {
    //        base++;      // Move to the next base

    //        num = 0;
    //        minSteps = -1;

    //        //        // Reset startTime to current time
    //        startTime = high_resolution_clock::now();

    //        //        // Debug print statements
    //        //        cout << "Time increment reached! Moving to base " << base << endl;
    //        //        cout << "Next time increment: " << timeinc << " minutes" << endl;
    //        //    }


    //        this_thread::sleep_for(milliseconds(100));
    //        if (base > 16) {
    //            break;
    //        }
    //    }
    //}
        //test function
       /*
        auto time = high_resolution_clock::now();
        random_device rd;
        mt19937 gen(rd());
        int failcounterl = 0;
        uniform_int_distribution<> dist1(0, 1000);
        uniform_int_distribution<> dist2(2, 16);
            auto endTime = time+ chrono::minutes(10);
            while ( high_resolution_clock::now() <endTime){
                num = dist1(gen);
                base = dist2(gen);

                result = multiplicativePersistenceOptimized(num, base, steps = 0);
                results2 = multiplicativePersistenceNaive(num, base, steps = 0);
        
                    if( result != results2){
                        cout<<"fail"<<endl;
                       failcounterl++;
        
                    }
                }
            cout<<"after ten min it failed "<<failcounterl<< " times "<<endl;*/

    //        //test function ends
        base = 10;
    std::cout << "enter an number no mattter how big" << endl;
    while (true) {
        cin >> num;
        if (cin.fail()) {  // Check if input is not an integer
            cin.clear();  // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore invalid input
            cout << "Invalid input! Please enter a valid number: ";
        }
        else {
            break;  // Valid input, exit loop
        }
    }



   // auto s3 = high_resolution_clock::now();
    results2 = multiplicativePersistenceNaive(num, base, steps = 0);
   // auto e3 = high_resolution_clock::now();
   // auto d3 = duration_cast<nanoseconds>(e3 - s3);
   ///* auto s1 = high_resolution_clock::now();*/
    result = multiplicativePersistenceOptimized(num, base, steps = 0);
   // /*auto e1= high_resolution_clock::now();
   // auto d1 = duration_cast<nanoseconds>(e1 - s1);*/
    if (result == results2){
    cout << "Final digit: " << result << " in " << steps << " steps." << endl;
    }else {
    cout<<"there is something wrong"<<endl;
    }
   // /*cout << "the optimed version took " << d1.count() << " nanoseconds" << endl;
   // cout << "the unoptimized version took " << d3.count() << " nanoseconds" << endl;*/
    return 0;
}
   