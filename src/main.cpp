#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <filesystem>

namespace fs = std::filesystem;

std::string get_path(std::string &command) {
  const std::string path_env = std::getenv("PATH");
  std::stringstream ss(path_env);
  std::string path;
  while(getline(ss,path,':')) {
    std::string abs_path = path + '/' + command;
    if(fs::exists(abs_path)) {
      return abs_path;
    }
  }
  return "";
}

int main() {
  // Flush after every std::cout / std:cerr
  std::unordered_set<std::string> builtin({"type", "exit", "echo", "pwd"});
  
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
      std::string exec = get_path(s);

      if(builtin.find(s)!=builtin.end()) 
        std::cout << s << " is a shell builtin" << std::endl;
      else if(exec!="") 
        std::cout << s << " is " << exec << std::endl;
      else 
        std::cout << s << ": not found" << std::endl;
      continue;
    }
    std::stringstream ss(input);
    std::string s;
    ss >> s;
    if(get_path(s)!="") {
      system(input.c_str());
      continue;
    }

    if(input == "pwd") {
      std::cout << fs::current_path() << std::endl;
      continue;
    }

    std::cout << input << ": command not found" << std::endl;   
  }
}