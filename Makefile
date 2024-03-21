.PHONY: phase1 phase2 clean

phase1:
	@echo "Building phase 1..."
	flex --outfile=Phase1/al.c Phase1/al.l
	gcc Phase1/al.c  -o Phase1/al

phase2:
	@echo "Building phase 2..."
	bison --yacc --defines --output=Phase2/parser.c Phase2/parser.y
	flex --outfile=Phase2/scanner.c Phase2/scanner.l
	gcc -o Phase2/parser Phase2/parser.c Phase2/scanner.c 

clean:
	@echo "Cleaning up..."
	# Add cleanup commands here
	rm -f Phase1/al.c Phase1/al
	rm -f Phase2/parser.c Phase2/parser.h Phase2/scanner.c