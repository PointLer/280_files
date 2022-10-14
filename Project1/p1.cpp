#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>

void print_prompt() {
    std::cout << "Please enter the integer and the test number: ";
}

//Four functions corresponding to four different kind of numbers
bool tetrahedral(int num);
bool palindrome(int num);
bool self_dividing(int num);
bool boring(int num);


int main() {
    //TODO: write your code here
    using namespace std;

    int test_number,test_type;
    bool test_result;

    //test whether the inputs are valid
    while(true){
        print_prompt();
        cin >> test_number >>  test_type;
        if(test_number > 0 && test_number <= 10000000 && test_type >= 1 && test_type <= 4)
            break;
    }

    //call specific function
    if(test_type == 1)
        test_result = tetrahedral(test_number);
    else if(test_type == 2)
        test_result = palindrome(test_number);
    else if(test_type == 3)
        test_result = self_dividing(test_number);
    else 
        test_result = boring(test_number);

    cout << test_result;
    return 0;
}

bool tetrahedral (int num){
    for(int i = 1; i * (i+1) * (i+2)  <= 6 * num; i++){
        if(i * (i+1) * (i+2)  == 6 * num)
            return true;
    }
    return false;
}

bool palindrome (int num){
    int reverse = 0;
    int temp = num;
    while(temp > 0){
        reverse = reverse * 10 + temp % 10;
        temp = temp / 10;
    }
    if(reverse == num)
        return true;
    else
        return false;

}

bool self_dividing (int num){
    int temp = num;
    int residue;
    while(temp > 0){
        residue = temp % 10;
        if(residue == 0)
            return false;
        else if(num % residue != 0)
            return false;
        temp = temp / 10;
    }
    return true;
}

bool boring (int num){
    if(num == 1)
        return false;

    int factor = 2;
    while(num > 1){
        while(num % factor == 0)
            num /= factor;
        factor += 1;
    }
    if(factor > 6)
        return false;
    else
        return true;
    
}