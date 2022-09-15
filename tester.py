from asyncio.subprocess import DEVNULL
from code import interact
from curses.ascii import isdigit
from genericpath import exists
import signal
import subprocess
import sys

def send_cmd(prog, test):
	p = subprocess.Popen(prog, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=DEVNULL)
	p.stdin.write(test.encode())
	p.stdin.close()
	p_res = p.stdout.read()
	p.stdout.close()
	p.terminate()
	p.wait()
	return p.returncode, p_res.decode().rstrip("\n")

def test_cmd(test, noout, i):
	sep = "\n\033[1m________________________________________________________________\033[0m\n"
	mini_code, mini_res = send_cmd("./minishell", test)
	bash_code, bash_res = send_cmd("bash", test)
	diff = col("Fail", "31")
	if mini_res == bash_res:
		diff = col("Success!", "32")
	if mini_code != bash_code:
		diff += " - " + col("Wrong exit code", "33")
	test = test.rstrip("\n")
	if noout:
		out = f"{col(f'Line {i + 1}: ', '1;31')}{test} {diff}{sep}"
	else:
		out = f"{col(f'Line {i + 1}: ', '1;31')}{test}\n{col('minishell: ', '31')}\n'{mini_res}'\n{col('exit code: ', '31')}{mini_code}\n{col('bash: ', '31')}\n'{bash_res}'\n{col('exit code: ', '31')}{bash_code}\n{diff}{sep}"
	print(out)

def col(str, col):
	return f"\033[{col}m{str}\033[0m"

def exit_interactive(code, frame):
	print("")
	exit(0)

def catch_args():
	argc = len(sys.argv) - 1
	single = -1
	noout = True
	interactive = False
	file_path = "tests"
	while argc >= 0:
		arg = str(sys.argv[argc])
		if arg == "-o":
			noout = False
		elif arg == "-i":
			interactive = True
		elif arg.isdigit():
			single = int(arg) - 1
		else:
			if not exists(arg):
				print("Error: '" + arg + "' isn't a valid file")
				exit(1)
			file_path = arg
		argc = argc - 1
	return noout, interactive, single, file_path

print(col("Welcome to the tester for the new 42 minishell!\n\t\tby XEDGit\n", "36;1"))
noout, interactive, single, file_path = catch_args()
fd = open(file_path, "r")
tests = fd.readlines()
fd.close()
if single != -1:
	test_cmd(tests[single], noout, single)
elif interactive:
	i = 1
	print(col("Enter a command line to test", "31"))
	signal.signal(signal.SIGINT, exit_interactive)
	while True:
		test = input(">")
		test_cmd(test, noout, i)
		i = i + 1
else:
	for i, test in enumerate(tests):
		test_cmd(test, noout, i)
		