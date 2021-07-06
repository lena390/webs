#!/usr/bin/python
import sys
import argparse
import os

CYAN = "\033[1;36m"
RESET = "\033[0;0m"
GREEN = "\033[0;32m"
RED   = "\033[1;31m"

parser = argparse.ArgumentParser()
parser.parse_args()
sys.stdout.write(CYAN)
print("Program args:")
sys.stdout.write(RESET)
print(parser)
sys.stdout.write(GREEN) 
print("Program enviroment:")
sys.stdout.write(RESET)
print(os.environ)

sys.stdout.write(RED) 
print("HELLO WORLD MOTHERFUCKER")
sys.stdout.write(RESET)

	# std::cout << RED UNDER "Hello World, motherfucker!" END << std::endl;
	# return (0);