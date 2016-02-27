#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main(){
	int teste = 1;
	int op;
	string exp;
	
	cin >> op;
	while( op ){
		cout << "Teste " << teste++ << endl;
		cin >> exp;
		int result;
		istringstream in( exp );
		in >> result;
		
		char ope;
		int num;
		for( int i = 0; i < op - 1; ++i ){
			in >> ope >> num;
			if( ope == '+' )
				result += num;
			else
				result -= num;
		}
		
		cout << result << endl;
		cout << endl;
		cin >> op;
	}
}
