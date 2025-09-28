import java.io.EOFException;
..

public class Lexer {
	
	private File input;
	private static .. keywordTable;  // la struttura dati potrebbe essere una hash map
	private ... stringTable// la symbol table in questo caso si riduce ad una semplice stringTable
	private int state;
    ..

	public Lexer(){
		// per la semplicità di questo esercizio si potrebbe evitare di fare due tabelle
		keywordTable = new ..
		stringTable = new  ..
		state = 0;
		keywordTable.put("if", new Token("IF"));   // inserimento delle parole chiavi nella keywordTable per evitare di scrivere un diagramma di transizione per ciascuna di esse (le parole chiavi verranno "catturate" dal diagramma di transizione e gestite e di conseguenza). IF poteva anche essere associato ad una costante numerica
        ..

	}
	
	public Boolean initialize(String filePath){
	
	   // prepara file input per lettura e controlla errori
	    
	} 
	
	public Token nextToken()throws Exception{
		
		//Ad ogni chiamata del lexer (nextToken())
		//si resettano tutte le variabili utilizzate
		state = 0;
		String lessema = ""; //è il lessema riconosciuto
        char c;
        ..
		
		while(true){

			 // legge un carattere da input e lancia eccezione quando incontra EOF per restituire null
			 //  per indicare che non ci sono più token
			
            c = ..
            ..
			
			
			//id
			switch(state){
				case 9:
					if(Character.isLetter(c)){
						state = 10;
						lessema += c;
						// Nel caso in cui il file è terminato ma ho letto qualcosa di valido
						// devo lanciare il token (altrimenti perderei l'ultimo token, troncato per l'EOF) 
						if( // controlla se è finito il file){
							return installID(lessema);
						}
						break;
					}
					state = 12;
					break;
					
				case 10:
					if(Character.isLetterOrDigit(c)){
						lessemq += c;
						if(// controlla se è finito il file)
							return installID(lessema);
						break;
					}else{
						state = 11;
						retrack();
						return installID(lessema);
					}
				default: break;
			}//end switch
			
			//unsigned numbers
			switch(state){
				case 12:
					if(Character.isDigit(c)){
						state = 13;
						lessema += c;
						if(// controlla se è finito il file){
							return new Token("NUMBER", lessema);
						}
						break;
					}
					state = 22;
					break;
                           
                case 13:
				..
           }
		}//end while
	}//end method
		
  
private Token installID(String lessema){
	Token token;
	
	//utilizzo come chiave della hashmap il lessema
	if(keywordTable.containsKey(lessema))
		return keywordTable.get(lessema);
	else{
		token =  new Token("ID", lessema);
		stringTable.put(lessema, token);
		return token;
	}
}
	

private void retrack(){
	// fa il retract nel file di un carattere
}
		
}
