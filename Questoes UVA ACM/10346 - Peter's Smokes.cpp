//#include <cstdio>
#include <iostream>
using std::cin;
using std::cout;

int main(){
	int n, k, temp, aux;

//	freopen( "in.txt", "r", stdin );
//	freopen( "out.txt", "w", stdout );
	
	while( cin >> n >> k ){
		
		temp = n;

		while( n >= k ){
			aux = n / k;
			temp += aux;
			n = aux + ( n % k );
		}

		cout << temp << "\n";
	}
		
	cout.flush();
}
