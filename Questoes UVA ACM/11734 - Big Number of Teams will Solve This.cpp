#include <iostream>
#include <string>
using namespace std;

int main(){
	char final[ 21 ];
	string envio, juiz;
	int casos;
	bool fora, correto;
	
	
	cin >> casos;
	
	char buffer;
	int i;
	for( int k = 1; k <= casos; ++k ){
		i = 0;
		fora = false;
		correto = true;
		
		while( cin.peek() == '\n' )
			cin.ignore();
			
		getline( cin, envio );
		cin >> juiz;
		
		for( int u = 0; u < envio.size(); ++u ){
			if( envio[ u ] == ' ' ){
				fora = true;
			}else if( envio[ u ] != '\n' )
				final[ i++ ] = envio[ u ];			
		}
		final[ i ] = '\0';
		i = 0;
		
		while( final[ i ] != '\0' && juiz[ i ] != '\0' ){
			if( final[ i ] != juiz[ i ] ){
				correto = false;
				break;
			}
			++i;
		}
		if( final[ i ] != '\0' || juiz[ i ] != '\0' )
			correto = false;
		
		
		if( correto == false )
			cout << "Case " << k << ": Wrong Answer" << endl;
		else{
			if( fora )
				cout << "Case " << k << ": Output Format Error" << endl;
			else
				cout << "Case " << k << ": Yes" << endl;
		}
		
	}
}
