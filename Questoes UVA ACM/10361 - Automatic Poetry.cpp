#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <iostream>
using namespace std;

string l1, l2;

void ig(){
	while( cin.peek() == '\n' ) cin.ignore();
}

int main(){
	int n;
	
	while( scanf( "%d", &n ) != EOF ){
		for( int i = 0; i < n; ++i ){
			ig();
			getline( cin, l1 );
			ig();
			getline( cin, l2 );
			
			int a, b, ind; 
			for( ind = 0; ind < l1.size(); ++ind ){
				if( l1[ ind ] == '<' )
					a = ind;
				else if( l1[ ind ] == '>' ){
					b = ind;
					break;
				}
			}
			string s2 = l1.substr( a + 1, b - a - 1 );
					
			int a2, b2;
			for( ind += 1; ind < l1.size(); ++ind ){
				if( l1[ ind ] == '<' )
					a2 = ind;
				else if( l1[ ind ] == '>' ){
					b2 = ind;
					break;
				}
			}
				
			string s3 = l1.substr( b + 1, a2 - b - 1 );
		//	cout << "2: " << a2 << " " << b2 << endl;
			string s4 = l1.substr( a2 + 1, b2 - a2 - 1 );
			string s5 = l1.substr( b2 + 1 );
			
			for( int i = 0; i < l1.size(); ++i ){
				if( l1[ i ] == '<' || l1[ i ] == '>' ) continue;
				cout << l1[ i ];
			}
			
			cout << endl;
			cout << l2.substr( 0, l2.find( "..." ) ) << s4 << s3 << s2 << s5 << endl;
		//	cout << "S2 " << s2 << endl << "S3 " << s3 << endl << "S4 " << s4 << endl << "S5 " << s5 << endl;
		}
				
	}
}

