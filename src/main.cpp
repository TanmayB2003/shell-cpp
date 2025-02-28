#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_set>

int main() {
  // Flush after every std::cout / std:cerr
  std::unordered_set<std::string> builtin({"type", "exit", "echo"});
  while(1) {
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    // Uncomment this block to pass the first stage
    std::cout << "$ ";

    std::string input;
    std::getline(std::cin, input);
   
    if(input.substr(0, 4) == "exit") return std::stoi(input.substr(5));

    if(input.substr(0, 4) == "echo") {
      std::cout << input.substr(5) << std::endl; 
      continue;
    }

    if(input.substr(0, 4) == "type") {
      std::string s = input.substr(5);
      if(builtin.find(s)!=builtin.end()) 
        std::cout << s << " is a shell builtin" << std::endl;
      else 
        std::cout << s << ": not found" << std::endl;
      continue;
    }

    std::cout << input << ": command not found" << std::endl;   
  }
}