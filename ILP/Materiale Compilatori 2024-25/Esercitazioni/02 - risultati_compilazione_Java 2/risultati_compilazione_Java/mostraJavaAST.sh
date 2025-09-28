#!/bin/sh
echo "usage: ./mostraJavaAST.sh  <file.java>"
echo "Attendere prego!! Apparirà una finestra Spoon"
java -cp spoon-core-9.2.0-beta-6-jar-with-dependencies.jar spoon.Launcher -i HelloWorld.java --gui