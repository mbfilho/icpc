#include <cstdio>
#include <iostream>
using namespace std;

/*
Posição é perdedora (primeiro jogador) se K = i*L + i
*/
int main(){
	ios_base::sync_with_stdio(false);
	int k;
	cin >> k;
	
	int tmp = 1000000000;
	for(int i = 1; k > i;++i){
		if((k-i) % i == 0 && (k-i) / i >= 2){
			tmp = (k-i) / i;
		}
	}

	cout << tmp << "\n";
	
}

