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

file = "tests"
if len(sys.argv) > 1:
	file = str(sys.argv[1])
fd = open(file, "r")
tests = fd.readlines()
for i, test in enumerate(tests):
	mini_code, mini_res = send_cmd("./minishell")
	bash_code, bash_res = send_cmd("bash")
	diff = "\033[31mNo\033[0m"
	if mini_res == bash_res:
		diff = "\033[32mYes!\033[0m"
	if mini_code != bash_code:
		diff = "\033[33mWrong exit code\033[0m"
	test = test.rstrip("\n")
	out = f"ms:'{mini_res}' {mini_code} - bash:'{bash_res}' {bash_code} - Equal: {diff}"
	print("Line {:d}:{:<30.30s}	{:>75s}".format(i, test, out))
	