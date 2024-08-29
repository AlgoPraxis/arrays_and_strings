#include <iostream> 
#include <fstream> 
#include <iomanip> 
#include <string>
#include <map>
#include <cmath>

int main (int argc, char** argv)
{
  std::map<char, int> alphabetMap;
  std::map<int, std::string> hashTable; 
  std::string text;
  std::string pattern;
  std::string temp;

  // Getting the text and the pattern from the user or a file
  // depending on the -i flag
  if (argc > 1 && std::string(argv[1]) == "-i") {
    // Get user input
    std::cout << "enter a text (all lower case): ";
    std::getline(std::cin, text);
    std::cout << "enter a pattern to be found in the text (all lower case): ";
    std::getline(std::cin, pattern);
  } else {
    // Read from file
    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
      std::cerr << "Error opening file. Make sure 'input.txt' exists in the same directory." << std::endl;
      return 1;
    }
    std::getline(inputFile, text);
    std::getline(inputFile, pattern);
    inputFile.close();
  }
  std::cout << "text = " << text << std::endl;
  std::cout << "pattern = " << pattern << std::endl;

  // Populate the map with lower case alphabet and corresponding integer codes
  for (char ch = 'a'; ch <= 'z'; ch++) {
    alphabetMap[ch] = ch - 'a' + 1;
  }
  alphabetMap[' '] = 0;

  // Print the map to verify its content
  for (const auto& pair : alphabetMap) {
      std::cout << "Character: " << pair.first << ", Code: " << pair.second << std::endl;
  }

  //Calculating the first window's hash, and assigning it to the hash table along with its string value
  //The base for the hash calc here is 10
  int hash = 0;
  for (int h = 0; h < pattern.length(); h++){
    hash += alphabetMap[text[h]] * std::pow(10, pattern.length() - 1 - h);
  }
  for (int m = 0; m < pattern.length(); m++) {
    temp += text[m]; 
  }
  std::cout << std::left << std::setw(7) << "hash = " << std::setw(10) << hash << "in window = " << temp << std::endl;
  hashTable[hash] = temp; 

  for (int i = 1;  i <= text.length() - pattern.length(); i++) {
    std::string subTemp;
    hash = (hash - alphabetMap[text[i-1]] * std::pow(10, pattern.length() - 1)) * 10 + alphabetMap[text[i + pattern.length() - 1]];
    for (int m = 0; m < pattern.length(); m++) {
      subTemp += text[i+m]; 
    }
    std::cout << std::left << std::setw(7) << "hash = " << std::setw(10) << hash << "in window = " << subTemp << std::endl;
    hashTable[hash] = subTemp; 
  }
  //finding the hash of the pattern and see if it exists in the hash table
  int hashPattern = 0;
  for (int h = 0; h < pattern.length(); h++){
    hashPattern += alphabetMap[pattern[h]] * std::pow(10, pattern.length() - 1 - h);
  }
  std::cout << "hashPattern = " << hashPattern << std::endl;

  if (hashTable[hashPattern] == pattern)
    std::cout << " SUCCESS " << std::endl;
  else
    std::cout << " Pattern not found in the text! " << std::endl;


  return 0;
}
