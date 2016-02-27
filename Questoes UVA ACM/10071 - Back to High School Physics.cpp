#include <iostream>
using namespace std;

int main(){
    int velocidade, tempo;
    int resposta;
    
    while( cin >> velocidade >> tempo ){
		resposta = velocidade * tempo * 2;  
		cout << resposta << endl;
    }
}
