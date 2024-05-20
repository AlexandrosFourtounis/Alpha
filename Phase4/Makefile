.PHONY: phase4 clean


phase4:
	@echo "Building Phase 4..."
	@bison --yacc --defines --output=parser.c parser.y -v 
	@flex --outfile=scanner.c scanner.l 
	@gcc -o parser parser.c scanner.c SymTable.c symtablehash.c quads.c stack.c  -g

clean:
	@echo "Cleaning up..."
	@rm -f parser.c parser.h scanner.c parser.output parser
