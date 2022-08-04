import subprocess
import sys

file = "TODO"
if len(sys.argv) > 1:
	file = str(sys.argv[1])
fd = open(file, "r")
tests = fd.readlines()
p = subprocess.Popen("./minishell", stdin=subprocess.PIPE)
for test in tests:
	p.stdin.write(test.encode())
p.stdin.close()
p.terminate()