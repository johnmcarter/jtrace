#--------------------------------------------------------------------
# John Carter
# makefile for jtrace
# Created: 2022/01/19 13:09:34
# Last modified: 2022/01/20 21:52:27
#--------------------------------------------------------------------

all:  jtrace
	
jtrace: jtrace.cpp utils.cpp
	g++ -Wall jtrace.cpp utils.cpp -o jtrace

clean: 
	rm jtrace