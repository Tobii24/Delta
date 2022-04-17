# Delta

## Syntax
### Features & Limitations
* *Dynamic*
* *Compiled*
* *Pointer Oriented Programming (POP) ─ Not to be confused with c/c++ pointers*
* *The language won't throw runtime errors, unless they break filters and/or creates a pernicious context*

### Pointers
> Everything in the language is a pointer, except for references
* `*<name>` - Returns the pointer's value
* `&<name>` - Returns the pointer's address
* `#<name>` - Returns the pointer's type
* `$<name>` - Returns the pointer's object

### Instructions
#### Arithmetic
* `add <variable:address> <expression>` - Sets the variable to it's value plus the expression
* `sub <variable:address> <expression>` - Sets the variable to it's value minus the expression
* `mul <variable:address> <expression>` - Sets the variable to it's value times the expression
* `div <variable:address> <expression>` - Sets the variable to it's value divided by the expression
* `mod <variable:address> <expression>` - Sets the variable to it's value to the modulus relative to the expression
* `pow <variable:address> <expression>` - Sets the variable to it's value powered by the expression
#### Misc
* `tbool <variable:address>` - Convert the variable to a boolean form
* `tnot <variable:address>` - Negates the variable
#### Array
* `set <array:address> <index> <expression>` - Sets the index value of the array to the expression given
* `get <array:address> <index>` - Gather the array index value
* `del <array:address> <index>` - Sets the index value of the array to 'undefined'

### Operations

#### Arithmetic
* `<expression> + <expression>` - Addition
* `<expression> - <expression>` - Subtraction
* `<expression> * <expression>` - Multiplication
* `<expression> / <expression>` - Division
* `<expression> % <expression>` - Modulus
* `<expression> ^ <expression>` - Exponentiation

#### Comparison
* `<expression> == <expression>` - Addition
* `<expression> != <expression>` - Subtraction
* `<expression> > <expression>` - Multiplication
* `<expression> < <expression>` - Division
* `<expression> >= <expression>` - Modulus
* `<expression> <= <expression>` - Exponentiation

#### Bitwise
* `<expression> xor <expression>` - Exclusive Or
* `<expression> band <expression>` - Bitwise And
* `<expression> bor <expression>` - Bitwise Or
* `<expression> lshift <expression>` - Left Shift
* `<expression> rshift <expression>` - Right Shift
* `bnot <expression>` - Bitwise Not

### Special Keywords
* `todef` - Variable value that means it will be defined later in the program
* `void` - Empty Value
* `null` - Null value
* `rterr` - Runtime error representation 
* `rtv`- Return Value
* `return <expression>` - Sets the keyword `rtv` to the value defined
* `break` - Stops a loop
* `continue` - Force a loop to it's next iteration

### Input & Output
* `in <expression>` - Gather user input
* `out <expression>` - Logs a value to the console

### File Manipulation
* `openf <path> <variable:address>` - Sets the variable to a file pointer
* `readf <file> <variable:address>` - Reads file content (string)
* `writef <file> <expression>` - Writes to the file (string)
* `readbf <file> <variable:address>` - Reads file content (binary)
* `writebf <file> <expression>` - Writes to the file (binary)
* `closef <file>` - Closes the file

### Conditions
* `if <condition> -> <reference:address>` - Base for condition
* `elseif <condition> -> <reference:address>` - Optional else if cases
* `else -> <reference:address>` - Optional else case

### References
> Reference function name ***'main'*** is protected
## Definition
* `ref <address> (args?) { <body> }`
## Access
* `while <condition> -> <reference:address>`
* `do -> <reference:address> while <condition>`
* `for <indexStart> <indexEnd> <step=1> -> <reference:address>`
* `iteration <array:address> -> <reference:address>`
* `call <reference:address>`

### Custom Pointers
* `type <name> { <body> }`
* `type <name> -> <todef>`

### Variables
#### Mutable
* `mutable <name> -> <expression>`
* `mutable <name> -> <todef>`
#### Fixed
* `fixed <name> -> <expression>`
* `fixed <name> -> <todef>`

### Datatypes
* `int` - Whole Number
* `float` - Rational Number
* `string` - String
* `char` - Character
* `array` - Arrays
* `dict` - Dictionaries
* `bool` - Boolean
* `bin` - Binary Data
* `<type>` - Custom Type
