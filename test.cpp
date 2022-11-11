#include"exint.hpp"
#include<iostream>
using namespace std;
exint<int> ex1, ex2;

#define Ex_io

int main(void){
	string str = "100123";
	exread_string(ex1);exread_string(ex2);
	cout << ex1 + ex2 << endl;// << ex1 - ex2 << endl << ex1 * ex2 << endl << ex1 / ex2 << endl << ex1 % ex2 << endl;
	return 0;
}