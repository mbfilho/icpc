 #include <iostream>
 using namespace std;

int main(){
	int casos, pontos;
	int melhor,soma, temp, ia, ib, ja, jb;
	
	cin >> casos;
	
	for( int k = 1; k <= casos; ++k ){
		cin >> pontos;
		melhor = -1;
		soma = 0;
		ia = 1;
		ib = jb = 0;
		
		for( int i = 1; i < pontos; ++i ){
			cin >> temp;
			
			if( soma + temp >= temp ){
				soma += temp;
				ja = i + 1;
			}else if( soma + temp < temp ){
				soma = temp;
				ia = i;
				ja = i + 1;
			}
			
			if( melhor < soma ){
				melhor = soma;
				ib = ia;
				jb = ja;
			}else if( melhor == soma ){
				if( (ja - ia) > (jb - ib) ){
					ib = ia;
					jb = ja;	
				}
			}
		}
		
		if( melhor >= 0 ){
			cout << "The nicest part of route " << k << " is between stops " << ib 
				<< " and " << jb << endl;
		}else
			cout << "Route " << k << " has no nice parts" << endl;
	}
}
