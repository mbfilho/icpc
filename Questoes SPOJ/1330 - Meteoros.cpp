#include <iostream>
#include <string>
using namespace std;

int main(){
	int x1, y1, x2, y2;
	int teste = 1;
	int mete;
	int x, y;
	int cont;
	
	cin >> x1 >> y1 >> x2 >> y2;
	while( x1 | y1 | x2 | y2 ){
		cin >> mete;
		cont = 0;
		cout << "Teste " << teste++ << endl;
		for( int i = 0; i < mete; ++i ){
			cin >> x >> y;
			if( x >= x1 && x <= x2 && y <= y1 && y >= y2 )
				++cont;
		}
		
		cout << cont << endl;
		cout << endl;
		cin >> x1 >> y1 >> x2 >> y2;
	}
}
