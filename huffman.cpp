#include<huffman.h>
#include <algorithm>
using namespace std;
bool sortBySecond(const pair<int,int> &a,const pair<int,int> &b)
{
    return (a.second > b.second);
}
void printMap(unordered_map<char, int> m)
{
    for ( auto it = m.begin(); it != m.end(); ++it )
        cout << " " << it->first << ":" << it->second;
    cout <<endl;
}
void Huff::setInputFile(string name)
{
    inputFile = name;
}
void Huff::setOutputFile(string name)
{
    outputFile = name;
}
void Huff::createFrequencyTable()
{
    //създаване на честотна таблица
    ifstream fin;
    char c;
    fin.open(inputFile, ios::in);
    while(true)
    {
        fin.get(c);
        //за да не чете последния символ 2 пъти
        if(fin.eof())
            break;
        if(table.find(c) == table.end())
            table[c] = 1;
        else
            table[c]++;
    }
}
void Huff::buildTree()
{
    vector<pair<char,int>> v;
    for(const pair<char,int> p : table)
        v.push_back(p);
    //сортираме вектора по втори елемент на двойката
    sort(v.begin(), v.end(), sortBySecond);
    /* for (const auto& p : v)
     {
         cout << p.first << ", " << p.second << endl;
     }*/

}
void Huff::printTree(ostream& out = cout, int currentHeight = 0) const
{
    tree.prettyPrint(out,currentHeight);

}
void Huff::printTable() const
{
    printMap(table);
}

int main()
{
    Huff h;
    h.setInputFile("input.txt");
    h.createFrequencyTable();
    h.printTable();
    cout<<"kotka";
    return 0;
}
