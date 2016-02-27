#include <iostream>
#include <string>
using namespace std;

int main(){
	int casos, j1, j2;
	int teste = 1;
	int a = 0, b = 0;
	
	cin >> casos;
	while( casos ){
		a = 0;
		b = 0;
		cout << "Teste " << teste++ << endl;
		for( int i = 0; i < casos; ++i ){
			cin >> j1 >> j2;
			a += j1;
			b += j2;
		}
		
		if( a > b )
			cout << "Aldo\n";
		else
			cout << "Beto\n";
		cout << endl;
		cin >> casos;
	}
}
