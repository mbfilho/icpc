#include <iostream>
using namespace std;

int main(){
	char palavra[ 100 ];
	char *temp;
	int casos, indice;
	
	cin >> casos;
	for( int i = 1; i <= casos; ++i ){
		cin >> indice >> palavra;
		--indice;
		palavra[ indice ] = '\0';
		temp = palavra + indice + 1;

		cout << i << " " << palavra << temp << endl;
	}
}
