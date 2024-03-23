.PHONY: phase2 clean


phase2:
	@echo "Building phase 2..."
	bison --yacc --defines --output=parser.c parser.y -v 
	flex --outfile=scanner.c scanner.l
	gcc -o parser parser.c scanner.c 

clean:
	@echo "Cleaning up..."
	# Add cleanup commands here
	rm -f parser.c parser.h scanner.c