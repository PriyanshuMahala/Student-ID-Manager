#include <iostream>
#include <string>
#include <fstream>

class student {
public:
    std::string name;
    int NID;
    int AMarks;

    student(std::string nme, int ID, int marks) {
        this->name = nme;
        this->NID = ID;
        this->AMarks = marks;
    }
};

int main() {
    std::string tName;
    std::string choice;
    int tId{};
    int Nent = 0;
    int tMark{};

    // Reading and printing existing entries

    while (Nent < 3) {
        std::cout << "Options are: Add entry, remove entry, find entry, pass\nChoose : ";
        std::getline(std::cin, tName);

        if ()

            // Rest of the code here
            if (!tName.empty()) {
                student new_student(tName, tId, tMark);
                Nent++;
                std::ofstream file("ENTRIES.txt", std::ios::app); // Open file in append mode
                file << "ENTRY NUM : " << Nent << '\n' << tName << '\n' << tId << '\n' << tMark << std::endl;
                file.close();
            }
    }
}
