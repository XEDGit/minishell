import subprocess
from time import sleep

fd = open("TODO", "r")
tests = fd.readlines()
p = subprocess.Popen("./minishell", stdin=subprocess.PIPE)
sleep(1)
for test in tests:
	p.stdin.write(test.encode())
	# sleep(1)
# print(p.stdout.read())
