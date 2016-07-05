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

printInput()
sendCommand('-break-insert main')
readUntil('^done')
sendCommand('-exec-run')
readUntil('*stopped')
