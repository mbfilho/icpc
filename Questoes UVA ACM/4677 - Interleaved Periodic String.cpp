#include <iostream>

using namespace std;

int main(){
	freopen( "in.txt", "r", stdin );
	freopen( "out.txt", "w", stdout );
	
	int casos, z, u;
	string str;
	scanf( "%d", &casos );
	
	for( int i=0; i<casos; i++ ){
		cin >> str;
		
		z = u = 0;
		for( int j=0; j<str.size(); j++ ){
			if( str[ j ] == '0' )
				z++;
			else
				u++;
		}
		
		if( z == 0 || u == 0 )
			cout << 1 << endl;
		else
			cout << 2 << endl;
	}
}
