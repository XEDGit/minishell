from asyncio.subprocess import DEVNULL
import subprocess
import sys

def send_cmd(prog):
	p = subprocess.Popen(prog, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=DEVNULL)
	p.stdin.write(test.encode())
	p.stdin.close()
	p_res = p.stdout.read()
	p.stdout.close()
	p.terminate()
	p.wait()
	return p.returncode, p_res.decode().rstrip("\n")

def col(str, col):
	return f"\033[{col}m{str}\033[0m"

file = "tests"
single = -1
noout = True
sep = "\n\033[1m________________________________________________________________\033[0m\n"
if len(sys.argv) > 1:
	if str(sys.argv[1]) == "-o":
		noout = False
	else:
		single = int(sys.argv[1]) - 1
if len(sys.argv) > 2:
	if str(sys.argv[2]) == "-o":
		noout = False
	else:
		file = str(sys.argv[2])
if noout and len(sys.argv) > 3:
	file = str(sys.argv[3])
fd = open(file, "r")
tests = fd.readlines()
for i, test in enumerate(tests):
	if single != -1 and i != single:
		continue
	mini_code, mini_res = send_cmd("./minishell")
	bash_code, bash_res = send_cmd("bash")
	diff = col("Fail", "31")
	if mini_res == bash_res:
		diff = col("Success!", "32")
	if mini_code != bash_code:
		diff = col("Wrong exit code", "33")
	test = test.rstrip("\n")
	if noout:
		out = f"{col(f'Line {i + 1}: ', '1;31')}{test} {diff}{sep}"
	else:
		out = f"{col(f'Line {i + 1}: ', '1;31')}{test}\n{col('minishell: ', '31')}\n'{mini_res}'\n{col('exit code: ', '31')}{mini_code}\n{col('bash: ', '31')}\n'{bash_res}'\n{col('exit code: ', '31')}{bash_code}\n{diff}{sep}"
	print(out)
	