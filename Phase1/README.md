# Alpha Phase 1

Alpha is a compiler project made for the needs of CS-340, 2023-2024 at the Computer Science department, University of Crete.
Phase 1 consists of a lexical analyzer made using flex. 
Flex uses defined regex patterns and the yylex function to parse the input.
Output can be seen in stdout as well as, an output file.

## Features
 * Strings are working correctly (including special chars, undefined chars and enters in a file (multiline string)).
 * Comments and multiline comments are parsed correctly.
 * Nested comments are not working (in a previous version they worked, but the analyzer stopped after encountering a nested comment).
 * Operators are working correctly.
 * Identifiers are working correctly.

## Installation
Run the following script (which runs the commands needed for compilation):
```python
python3 run.py
```
Alternatively, run the following commands:
* flex --outfile=al.c al.l
* gcc -o al al.c

## Authors
This project was made in collaboration with [Georgia Tsanta / csd5020](https://github.com/georgiats0) and [Dimitris Asimakopoulos / csd4845](https://github.com/mitsosasim).


## Credits
The project was made for the needs of CS-340 and our lecturer [Prof. Antonis Savvidis]().

## Contributing

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.

## License

[MIT](https://choosealicense.com/licenses/mit/)
