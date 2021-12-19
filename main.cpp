#include <iostream>
#include <thread>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <random>

// Input file path
std::string input;

// Output file path
std::string output;

// Alphabet file path
std::string alphabet_file;

//Dictionary for storing the alphabet
std::map<char, unsigned long> alphabet;

//The string into which the text is read from the input
std::string text;

// String array for encoded text
std::string *encoded_text;

// Auxiliary array for generating the alphabet
short busy_digits[90] = {0};

/// <summary>
/// Function that displays an error message and exits the program
/// </summary>
void exception() {
    std::cout << "Incorrect command line.\nPlease write: "
                 "<input_file_name> <output_file_name> <alphabet_file_name>\n"
                 "Example: 'tests/test1/input.txt tests/test1/output.txt tests/test1/alphabet.txt'";
    exit(0);
}

/// <summary>
/// A function for writing the alphabet to a file (which is needed to check the correctness of the program)
/// </summary>
void alphabetFileFill() {
    std::ofstream out;
    out.open(alphabet_file);
    out << "Alphabet:\n";
    out << "----------\n";
    for (auto &item: alphabet) {
        out << "| " << item.first << " ~ " << item.second << " |"
            << "\n----------\n";
    }
    out.close();
}

/// <summary>
/// A function that assigns a number from 10 to 99 to each character
/// </summary>
void alphabetGeneration() {
    std::random_device rd;
    std::mt19937 mersenne(rd());
    for (size_t i = 0; i < 26; i++) {
        unsigned long random_number = mersenne() % 90;
        if (busy_digits[random_number] == 0) {
            alphabet[(char) (i + 97)] = random_number + 10;
            busy_digits[random_number] = 1;
        } else
            i--;
    }
    alphabetFileFill();
}

/// <summary>
/// Function to read from a file
/// </summary>
void inputRead() {
    std::ifstream in;
    in.open(input);
    if (!in.is_open()) {
        std::cout << "Error with file opening. Try again with new file path.!\n";
    } else {
        char char_to_read;
        text = "";
        while (in >> std::noskipws >> char_to_read) {
            text += tolower(char_to_read, std::locale());
        }
    }
    std::cout << "Input text:" << std::endl;
    std::cout << text << std::endl;
    in.close();
}

/// <summary>
/// Encoding function that uses multiple threads
/// </summary>
void encode() {
    std::vector<std::thread> threads(text.size());
    for (int i = 0; i < text.size(); ++i) {
        threads[i] = std::thread([=] {
            char letter;
            std::_Rb_tree_iterator<std::pair<const char, unsigned long>> it;
            letter = text[i];
            it = alphabet.find(letter);

            if (it == alphabet.end())
                encoded_text[i] = (char) (letter);
            else
                encoded_text[i] = std::to_string(it->second);
        });
    }
    for (int i = 0; i < text.size(); ++i) {
        threads[i].join();
    }
}

/// <summary>
/// А function that encodes text and writes it to a file
/// </summary>
void writeEncodedVersion() {
    encoded_text = new std::string[text.size()];
    encode();
    std::ofstream out;
    out.open(output);
    std::cout << std::endl;
    std::cout << "Encoded text:" << std::endl;
    for (int i = 0; i < text.size(); ++i) {
        out << encoded_text[i];
        std::cout << encoded_text[i];
    }
    out.close();
    delete[] encoded_text;
}

/// <summary>
/// A function in which command line arguments are assigned to variables
/// </summary>
/// <param name="argc"> - number of input arguments</param>
/// <param name="argv"> - array of input arguments</param>
void argsInput(const int &argc, char *argv[]) {

    if (argc != 4) {
        exception();
    }
    input = argv[1];
    output = argv[2];
    alphabet_file = argv[3];
}

int main(int argc, char *argv[]) {
    argsInput(argc, argv);
    alphabetGeneration();
    inputRead();
    writeEncodedVersion();
    std::cout << std::endl;
    std::cout << "Done!";
    return 0;
}