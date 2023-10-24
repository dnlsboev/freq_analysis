#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <ctime>

using namespace std; 

int main()
{
    map<char, int> frequencies; 

    // init
    for(int c {97}; c < 123; c++)
        frequencies[(char) c] = 0;

    clock_t time = clock();
    
    string file_name = "Asimov Profession ENG.txt";

    ifstream input_file(file_name);
    if(input_file.is_open())
    {
        string line;

        while(getline(input_file, line))
            for (char c : line)
                if (isalpha(c))
                    frequencies[(char) tolower(c)]++;
    }
    input_file.close();

    float full_time = (float) (clock() - time) / CLOCKS_PER_SEC;


    cout << "File name: " << file_name << endl;
    cout << "Time: " << full_time << " sec." << endl;

    // out
    for (const auto& [character, freq] : frequencies)
        cout << character << ": " << freq << endl;
}
