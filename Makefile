#give PN the name of your c file wihich contains main

PN=usb
PN1=usb1
CCA=arm-linux-gcc
CCL=gcc

CFLAGS=-Wall -Werror                      

all: $(PN) $(PN1)

$(PN): $(PN).o
	$(CCL) $(CFLAGS) -o $(PN) $(PN).o -lusb-1.0

$(PN1): $(PN1).o
	$(CCA) $(CFLAGS) -o $(PN1) $(PN1).o -lusb-1.0
	

$(PN).o: $(PN).c
	$(CCL) -c -o $(PN).o $(PN).c

$(PN1).o: $(PN).c
	$(CCA) -c -o $(PN1).o $(PN).c
	
clean:
	rm -rf $(PN) $(PN).o $(PN1) $(PN1).o

download:
	sshpass -p 'root' scp $(PN1) root@10.0.0.42:/bin/EL
	
	

