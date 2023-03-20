cd scriptsMenu
gcc startGame.c -o start
cd ..\\scriptsSinglePlayer
gcc main.c utilitaires.c definitions.h -o game -lpthread
cd ..\\scriptsMultiplayer
gcc main.c utilitaires.c definitions.h -o game -lpthread
cd ..\\scriptsMultiplayerNetwork\\Client
gcc main.c utilitaires.c definitions.h -o game -lpthread -lws2_32
cd ..\\Server
gcc main.c utilitaires.c definitions.h -o game -lpthread -lws2_32
cd ..
cd ..
cls