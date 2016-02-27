#include <iostream>
using namespace std;


int main(){
	int casos;
	int f, m;
	char code;
	
	freopen( "in.txt", "r", stdin );
	freopen( "out.txt", "w", stdout );
	
	cin >> casos;
	while( casos-- ){
		f = m = 0;
		
		cin >> code;
		while( code != '\n' && cin.eof() == false ){
			if( code == 'f' || code == 'F' )
				++f;
			else if( code == 'm' || code == 'M' )
				++m;
			cin.get( code );
		}
		
		if( m == f && m + f != 2 )
			cout << "LOOP" << endl;
		else
			cout << "NO LOOP" << endl;		
	}
}
