#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <ctime>
#include <vector>

#ifdef _OPENMP
#include <omp.h>
#endif


using namespace std; 


int main()
{
    #ifdef _OPENMP
    cout << "Caution: This program was compiled with " 
            "OpenMP and can consume all CPU resourses "
            "of your PC!" << endl;
    #endif
     
    vector<string> lines;
   

    // openning file and getting lines in the vector
    string filename = "Bible50.txt";
    ifstream input_file;
    input_file.open(filename);
    if(input_file.is_open()){
        string line;
        while (getline(input_file, line))
            lines.push_back(line);
    }

    input_file.close();


    int num_of_lines = lines.size();

    int num_threads;
    cout << "Enter num of threads" << endl;
    cin >> num_threads;
    omp_set_num_threads(num_threads);

    cout << "THIS PROGRAM USE " << num_threads << " THREADS" << endl;

    // initialization of frequencies
    unsigned long int frequencies[26];
    
    for(int i = 0; i < 26; i++)
        frequencies[i] = 0;


    double exec_time;
    #ifdef _OPENMP
        double itime = omp_get_wtime();
    #else 
        clock_t itime = clock();
    #endif
 

    #pragma omp parallel for reduction(+: frequencies)
    for (int i = 0; i < num_of_lines; i++){     
        for (int j =0; j < size(lines[i]); j++){
            if (isalpha(lines[i][j]))
                frequencies[(int) tolower(lines[i][j]) - 97] += 1;
        }
    }
        

    #ifdef _OPENMP
        double ftime = omp_get_wtime();
        exec_time = ftime - itime;
    #else 
        clock_t ftime = clock();
        exec_time = (double) (ftime - itime) / CLOCKS_PER_SEC;
    #endif  


    cout << "File name: " << filename << endl;
    cout << "Num of lines = " << num_of_lines << endl;
    cout << "Time: " << exec_time << " sec." << endl;


    string answer;
    cout << "Show freq of symbols (y/n)? " << endl;
    cin >> answer;
    if (answer == "y" or answer == "Y"){                
        for (int i = 0; i < 26; i ++)
            cout << (char)(i+97) << ": " << frequencies[i] << endl;
    }

    return 0;
}
