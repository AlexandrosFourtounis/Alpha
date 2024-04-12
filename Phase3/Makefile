.PHONY: phase3 clean


phase3:
	@echo "Building phase 3..."
	bison --yacc --defines --output=parser.c parser.y -v 
	flex --outfile=scanner.c scanner.l
	gcc -o parser parser.c scanner.c SymTable.c symtablehash.c -g

clean:
	@echo "Cleaning up..."
	# Add cleanup commands here
	rm -f parser.c parser.h scanner.c parser.output parser