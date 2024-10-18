#include <iostream>  

unsigned long long factorial(int n);  
  
int main() {  
    for (int i = 1; i <= 10; ++i) {  
        std::cout << "Factorial of " << i << " is " << factorial(i) << std::endl;  
    }  
    return 0;  
}  

unsigned long long factorial(int n) {  
    unsigned long long result = 1;  
    for (int i = 1; i <= n; ++i) {  
        result *= i;  
    }  
    return result;
}