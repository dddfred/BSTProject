/* ******************************************************** */
/* Programmer: Fredy Diaz Peralta                         */
/*Date: 05/20/2021                                        */
/* Purpose: To analize a txt file using a BST and output  */
/*          an analisis                                   */
/* Input: txt file chosen by the user                    */
/* Output: Print Out analisis of the txt file             */
/* ******************************************************** */

#include <algorithm>
#include <sstream>
#include <string>
#include <iomanip>
#include "BST_Project.cpp"
using namespace std;
int main()
{
    BSTree<string> T1;
    string filename;
    ifstream infile;
    int wordCount = 0;
    int totalCharacters = 0;
    ofstream outfile;
    double averageSentenceLen = 0;
    double averageWordLen = 0;
    string item;

    
    cout << "Enter file's name to open" << endl;
    cin >> filename;
    infile.open(filename.c_str());
    if (!infile.is_open())
    {
        cout << "Cannot open file! Please try again." << endl;
        return 1;
    }
    while (!infile.eof())
    {
        infile >> item;
        // Pre format word
        size_t i = 0;
        size_t len = item.length();
        while (i < len)
        {
            if (item[i] != '\'' && (!isalnum(item[i]) || item[i] == ' '))
            {
                item.erase(i, 1);
                len--;
            }
            else
                i++;
        }
        // Count characters
        for (size_t i = 0; i < item.length(); i++)
        {
            if (item[i] != '\'')
            {
                totalCharacters += 1;
            }
        }
        //
        if (item != "")
        {
            item[0] = toupper(item[0]);
            T1.insertItem(item);
            // Increase total word count
            wordCount += 1;
        }
    }

    infile.close();

    // Count number of sentences
    infile.open(filename.c_str());
    if (!infile.is_open())
    {
        cout << "Cannot open file! Please try again." << endl;
        return 1;
    }
    string sentence;
    int count = 0;
    int words = 0;
    while (getline(infile, sentence, '.'))
    {
        count++;
        istringstream stringStream(sentence);
        int cnt = 0;
        string word;
        while (stringStream >> word)
        {
            cnt++;
        }
        words += cnt;
    }
    infile.close();
    averageSentenceLen = static_cast<double>(words) / count;
    averageWordLen = static_cast<double>(totalCharacters) / wordCount;

    // Write to the report
    outfile.open("Analysis.txt");
    if (!outfile.is_open())
    {
        cout << "Cannot open file report! Please try." << endl;
        return 1;
    }
    outfile << "FILE NAME: " << filename <<  endl << endl;
    outfile << right << setw(50) << setfill(' ') << "STATISTICAL SUMMARY" << endl << endl;
    outfile << "TOTAL NUMBER OF WORDS : " << wordCount << endl;
    outfile << "TOTAL NUMBER OF \"UNIQUE\" WORDS : " << T1.uniqueWordsUsedAll() << endl;
    outfile << "TOTAL NUMBER OF \"UNIQUE\" WORDS OF MORE THAN THREE LETTERS : " << T1.uniqueWordsUsed() << endl;
    outfile << "AVERAGE WORD LENGTH : " << fixed << setprecision(2) << averageWordLen << " characters" << endl;
    outfile << "AVERAGE SENTENCE LENGTH : " << fixed << setprecision(2) << averageSentenceLen << " words" << endl;
    outfile << endl << endl;
    outfile << right << setw(50) << setfill(' ') << "STYLE WARNINGS" << endl << endl;
    outfile
            << "WORDS USED TOO OFTEN: (  WORDS OF MORE THAN 3 LETTERS THAT ARE USED MORE THAN 5% OF THE TOTAL NUMBER OF WORDS OF MORE THAN 3 LETTERS )"
            << endl << endl;
    T1.printOften(wordCount, outfile);
    if (averageSentenceLen > 10)
    {
        outfile << endl << "AVERAGE SENTENCE LENGTH TOO LONG - " << averageSentenceLen << " words";
    }
    if (averageWordLen > 5)
    {
        outfile << endl << "AVERAGE WORD LENGTH TOO LONG - " << static_cast<float>(totalCharacters) / wordCount << " characters";
    }
    outfile << endl << endl;
    outfile << right << setw(50) << setfill(' ') << "INDEX OF UNIQUE WORDS" << endl;
    for (int i = 0; i < 26; i++)
    {
        int alphabet = 'a' + i;
        char x = alphabet;
        outfile << "\n";
        T1.printInorderIndex(toupper(x), outfile);
    }
    outfile.close();
    // reads the created file and prints it out to the console
    ifstream f("Analysis.txt");

        if (f.is_open())
            std::cout << f.rdbuf();
    
    
    return 0;
}

