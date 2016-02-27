#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

int main(){
	int fac, b, lsd;
	
	while( scanf( "%d %d %d", &b, &lsd, &fac ) == 3 ){
		int cont = 0, carry = 0, ult = lsd;
		
		do{
			++cont;
			int temp = ult * fac + carry;
			carry = temp / b;
			ult = temp % b;
		}while( ult != lsd || carry );		
		
		printf( "%d\n", cont );
		
	}
}



