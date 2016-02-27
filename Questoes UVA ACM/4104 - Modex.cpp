#include <iostream>
using namespace std;

int main(){
	int x, y, n, z;
	int casos;
	
	cin >> casos;

	while( casos-- ){
		cin >> x >> y >> n;
		z = 1;

		while( y ){
			if( y & 1 )
				z = ( z * x ) % n;
			
			x = ( x * x ) % n;
			y = y >> 1;
		}

		cout << z << endl;
	}
}
