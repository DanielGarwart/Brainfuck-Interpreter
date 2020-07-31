#include <string>
#include <cstdio>
#include <memory>
#include <iostream>
#include <stdexcept>
#include <stack>
#include <fstream>
#include <sstream>
#include <limits>

constexpr size_t amoCells = 16384;

namespace Brainfuck {

typedef const std::string BF_ERROR;
typedef std::string::const_iterator nodeptr;
char cell_buffer[amoCells];
    
short index = 0;
BF_ERROR cie = "ERROR: Cell Not Available For Access!";
BF_ERROR ncl = "ERROR: ] Has No Corresponding [!";
std::stack<nodeptr> insStack;

std::string getCommandStack(const std::string& filepath) {
    std::ifstream file(filepath);
    std::stringstream ss;
    std::string line;
    if(!file.is_open()) 
        throw std::runtime_error("Couldn't Open File!");
    while(std::getline(file, line)) 
        ss << line;
    return ss.str();
}

void interpret(const std::string& instructions) {
    bool newLine = false;
    for(auto insPtr = instructions.begin(); insPtr != instructions.end(); insPtr++)
    switch(*insPtr) {
        case '>': 
            if(index == amoCells) 
                throw std::runtime_error(cie.data()); 
            else index++; 
            break;
        case '<': 
            if(index == 0) 
                throw std::runtime_error(cie.data()); 
            else index--; 
            break;
        case '+': 
            cell_buffer[index]++; 
            break;
        case '-': 
            cell_buffer[index]--; 
            break;
        case '[':
            insStack.push(insPtr);
            if (cell_buffer[index] == 0) {
				auto subPtr = insPtr;
				while (insPtr++ != instructions.end()) {
					if (*insPtr == '[')			
                        insStack.push(insPtr);
					else if (*insPtr == ']') {
						if (insStack.empty())	
                            throw std::runtime_error(ncl.data()); 
						auto tempPtr = insStack.top(); insStack.pop();
						if (subPtr == tempPtr)	
                        break;
                    }
                } // End of while
            } // End of if
            break;
        case ']': 
            if(insStack.empty()) 
                throw std::runtime_error(ncl.data());
            if(cell_buffer[index] != 0) 
                insPtr = insStack.top();
            else
                insStack.pop(); 
            break;
        case '.':
            newLine = true;
            std::printf("%c", cell_buffer[index]); 
            break;
        case ',': 
            short num;
            std::cin >> num;
            cell_buffer[index] = (char)num;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            break;
        default: 
            break;
    } // End of switch statement and for loop
    if(newLine) std::printf("\n");
}

}

void processFile(char** args) {
    std::memset(Brainfuck::cell_buffer, 0, sizeof(Brainfuck::cell_buffer));
    std::string code = Brainfuck::getCommandStack(args[1]);
    std::printf("Interpretation of Brainfuck file resulted in:\n");
    Brainfuck::interpret(code);
}

void interactiveShell() {
    std::string input = "";
    int32_t numLine = 0;

    do {
        std::printf("%d >>> ", numLine);
        std::getline(std::cin, input);
        Brainfuck::interpret(input);
        numLine++;
    } while ( input != ":q");
    std::printf("Interpreter exited !");
}

int main(int argc, char** argv)
{
    try {
        if (argc != 2) throw std::runtime_error("Amount Of Arguments Is Too Low/High!");
        if(strcmp(argv[1], "--interpret") == 0 || strcmp(argv[1], "-") == 0) 
            interactiveShell();        
        else
            processFile(argv);
    } catch(const std::exception& e) {
        std::printf("%s\n", e.what());
    }
}
