#include <iostream>
using std::cin;
using std::cout;

int main(){
	unsigned int femeas, machos, femeas_temp;
	int anos;

	cin >> anos;
	if( anos != -1 ){	
		while( anos != -1 ){
			femeas = 1;
			machos = 0;
			while( anos-- ){
				femeas_temp = femeas;
				femeas = machos + 1;
				machos += femeas_temp;	
			}
			cout << machos << " " << ( machos + femeas ) << std::endl;
			cin >> anos;
		}
	
	}	
}
