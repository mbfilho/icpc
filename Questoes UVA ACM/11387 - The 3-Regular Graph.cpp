#include <iostream>
using namespace std;

int main(){
	int n;
	
	cin >> n;
	while( n != 0 ){
		if( n <= 3 || n % 2 != 0 )
			cout << "Impossible" << endl;
		else{
			int k = n / 2;
			cout << 3 * k << endl;
			for( int i = 1; i < n; ++i )
				cout << i << " " << (i + 1) << endl;
				
			for( int i = 1; i <= (n - k); ++i )
				cout << i << " " << (i + k) << endl;
			
			cout << n << " " << 1 << endl;
		}
		
		cin >> n;
	}
}
