#include <iostream>
#include <string>
#include <sstream>

/*
Caesarean cipher; support for:
-Upper and lowercase characters
-Looping to the beginning of the alphabet
-Does nothing to symbols and special characters
-Entering bad input (decode/encode, integer shift)
*/

std::string alph = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz";

// Encode method
std::string encode(std::string &msg, int shift) {
  std::string encoding = "";
  for (char a: msg) {
    std::size_t start = alph.find(a);
    if (start == std::string::npos) {
      encoding += a;
    }
    else {
      encoding += alph.at((start+shift*2)%52);
    }
  }
  return encoding;
}

//Decode method
std::string decode(std::string &msg, int shift) {
  std::string decoding = "";
  for (char a: msg) {
    std::size_t start = alph.find(a);
    if (start == std::string::npos) {
      decoding += a;
    }
    else {
      decoding += alph.at((52+start-shift*2)%52);
    }
  }
  return decoding;
}

int main() {
  std::string action = "";
  std::string msg = "";
  std::string yn = "";
  int shift;
  bool valid = false;

  while (action == "" || !(action == "encode" || action == "decode")) {
    std::cout << "Would you like encode or decode?" << std::endl;
    getline(std::cin, action);
    if (action != "encode" && action != "decode") {
      std::cout << "Bad input! Please enter either 'encode' or 'decode.' "<<std::endl;
    }
  }

  if (action == "encode") {
    std::cout << "Enter the message you would like to encode: "<< std::endl;
    getline(std::cin, msg);
    while (!valid) {
      valid = true;
      std::cout << "Enter as a number the shift you would like to apply to the message: "<< std::endl;
      std::cin >> shift;
      if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore();
        std::cout << "Bad input! Please enter an integer value and try again." << std::endl;
        valid = false;
      }
    }
    std::cout << "Your message '" << msg << "' with a Caesarean shift of " << shift <<
    " is:\n" << encode(msg, shift) << std::endl;
  }

  else {
    std::cout << "Enter the message you would like to decode: " << std::endl;
    getline(std::cin, msg);
    while (!valid) {
      valid = true;
      std::cout << "Enter the key shift as an integer. If you don't know, enter 0" << std::endl;
      std::cin >> shift;
      if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore();
        std::cout << "Bad input! Please enter an integer value and try again." << std::endl;
        valid = false;
      }
    }
    if (shift != 0) {
      std::cout << "Your decoded message is:\n" << decode(msg, shift) << std::endl;
    }
    else {
      std::cout << "Listed below are all possible decodings with appropriate shifts: " << std::endl;
      for (int i = 1; i < 26; i++) {
        std::cout << "Shift of " << i << ": " << decode(msg, i) << std::endl;
      }
    }
  }
  return 0;
}