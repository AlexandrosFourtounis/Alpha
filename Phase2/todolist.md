# Todo List

- [x] FAQ no.10 
- [x] insert with scope=0 to symboltable
- [x] save values from yylval for terminal chars
- [x] test all save files that they are working
- [x] FAQ no.7 works except: example = function (a,b) { return a + b; }
        it should be example = ( function (a,b) { return a + b; } ) based on grammar rules given.
- [ ] print grammar rules as they are found


IMPORTANT!!
- [x] Working/Anonymous works
- [ ] Working/Block works
- [ ] Working/Circle problem at line 12,20,27. (shouldnt be inserted into symboltable) --> can be fixed with scope sol. At the end they are being inserted into symboltable ??
- [] Working/GlobalAndLocal problem at line 9,10 --> can be fixed with scope sol. At the end they are being inserted into symboltable ??
- [x] Working/Grammar ok?? 
- [] Random NOT working. Inserts return and if statements to symbol table.
- []