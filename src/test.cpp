#include <stdio.h>
#include <math.h>
#include <iostream>



int main(){
	int angle1 = 45;
	double pi = 3.1415926535897;
	double a;
	a = tan(angle1 * pi / 180);
	std::cout << a << std::endl;
}