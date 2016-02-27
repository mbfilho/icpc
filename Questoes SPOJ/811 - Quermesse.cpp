#include <iostream>
using namespace std;

int main(){
	int part, ingre;
	bool vencedor = false;
	int teste = 1;
	
	
	cin >> part;
	while( part ){
		vencedor = false;
		cout << "Teste " << teste++ << endl;
		for( int i = 1; i <= part; ++i ){
			cin >> ingre;
			if( ingre == i && !vencedor ){
				vencedor = true;
				cout << i << endl;
			}
		}
		cout << endl;
		cin >> part;
	}
}
