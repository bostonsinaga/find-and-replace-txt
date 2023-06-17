namespace utility {

std::string readFile(std::string &fileDirIn) {

    std::ifstream fileIn(fileDirIn);
    std::string text = "", stringBuffer;

    while (std::getline(fileIn, stringBuffer)) {
        text += stringBuffer + "\n";
    }

    if (text == "") {
        std::cerr << "File is empty\n";
    }

    fileIn.close();
    return text;
}

std::vector<std::vector<int>> findText(
    std::string &text,
    std::string &findString
) {
    std::vector<std::vector<int>> foundBeginEndDex;

    for (int i = 0; i < text.size(); i++) {
        for (int j = 0; j < findString.size(); j++) {

            if (text.size() > i + j &&
                text.at(i + j) == findString.at(j)
            ) {
                if (j == findString.size() - 1) {
                    foundBeginEndDex.push_back({i, i+j});
                }
            }
            else break;
        }
    }

    return foundBeginEndDex;
}

void countFoundText(std::vector<std::vector<int>> foundBeginEndDex) {
    int size = foundBeginEndDex.size();

    if (size > 0) {
        std::cout << "Total found:  " << foundBeginEndDex.size() << std::endl;
    }
    else {
        std::cerr << "No word or phrase are found\n";
    }
}

void replaceText(
    std::string &text,
    std::string &findString,
    std::string &replaceString,
    std::string &fileDirOut
) {
    std::vector<std::vector<int>> foundBeginEndDex = findText(text, findString);
    countFoundText(foundBeginEndDex);

    if (foundBeginEndDex.size() == 0) {
        return;
    }

    for (auto &indexes : foundBeginEndDex) {
        std::string
            beginCutStr = text.substr(0, indexes.front()),
            endCutStr = text.substr(indexes.back() + 1);

        text = beginCutStr + replaceString + endCutStr;
    }

    // write file
    std::ofstream fileOut(fileDirOut);
    fileOut << text;
    fileOut.close();

    std::cout << "Replace and write to '" << fileDirOut << "' succeeded\n";
}

void printHelp() {
    std::cout
        << "---------------------------\n"
        << "find-and-replace-txt v1.0.0\n"
        << "by github.com/bostonsinaga\n"
        << "---------------------------\n\n"
        << "Help:\n"
        << "(consider the position)\n\n"
        << "--help / -h\n"
        << ">>>> show help menu\n"
        << "--in [FILE_IN] --find [STRING] --replace [STRING] --out [FILE_OUT]\n"
        << ">>>> find and replace string to specified file\n"
        << "--in [FILE_IN] --find [STRING] --replace [STRING]\n"
        << ">>>> find and replace string to present file\n"
        << "--in [FILE_IN] --find [STRING]\n"
        << ">>>> find string for counting\n";
}

}