

Per vedere come 
1. Creare il risultato del preprocessore in helloworld.i 
-> Esegui da linea di comando, nella cartella,  "gcc -E helloworld.c  > helloworld.i"

2. Creare il risultato della compilazione in assembly in helloworld.s
-> Esegui da linea di comando, nella cartella,  "gcc -S helloworld.c  > helloworld.s"
   (produce file di testo con codice assembly)

3. Creare il risultato della compilazione ma prima del linking helloword.o   
-> Esegui da linea di comando, nella cartella,  "gcc -c helloworld.c  > helloworld.o"
   (produce codice macchina binario senza funzioni di libreria)

4. Creare eseguibile finale dopo compilazione e linking 
-> Esegui da linea di comando, nella cartella,  "gcc helloworld.c"
   (Usa gcc senza opzioni : produce file binario con codice macchina completo)

Lanciare i comandi da una finestra di terminale.
Bisogna avere gcc o clang istallati.

Per vedere tutte le opzioni di gcc (e di clang) vai a
https://clang.llvm.org/docs/CommandGuide/clang.html
