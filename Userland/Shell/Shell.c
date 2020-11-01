#ifndef SHELL
#define SHELL

#define TOTAL_LINES 64
#define MAX_LINE_LENGTH 128


static char * lines[TOTAL_LINES];

void startShell() {
  //Inicia la linea de comandos
  // while(1) {
  //   drawShell();
  // }
}

void moveUpLines() {
  //Mueve todas las lineas para arriba
}

void drawShell() {
  //dibuja la shell
}

void executeCommand(char * command) {
  //lee el comando de la primera linea y se fija de ejecutarlo
}

#endif
