#include<huffman.h>
#include <algorithm>
#include <iomanip>
#include<string>
#include<sstream>
#include<iostream>
using namespace std;
bool sortBySecond(const HuffmanTree* a,const HuffmanTree* b)
{
    return (a->getRootData().second < b->getRootData().second);
}
int binToDec(string bin)
{
    int result = 0;
    for(int i = 0; i<bin.size(); i++)
    {
        if(bin.at(i) == '1')
        {
            if(i == (bin.size() - 1))
                result += 1;
            else
                result += (pow(2,bin.size()-1-i));

        }
    }
    return result;
}
void Huff::copy(Huff const& other)
{
    tree = other.tree;
    frequencyTable = other.frequencyTable;
    codeTable = other.codeTable;
    inputFile = other.inputFile;
    outputFile = other.outputFile;
    code = other.code;
}
Huff& Huff::operator=(Huff const& other)
{
    if(this !=& other)
    {
        copy(other);
    }
    return *this;
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
        if(frequencyTable.find(c) == frequencyTable.end())
            frequencyTable[c] = 1;
        else
            frequencyTable[c]++;
    }
    fin.close();
}

string Huff::binaryCodeHelp(const char c, const HuffmanTree& start) const
{
    if(c == start.getRootData().first)
        return "";
    if(start.empty())
        return "";
    if(start.left().isMember(c))
        return "0" + binaryCodeHelp(c, start.left());
    if(start.right().isMember(c))
        return "1" + binaryCodeHelp(c, start.right());
    return "";//ако символът не се съдържа изобщо в дървото с корен start
}

string Huff::binaryCode(const char c) const
{
    return binaryCodeHelp(c,tree);
}

void Huff::createCodeTable()
{
    if(tree.empty())
        return;

    for( pair<char,int> p : frequencyTable)
    {
        codeTable.emplace(p.first,binaryCode(p.first));
    }
}
void Huff::saveBinaryCode()
{
    ifstream fin;
    ofstream fout;
    char c;
    fin.open(inputFile, ios::in);
    fout.open(outputFile, ios::out | ios::app);
    while(true)
    {
        fin.get(c);
        //за да не чете последния символ 2 пъти
        if(fin.eof())
            break;
        for(const pair<char,string> p : codeTable)
        {
            if(p.first == c)
            {
                fout<<p.second;
                code += p.second;
            }
        }
    }
    fin.close();
    fout.close();
}
//връща като резултат възела с най-малка числена стойност като същевременно го премахва от списъка с възели, подаден като параметър
HuffmanTree*& Huff::findMinNode(list<HuffmanTree*>& nodes)
{
    nodes.sort(sortBySecond);
    return nodes.front();
}

void Huff::buildTree()
{
    //стъпка 2 от построяване на дърво на Хъфман от описанието
    //създаваме n дървета от по един възел, който съдържа наредена двойка и ги записваме в списък, като той е сортиран във низходяш
    list<HuffmanTree*> nodes;
    for(const pair<char,int> p : frequencyTable)
    {
        nodes.push_front(new HuffmanTree(p, HuffmanTree(), HuffmanTree()));
    }
    while(nodes.size() > 1)
    {
        HuffmanTree* fst = findMinNode(nodes);
        nodes.pop_front();//премахваме fst от списъка
        HuffmanTree* snd = findMinNode(nodes);
        nodes.pop_front();//премахваме snd от списъка
        HuffmanTree* res = new HuffmanTree(make_pair(' ',fst->getRootData().second + snd->getRootData().second), *fst, *snd);//строим ново дърво с поддървета 2те най-малки досега
        nodes.push_front(res);
    }
    //има само 1 възел в списъка и това е нашият корен

    tree =  *(nodes.front());
    nodes.pop_front();
}
void Huff::saveDecCode()const
{
    ofstream fout;
    fout.open(outputFile, ios::out);//да изтрива бинарната последователност, нея я имаме записана в code
    list<string> subs;

    for(int i=0; i<=code.size(); i += 8)
    {
        cout<<i<<endl;
        cout<<code.substr(i,8)<<endl;
        subs.push_back( code.substr(i,8));
    }
    fout<<"\n";
    for(const string s : subs)
    {
        int tmp = binToDec(s);
        cout<<"tmp: "<<tmp<<endl;
        cout<<tmp<<endl;
        fout<<tmp<<" ";
    }
    fout.close();
}
void Huff::calculateCompressionRate() const
{
    int counter = 0;
    ifstream fin;
    fin.open(inputFile, ios::in);
    char c;
    while(true)
    {
        fin.get(c);
        counter ++;
        //за да не чете последния символ 2 пъти
        if(fin.eof())
            break;
    }
    fin.close();
    cout<<code.size()<<":"<<counter - 1<<endl;;
}
void Huff::printTree() const
{
    tree.prettyPrint(cout,0);
}

void Huff::printFrequencyTable() const
{
    for ( const pair<char,int> p : frequencyTable )
    {
        cout << " " << p.first << ":"<< p.second;
    }
    cout <<endl;
}
void Huff::printCodeTable() const
{
    for ( const pair<char,string> p : codeTable)
    {
        cout<<" " << p.first << ":"<< p.second;
    }
    cout <<endl;
}
