#include <iostream>
#include <string>
using namespace std;

int mdc( int a, int b ){
		if( a < b ){
			int temp = a;
			a = b;
			b = temp;
		}

	while( b ){
		int temp = a % b;
		a = b;
		b = temp;
	}
	
	if( a == 1 )
		return 0;
	
	return a;
	
	
	
}

int main(){
	int vezes;
	string s1, s2;
	int num1, num2;
	
	freopen( "in.txt", "r", stdin );
	freopen( "out.txt", "w", stdout );
	
	cin >> vezes;
	for( int k = 1; k <= vezes; ++k ){
				
		cin >> s1 >> s2;
		
		num1 = num2 = 0;
		for( int i = s1.length() - 1; i >= 0; --i ){
			if( s1[ i ] == '1' )
				num1 = num1 | ( 1 << (s1.length() - 1 - i) );
		}
		
		for( int i = s2.length() - 1; i >= 0; --i ){
			if( s2[ i ] == '1' )
				num2 = num2 | ( 1 << (s2.length() - 1 - i) );
		}
		
		if( mdc( num1, num2 ) )
			cout << "Pair #" << k << ": All you need is love!" << endl;
		else
			cout << "Pair #" << k << ": Love is not all you need!" << endl;
	}
}
