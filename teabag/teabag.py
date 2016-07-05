#!/usr/bin/env python3

import subprocess

print("Hello")


gdb = subprocess.Popen(["/usr/bin/gdb", "--interpreter=mi", "/home/maciek/workspace/build/teabag-debug/test"], stdin=subprocess.PIPE, stdout=subprocess.PIPE, universal_newlines=True, bufsize=1)

def readInput():
	lines = []
	while(True):
		l = gdb.stdout.readline().strip()
		#print('l=%s' % l)
		if l == '(gdb)':
			return lines
		
		lines.append(l)

def sendCommand(command):
	print('<<< sending: %s' % command)
	gdb.stdin.write(command + '\n')

def printInput():
	print('>>> in: %s' % readInput())

def readUntil(inputClass):
	while(True):
		lines = readInput()
		print('>>> in: %s' % lines)
		for line in lines:
			if line.startswith(inputClass):
				return

def execCommand(cmd):
	sendCommand(cmd)
	printInput()

printInput()
execCommand('-break-insert main')

sendCommand('-exec-run')
readUntil('*stopped')

execCommand('-stack-info-frame')
execCommand('-stack-info-depth')
execCommand('-stack-list-arguments --all-values')
execCommand('-stack-list-frames')
execCommand('-stack-list-locals --simple-values')
execCommand('-stack-list-variables --simple-values')
execCommand('-symbol-list-lines /home/maciek/workspace/build/teabag-debug/test.cc')
execCommand('-data-disassemble -f test.cc -l 4 -n 1 0')
execCommand('-data-evaluate-expression &argc')
execCommand('-data-evaluate-expression &argv')
execCommand('-data-evaluate-expression &s')
execCommand('-data-evaluate-expression sizeof(s)')

while(True):
	print('==================')
	sendCommand('-exec-step')
	readUntil('*stopped')
	execCommand('-stack-info-depth')


