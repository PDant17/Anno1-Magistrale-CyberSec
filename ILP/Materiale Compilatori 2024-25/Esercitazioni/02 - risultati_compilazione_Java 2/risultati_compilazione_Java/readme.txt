Lanciare da una finestra di terminale i comandi .sh nella cartella per ottenere quanto promesso dal nome del file.

Questi comandi funzionano sicuramente con 
openjdk version "13.0.6" 2021-01-19.  (magari anche altre versioni)

e spoon (già presente nella cartella - https://spoon.gforge.inria.fr/index.html) 

Cosa fare:
1. esegui nel terminale il comando
./mostraJavaAST.sh

->  visualizzerà l'Abstract Syntax Tree (AST) del programma HelloWorld.java in una finestra spoon. 


2. esegui nel terminale il comando
./mostraJavaBytecode.sh HelloWorld.class 

-> mostrerà a video il bytecode contenuto nel file .class