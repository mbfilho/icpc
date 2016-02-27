import java.util.*;
import java.math.*;

class Main{
	static int mapa[] = new int[300];	

	public static BigInteger Converter(String num, int base){
		BigInteger ret = new BigInteger("0"), b = new BigInteger(base +"");

		
		for(int i = 0; i < num.length(); ++i){
			ret = ret.multiply(b).add( new BigInteger(mapa[num.charAt(i)]+"") );
//			b = b.multiply(basis);
		}
		
		return ret;
	}
	
	public static String safe(String a){
		String ret = "";
		for(int i = 0; i < a.length(); ++i){
			if((int)a.charAt(i) > 0x20) ret += ("" + a.charAt(i));
		}
		return ret;
	}
	
	public static void main(String args[]){
		Scanner sc = new Scanner(System.in);
		String linha;
		boolean novo = true;

		while( sc.hasNextLine() && (linha = sc.nextLine()) != null){
			linha = safe(linha);
			if(linha.equals("")) continue;
			if(novo) novo = false;
			else System.out.println();

			
			//System.out.println(">>> " + linha);
			for(int i = 0; i < mapa.length; ++i) mapa[i] = 0;
			
			for(int i = 0, j = linha.length(); i < j; ++i){
				if(linha.charAt(i) == ' ') throw new RuntimeException();
				mapa[linha.charAt(i)] = i;
			}			
			
			String num = null;
			while(sc.hasNextLine() && (num = sc.nextLine()) != null){
				if(num.equals("")) break;
				num = safe(num);
				//num = num.replace(" ", "");
				//System.out.println("|" + num + "|");
				int menor = 1;
				
				for(int i = 0; i < num.length(); ++i){
					menor = Math.max(menor, mapa[num.charAt(i)]);
				}
				//System.out.println("Menor " + menor);
				BigInteger soma = BigInteger.ZERO;
				for(int i = menor + 1; i <= linha.length(); ++i){
					
					//System.out.println("*");
					soma = soma.add(Converter(num,i));
				}
				
				System.out.println(soma);
			}
		}
	}
}