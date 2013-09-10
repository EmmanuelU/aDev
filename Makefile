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
	@curl http://www.rootfiles.org/pub/mirror/xmcwildchild22/aDev/tools.zip > tools.zip
	clear
	@chmod +x CheckForTools.sh
	./CheckForTools.sh
	@-rm -f CheckForTools.sh
	@-rm -f tools.zip
	clear
	@-rm -rf *.sh
	@-rm -rf tools.zip
	@chmod +x bin/*
	@echo "aDev configured, please Run: '/./tmp/aDev.sh' right now."
	@echo 
	@echo "Then run 'aDev test' to confirm aDev installed properly"
