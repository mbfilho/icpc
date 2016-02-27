#include <iostream>
#include <string>
using namespace std;

int main(){
	string n1, n2;
	int casos, j1, j2;
	int teste = 1;
	
	cin >> casos;
	while( casos ){
		
		cin >> n1 >> n2;
		cout << "Teste " << teste++ << endl;
		for( int i = 0; i < casos; ++i ){
			cin >> j1 >> j2;
			if( ( j1 + j2 ) % 2 == 0 )
				cout << n1 << endl;
			else
				cout << n2 << endl;
		}
		cout << endl;
		cin >> casos;
	}
}