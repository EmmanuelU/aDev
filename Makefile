# CFLAGS =

all: clean aDev config

aDev: aDev.c
	clear
	@echo Building aDev ...
	@echo 
	@-rm -f aDev *.o
	@$(CC) $(CFLAGS) -o $@ $^
	@-rm -rf bin/aDev
	@mkdir -p bin
	@mv aDev bin
	@chmod +x bin/*
	@echo Done

clean:
	clear
	@echo Cleaning Workspace ...
	@-rm -rf aDev *.o *.zip tools *.sh bin *.txt
	@echo 
	@echo Done

config:
	clear
	@echo Downloading Proprietary Files ...
	@-rm -f tools.zip
	@curl http://www.rootfiles.org/pub/mirror/xmcwildchild22/aDev/CheckForTools.sh > CheckForTools.sh
	@curl http://www.rootfiles.org/pub/mirror/xmcwildchild22/aDev/CheckForComp.sh > CheckForComp.sh
	@wget http://www.rootfiles.org/pub/mirror/xmcwildchild22/aDev/tools.zip -O tools.zip
	clear
	@chmod +x CheckForTools.sh
	@chmod +x CheckForComp.sh
	./CheckForTools.sh
	clear
	@-rm -rf tools.zip
	@chmod +x bin/*
	./CheckForComp.sh
	@-rm -rf *.sh
	@-rm -rf *.zip
	@echo 
