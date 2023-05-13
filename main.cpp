#include <iostream>
#include "Caff.h"

void printUsage() {
    std::cout << "usage:" << std::endl;
    std::cout << "\t./parser -caff [path-to-caff].caff" << std::endl;
    std::cout << "\t./parser -ciff [path-to-ciff].ciff" << std::endl;
}

bool checkOption(const std::string &optionName) {
    if (optionName != "-caff" && optionName != "-ciff") {
        printUsage();
        return false;
    }
    return true;
}

bool checkFileName(const std::string &optionName, const std::string &fileName) {
    auto selectedFileType = optionName.substr(1);

    auto dotPosition = fileName.find_last_of('.');
    auto fileExtension = fileName.substr(dotPosition + 1);

    if (selectedFileType != fileExtension) {
        std::cout << "The selected file type '" << fileExtension << "' is not valid for the selected option '"
                  << optionName << "'." << std::endl;
        printUsage();
        return false;
    }
    return true;
}

int main(int argc, char *argv[]) {
    auto argumentCount = argc - 1;
    if (argumentCount != 2) {
        printUsage();
        return -1;
    }

    std::string optionName = argv[1];
    std::string fileName = argv[2];

    if (!checkOption(optionName) || !checkFileName(optionName, fileName)) {
        return -1;
    }

    try {
        Caff caff(fileName);
        caff.convert();
    } catch (const std::exception &exception) {
        std::cout << exception.what() << std::endl;
        return -1;
    }

    return 0;
}
