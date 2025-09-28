package esercitazione4;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.Reader;

public class Circuit {
    public static void main(String[] args) throws Exception {
        String res = "corretta!!";
        System.out.println("Type in circuit, hit Return, then Cmd-D (in MacOs) o Ctrl-D (in Windows)");
        InputStreamReader inp = new InputStreamReader(System.in);
        Reader keyboard = new BufferedReader(inp);
        parser p = new parser(new esercitazione4.Yylex(keyboard));
        try {
            p.debug_parse(); // l'uso di p.debug_parse() al posto di p.parse() produce tutte le azioni del parser durante il riconoscimento
        }
        catch(Exception e){
            res = "errata!!";
        }
            System.out.println("Frase " + res);
    }
}
