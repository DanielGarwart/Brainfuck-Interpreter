## Simple Brainfuck Interpreter
**General:**  
	The Runtime Accounts For 2^14 Cells Currently.  
	The Following Exceptions Can Be Thrown:  
		

 - Cell Index Error: `$ ERROR: Cell Not Available For Access!`
 - No Corresponding Loop Sign: `$ ERROR: ] Has No Corresponding [!` 

**Compilation:**  
	GCC/Clang:
		
    $ g++/clang++ main.cpp -o "brainfuck" -std=c++17

## How To Use It
**For Files:**
    In the command line, type:
    `$ brainfuck "[filename.bf]"`
    **Interactive Shell**
        `$ brainfuck -i/--interpret`


