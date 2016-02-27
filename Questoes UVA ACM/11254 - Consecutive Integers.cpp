#include <iostream>
using namespace std;

int main(){
	int n, melhorn, melhora;
	
	
	cin >> n;
	
	while( n != -1 ){
		melhorn = 1;
		melhora = n;
		
		int i = 2;
		int temp;
		

		while( i < 10 + n / 2 ){
			temp = 2 * n - i * ( i - 1 );
			if( temp <= 0 )
				break;
			if( temp % (2 * i) == 0 ){
				melhorn = i;
				melhora = temp / ( 2 * i );
			}
			++i;
		}
		
		
		cout << n << " = " << (melhora) << " + ... + " << (melhora + melhorn - 1) << endl;
		cin >> n;
		
	}
}
