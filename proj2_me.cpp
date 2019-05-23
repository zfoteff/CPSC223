/*
Class: CPSC 122-01
Team Member 1: Zac Foteff
Team Member 2: None
Submitted by: Zac Foteff
GU Username: zfoteff
File Name: proj2.cpp
Program displays user defined amount of prime numbers calculated by program and
displays them in user defined amount of columns

To Build: g++ proj2.cpp -o proj2
To Execute: ./proj2
*/



#include <iostream>
#include <fstream>
using namespace std;

void display(int, int, ofstream&);
bool isPrime(int);

int main(int argc, char* argv[]){


int P, N; // prime numbers to be generated, number of columns
ofstream fout;
fout.open(argv[1]);


//primes
cout<< "How many prime numbers do you want printed out? ";
cin>> P;

while (P <= 1){
	cout<<"Please enter a number greater than 1: ";
	cin>> P;
}

//number of cols
cout<< "How many columns should the numbers be outputted in: ";
cin>> N;

while (N <= 0){
	cout<< "Please enter a number greater than 0: ";
	cin>> N;
}
//makes sure cols doesn't exceeed number of primes
while (N > P){
	cout<< "Please enter fewer columns than numbers: ";
	cin>> N;
}

display(P, N, fout);
cout<<"\nComplete."<<endl;


cout<<endl;
return 0;
}

/*

Pre: Input number of primes >= 1, number of 
columns < number of primes

Post: Uses modulus and while loop to 
output user specified number of columns and
prime numbers

*/
void display(int numPrimes, int numCols, ofstream& fOut){
	int counter = 0; // value that helps exit the loop
	int x = 2;
	
	while(counter< numPrimes){
		
		if(isPrime(x)){
			fOut<< x<< '\t';
			if(counter % numCols == numCols - 1){
				fOut<<endl;
			}
			counter++;
		}
		
		x++;
	}
}



/*

Pre: input number x to be checked for primality

Post: Uses modulus and for loops to check each 
number's primality. If it is prime, true is returned.
If the number is not prime false is returned

*/ 
bool isPrime(int x){
	
	if (x == 2)
		return true;

	if (x< 2)
		return false;
	
	
	//covers the most common devisor
	if(x % 2 == 0)
		return false;
	
	
	// since all even numbers are elimanated, this will increment through all odd numbers up to half the user inputted number
	for (int i = 3; i < x/2; i += 2){
		
		if(x % i == 0)
			return false;
		
	}
	return true; // this is if the number goes through all numbers in for loop and is prime
}