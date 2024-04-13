# Alpha Phase 2

Alpha is a compiler project made for the needs of CS-340, 2023-2024 at the Computer Science department, University of Crete.
Phase 2 consists of the syntax analysis made using flex/yacc/bison. 

## Features
 * Symtable and Grammar are correctly implemented
 * The output is the desired one, as said in the assignment
 * Scopes are not fully implemented especially for the functions
 * The function scope handling has problems like when inserting in the symtable the arguments do not have the right scope and when we insert a function with the same name in another scope it is not inserted.
 * Shadowing for scopes is also not fully implemented.

## Installation
We have a Makefile 
Alternatively, run the following commands:
* run : make
* clean : make clean

## Authors
This project was made in collaboration with [Georgia Tsanta / csd5020](https://github.com/georgiats0) and [Dimitris Asimakopoulos / csd4845](https://github.com/mitsosasim).


## Credits
The project was made for the needs of CS-340 and our lecturer [Prof. Antonis Savvidis]().

## Contributing

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.

## License

[MIT](https://choosealicense.com/licenses/mit/)
