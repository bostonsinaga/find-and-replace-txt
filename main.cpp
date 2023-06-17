#include <iostream>
#include <fstream>
#include <vector>
#include "utility.h"

int main(int argc, char *argv[]) {

    int inputStrCt = argc - 1;
    std::string text;
    std::string inputStrArr[inputStrCt];

    for (int i = 1; i < argc; i++) {
        inputStrArr[i-1] = argv[i];
    }

    if (inputStrCt >= 4 && inputStrArr[0] == "--in") {
        text = utility::readFile(inputStrArr[1]);
        if (text == "") {
            return 0;
        }
    }
    
    // show help menu
    if (inputStrCt == 1 &&
        (inputStrArr[0] == "--help" || inputStrArr[0] == "-h")
    ) {
        utility::printHelp();
    }
    // find and replace string to specified file
    else if (
        inputStrCt == 8 &&
        inputStrArr[0] == "--in" &&
        inputStrArr[2] == "--find" &&
        inputStrArr[4] == "--replace" &&
        inputStrArr[6] == "--out"
    ) {
        utility::replaceText(text, inputStrArr[3], inputStrArr[5], inputStrArr[7]);
    }
    // find and replace string to present file
    else if (
        inputStrCt == 6 &&
        inputStrArr[0] == "--in" &&
        inputStrArr[2] == "--find" &&
        inputStrArr[4] == "--replace"
    ) {
        utility::replaceText(text, inputStrArr[3], inputStrArr[5], inputStrArr[1]);
    }
    // find string for counting
    else if (
        inputStrCt == 4 &&
        inputStrArr[0] == "--in" &&
        inputStrArr[2] == "--find"
    ) {
        utility::countFoundText(utility::findText(text, inputStrArr[3]));
    }
    // show help menu
    else if (inputStrCt == 0) {
        utility::printHelp();
    }
    // command does not match
    else {
        std::cerr << "Error command. Type '--help'\n";
    }

    return 0;
}