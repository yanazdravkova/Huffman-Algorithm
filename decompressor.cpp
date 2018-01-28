#include <decompressor.h>
#include<string>
#include<iostream>
using namespace std;

Decompressor& Decompressor::operator=(Decompressor const& other)
{
    tree = other.tree;
    inputFile = other.inputFile;
    outputFile = other.outputFile;
}
string Decompressor::getInputFile()const
{
    return inputFile;
}
string Decompressor::getOutputFile() const
{
    return outputFile;
}

void Decompressor::setInputFile(string name)
{
    inputFile = name;
}
void Decompressor::setOutputFile(string name)
{
    outputFile = name;
}
void Decompressor::enterTree()
{
    tree.enter(cin);
}
string Decompressor::readCode() const
{
    string code;
    ifstream fin;
    fin.open(getInputFile(), ios::in);
    char c;
    //изчитаме двоичната последователнот от входния файл
    while(true)
    {
        fin.get(c);
        if(fin.eof())
            break;
        code += c;
    }
    fin.close();
    return code;
}
void Decompressor::decompress(string& code,HuffmanTree::Position curr, string& result)
{

    if(tree.empty())
        return;
    else
    {
        //cout<<"code "<<code<<endl;
        //cout<<"code size "<<code.size()<<endl;
        if(curr.isLeaf())
        {
            //cout<<"cur first"<<(*curr).first<<"\n\n";
            result += (*curr).first;
            if(!code.empty())
            {
                decompress(code,tree.getRoot(),result);
            }


        }
        else
        {
            if(code[0] == '0')
            {
                //cout<<"init"<<code[0]<<endl;
                string tmp = code.substr(1);

                decompress(tmp,curr.left(),result);
            }
            else
            {
                //cout<<"init"<<code[0]<<endl;
                if(code.size()==1)
                {
                    string s;
                    decompress(s,curr.right(),result);
                }
                else
                {
                    string tmp = code.substr(1);
                    decompress(tmp,curr.right(),result);
                }

            }
        }
    }
}
void Decompressor::run()
{
    if(getInputFile().empty())
    {
        string name;
        cerr<<"No input file declared\n";
        cout<<"Enter input file name: ";
        getline(cin,name);
        setInputFile(name);
    }
    if(getOutputFile().empty())
    {
        string name;
        cerr<<"No output file declared\n";
        cout<<"Enter output file name: ";
        getline(cin,name);
        setOutputFile(name);
    }
    //въвеждаме дървото от стандартния вход
    tree.enter(cin);
    tree.prettyPrint(cout,0);
    //записваме двоичната последователност
    string code = readCode();
    //cout<<code;
    //декомпресирания резултат записваме в низа result и след това в изходния файл
    string result = "";
    decompress(code, tree.getRoot(),result);
    cout<<result;
    ofstream fout;
    fout.open(getOutputFile(),ios::out|ios::app);
    fout<<result;
    fout.close();
}
