#ifndef CHUNK_H
#define CHUNK_H
//////////////////////////////////////////////////
#include <fstream>
#include <cmath>
#include <string>
#include <bitset>

class Abstract
{
public:
    Abstract() {};
    virtual void cypher() = 0; // Pure virtual function
};

class Quantum : public Abstract
{
private: // Member variables are private as I don't plan for this class to be inherited.
    char comma = ',';
    char space = ' ';
    std::string pair; // Made as a member variable instead of a local function variable.
    int target, current, modulo;
public:

    Quantum(int mod) : modulo(mod)
    {
        srand(time(nullptr)); // This creates our seed when creating an object.  Not the best method, but for our purposes it works.
    };

    void createRandom()
    {
        target = (rand() % modulo + 1); //From cplusplus, the right handside notation of the modulo dictates that we have a range of 1 - modulo. Allowing for 128 or 64 modulo.
    }

    void createPair()
    {
        pair = ""; // Resets pair and current each time the pair is called. Used to avoid appending a long string since it is shared between functions.
        current = 1;
        std::string line;
        std::ifstream read("flip.txt");
        if (read.is_open()) // Just ensures that the file is open.
        {
            while (std::getline(read, line)) // Read helps extract the binary sequence from the line and store it into line. Does so until it finds a delimination character like \n. Putting it into a while loop allows it to continue until it reaches the end of the file
            {
                if(current == target) // Random Num Gen with a range of 1 - 128 will create the target line
                {
                    //std::cout << "Target Value: " << target << std::endl;
                    for (int i = 0; i < line.length(); i++) // A line's length is 3 in flip.txt. Two bits a 0 or a 1, and a comma character.
                    {
                        if (line[i] == comma) {continue;} // Condition given to skip the comma in this specific line.
                        pair += line[i]; // By skipping the comma, we can take this string and replace the bit in binSeq.txt
                    }
                }
                current++; // A very slow and obviously not optimal way to get this value as you could imagine if we had thousands of lines.
            }
            read.close();
        }
        else {std::cout << "Can't open file" << std::endl;} // Data validation.
    }

    void editFile()
    {
        std::string line;
        std::ifstream read("binSeq.txt"); // Reading the given file, and writing it to separate file.
        std::ofstream write("temp.txt");
        if (read.is_open() && write.is_open()) // Checks if both files are open
        {
            while (std::getline(read, line))
            {
                for(int i = 0; i < line.length(); i++) // Reason for .length() is because binSeq.txt has a shorter length and this is accounting for that. | Can I do i += 2
                {
                    if(line[i] == space) {continue;} // Just like the comma, the space is skipped inbetween each sequence.
                    createRandom(); // Generates the target number to call a certain pair line in flip.txt
                    createPair(); // Uses the random number to call a respective line and create the pair string which can be "01" or "10"
                    line.replace(i,1, pair); // At each bit, a random number is called, creates a pair for each bit and replaces that bit.
                    i++; // Incrementing on top of the for loop condition because our string length is increasing by 1 character since we are replacing one character with 2. Prevents from skipping a bit.
                }
                for(int i = 8; i < line.length(); i+=9) // We start at the index of 8 of each line because we want bitset to have 8-bit sequences. Since we doubled it the sequences are currently 16. Incrementing by 9 because the space inserted has to be acocunted for.
                {
                    if(line[i] == space) {continue;} //This skips the spaces already between the 16 bit sequences.
                    line.insert(i, " "); // Since we are incrementing by 9 and adding a space it still lines up, but this helps break up the 16-bit sequences into 8-bits.
                }
                write << line << std::endl; // Write the replaced and spaced out line to temp.txt
            }
            read.close();
            write.close();
            std::remove("binSeq.txt"); // Once closed, we delete our the binSeq.txt
            std::rename("temp.txt", "binSeq.txt"); // Rename the temp as our bitSeq.txt
            std::ofstream write("temp.txt"); // Create temp.txt again for next object/call
        }
        else {std::cout << "Can't open file" << std::endl;}
    }

    void cypher() // Defining this pure virtual function allows this class to not be abstract.
    {
        copy(); // Creates a copy of binSeq.txt before it is edited
        editFile(); // Replaces the bits and inserts the spaces
        std::string line, line2;
        std::ifstream read("binSeq.txt");
        if(read.is_open())
        {
            while(std::getline(read,line))
            {
                line2 = ""; // Like pair, this resets the
                for(int i = 0; i < line.length(); i++)
                {
                    if(line[i] == space) {continue;}  // Here im skipping the spaces I just created. Bitset doesn't really work with spaces;
                    line2+=line[i]; //Basically the respective file line without any spaces between the sequences.
                }
                for(int i = 0; i < line2.length(); i += 8) //similar to the spacing, since we have no spacing in this line, we increment by 8 as we bitset to have 8-bit sequences.
                {
                    std::string sequence = line2.substr(i,8); //At whatever position, 0, 8, 16.... it creates a subset of the string line2 called sequence to represent each individual 8-bit sequence that are 0-8, 8-16, 16-24, etc...
                    unsigned long int character = std::bitset<8>(sequence).to_ulong(); // A bitset of 8, passing the subset string sequence and converting it as a unsigned long int hence why character is the same type.
                    std::cout << character << "."; // Formating that was required
                }
                std::cout << std::endl; // Follows how the lines are formatted in the binSeq.txt file
            }
            read.close();
        }
        else {std::cout << "Can't open file" << std::endl;}
        replace(); // Once we have the cypher, we delete the binSeq.txt file that was edited and rename the unedited backup file called backup.txt and rename it as binSeq.txt so that it's ready for the next object call
    }

    void copy() // See line 94
    {
        std::string line;
        std::ifstream read("binSeq.txt");
        std::ofstream write("backup.txt");
        if (read.is_open() && write.is_open())
        {
            while (std::getline(read, line))
            {
                write << line << std::endl;
            }
            read.close();
            write.close();
        }
        else {std::cout << "Can't open file" << std::endl;}
    }

    void replace() // See line 120
    {
        std::remove("binSeq.txt");
        std::rename("backup.txt", "binSeq.txt");
        std::ofstream write("backup.txt");
    }
};
//////////////////////////////////////////////////
#endif //CHUNK_H


// https://gist.github.com/vgrllc/3976dac7bb243bdfbfef3b019345ad64