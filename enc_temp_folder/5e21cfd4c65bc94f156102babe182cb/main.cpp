#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

struct students
{
    std::string name;
    int ID = 0;
    float Marks = 0;
};

void options() {
    std::cout << "Options are: Add Entry, Remove Entry, Find Entry,Print Entries, Exit\n";
}

template<typename T>
T getInput(const std::string& prompt) {
    T value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            // Input successful
            break;
        }
        else {
            // Clear error flag and discard invalid input
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please try again." << std::endl;
        }
    }
    // Clear input buffer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}

void CreateEntry(const std::string& FileName, int num, const students& TMP) {
    std::ofstream file(FileName, std::ios::app); // Open in append mode
    file << "ENTRY : " << num << '\n' << "[NAME]: " << TMP.name << '\n'
        << "[ID] : " << TMP.ID << '\n' << "[MARKS] : " << TMP.Marks << '\n';
    file.close();
}

void RemoveEntry(const std::string& FileName, int num) {
    std::ifstream inFile(FileName);
    std::ofstream outFile("temp.txt");

    std::string line;
    int entryCount = 0;

    while (std::getline(inFile, line)) {
        if (line.find("ENTRY : ") != std::string::npos) {
            int entryNumber = std::stoi(line.substr(8));
            if (entryNumber != num) {
                outFile << line << '\n';
                entryCount++;
            }
        }
        else {
            outFile << line << '\n';
        }
    }

    inFile.close();
    outFile.close();

    // Remove original file and rename temp file
    std::remove(FileName.c_str());
    std::rename("temp.txt", FileName.c_str());

    if (entryCount == 0)
        std::cout << "No such entry found.\n";
    else
        std::cout << "Entry " << num << " removed successfully.\n";
}

void findEntry(const std::string& FileName, const std::string& name) {
    std::ifstream inFile(FileName);
    std::string line;
    bool found = false;

    while (std::getline(inFile, line)) {
        if (line.find("[NAME]: " + name) != std::string::npos) {
            // Found the entry
            found = true;
            std::cout << "Entry found:\n" << line << '\n';
            // Print additional information if needed
            for (int i = 0; i < 3; ++i) {
                std::getline(inFile, line);
                std::cout << line << '\n';
            }
            break;
        }
    }

    if (!found)
        std::cout << "Entry with name \"" << name << "\" not found.\n";

    inFile.close();
}

void print(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        std::cout << "Unable to open file " << filename << std::endl;
        return;
    }

    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }

    file.close();
}



int main() {
    const std::string fName = "ENTRIES.txt";
    int EnNum = 0;
    students temp;
    std::string Tchoice;
    while (true) {
        options();
        std::cout << "Choose : ";
        std::getline(std::cin, Tchoice);
        if (Tchoice == "Add Entry") {
            std::cout << "Enter student name : ";
            std::getline(std::cin, temp.name);
            temp.ID = getInput<int>("Enter ID : ");
            temp.Marks = getInput<float>("Enter average marks : ");
            EnNum++;
            CreateEntry(fName, EnNum, temp); // Using float for Marks
        }
        else if (Tchoice == "Remove Entry") {
            int entryNum = getInput<int>("Enter entry number to remove: ");
            RemoveEntry(fName, entryNum);
        }
        else if (Tchoice == "Find Entry") {
            std::string name = getInput<std::string>("Enter student name : ");
            findEntry(fName, name);
        }
        else if (Tchoice == "Print Entries") {
            print(fName);
        }
        else if (Tchoice == "Exit" || Tchoice == "cls") {
            std::cout << "Exiting........\n";
            return 0;
        }
        else {
            std::cout << "Invalid\n";
        }
    }
    return 0;
}
