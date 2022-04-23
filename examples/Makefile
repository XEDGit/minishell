OUTS:= $$(echo `find . -name '*.c' | cut -d "/" -f 2 | cut -d "." -f 1`)

ERROR:= \e[1;31m

MAGENTA:= \e[1;35m

BOLD:= \e[1m

OUTPUT_END:= \e[30;47m

RESET:= \e[0m

all:
	@C=0;\
	printf "Which file do you want to run?\n\n$(MAGENTA)";\
	for f in $(OUTS); do\
		((C=C+1));\
		printf "  $$C) $$f\n";\
	done;\
	C2=0;\
	printf "$(RESET)\nSelect a number: ";\
	read -rn1 TO_TEST;\
	if [[ $$TO_TEST == q || $$TO_TEST == $$(printf "\e") ]]; then\
		printf "\n";\
		exit 0;\
	fi;\
	for f in $(OUTS); do\
		((C2=C2+1));\
		if [[ ($$C2 -eq $$TO_TEST) ]]; then\
			FILE=$$f;\
		fi;\
	done;\
	if [ -z "$$FILE" ]; then\
		printf "\n$(ERROR)Error: Insert a number between 1 and $$C$(RESET)\n" >&2;\
		exit 1;\
	fi;\
	printf "$(MAGENTA)\nOutput:\n____________________\n$(RESET)";\
	gcc "./$$FILE.c" -o "$$FILE";\
	if [ $$? = 0 ]; then\
		./$$FILE;\
		rm $$FILE;\
		printf "$(OUTPUT_END)%%$(RESET)$(MAGENTA)\n____________________\n$(RESET)";\
	fi
