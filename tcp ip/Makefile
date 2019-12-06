#
# POSIX calls
# TCP/IP API
# Makefile
#

GC = gcc
GCC = arm-linux-gcc

CFLAGS = -O2 -Wall -Werror
LDFLAGS = -lrt

SSERVER = TCPEchoServer.c
SSCLIENT = TCPEchoClient.c

SAUX = Auxiliary.c
SCLNSOK = CreateTCPClientSocket.c
SSRVSOK = CreateTCPServerSocket.c
SACCEPT = AcceptTCPConnection.c 
SHANDLE = HandleTCPClient

SERVER = TCPEchoServer 
CLIENT = TCPEchoClient

AUX = Auxiliary
CLNSOK = CreateTCPClientSocket
SRVSOK = CreateTCPServerSocket
ACCEPT = AcceptTCPConnection
HANDLE = HandleTCPClient

.PHONY: all clean

all: $(AUX) $(CLNSOK) $(SRVSOK) $(ACCEPT) $(HANDLE) $(AUX) $(SERVER) $(CLIENT)

$(AUX): $(AUX).o
	$(GC) -o $@ $^ $(LDFLAGS)
	@echo Auxiliary 
	
$(AUX).o: $(SAUX)
	$(GC) -c $(CFLAGS) -o $@ $^
	
$(CLNSOK): $(CLNSOK).o
	$(GC) -o $@ $^ $(LDFLAGS)
	@echo CreateTCPClientSocket 

$(CLNSOK).o: $(SCLNSOK)
	$(GC) -c $(CFLAGS) -o $@ $^

$(SRVSOK): (SRVSOK).o
	$(GC) -o $@ $^ $(LDFLAGS)
	@echo CreateTCPServerSocket 
	
$(SRVSOK).o: $(SSRVSOK)
	$(GC) -c $(CFLAGS) -o $@ $^
	
$(ACCEPT): $(ACCEPT).o
	$(GC) -o $@ $^ $(LDFLAGS)
	@echo AcceptTCPConnection 
	
$(ACCEPT).o: $(SACCEPT)
	$(GC) -c $(CFLAGS) -o $@ $^
	
$(HANDLE): $(HANDLE).o
	$(GC) -o $@ $^ $(LDFLAGS)
	@echo HandleTCPClient 

$(HANDLE).o: $(SHANDLE)
	$(GC) -c $(CFLAGS) -o $@ $^

#$(CLIENT): $(CLIENT).o  
#	$(GC) -o $@ $^ $(LDFLAGS)
#	@echo Binaries for CLIENT are made
#
#$(CLIENT).o: $(SCLIENT)
#	$(GC) -c $(CFLAGS) -o $@ $^
#
#$(SERVER): $(SERVER).o
#	$(GC) -o $@ $^ $(LDFLAGS)
#	@echo Binaries for SERVER are made
#
#$(SERVER).o: $(SSERVER)
#	$(GC) -c $(CFLAGS) -o $@ $^

# Code for cross-compilation
#
#$(TARGET): $(TARGET).o
#	$(GCC) -o $@ $^ $(LDFLAGS)
#	@echo Binaries for TARGET are made
#
#$(TARGET).o: $(SOURCES)
#	$(GCC) -c $(CFLAGS) -o $@ $^

clean:
	rm -rf $(HOST) $(HOST).o
	rm -rf $(TARGET) $(TARGET).o

