#include<command.h>
#include<huffman.h>
#include<iostream>
#include<string>
#include <stdlib.h>
using namespace std;
void Command::copy(Command const& other)
{
    h = other.h;
    command = other.command;
}
    Command::Command(Command const& other):Command(other.h, other.command){}
    Command& Command::operator=(Command const& other)
    {
        if(this != &other)
        {
            copy(other);
        }
        return *this;
    }

    void Command::setCommand(string c)
    {
        command = c;
    }
    string Command::getCommand()
    {
        return command;
    }
    void Command::run()
    {
        cout<<"run executed"<<endl;
        if(command.compare("compress") == 0)
        {
            h = new Huff();
            cout<<"~!!!!!";
            h->createFrequencyTable();
            cout<<endl<<"FREQUENCY TABLE"<<endl;
            h->printFrequencyTable();
            h->buildTree();
            cout<<"TREE"<<endl;
            h->printTree();
            h->createCodeTable();
            cout<<"CODE TABLE"<<endl;
            h->printCodeTable();
            cout<<"COMPRESSION RATE"<<endl;
            h->calculateCompressionRate();
            int a;
            cout<<"to save binary format press 1 || to save decimal press 0";
            cin>>a;
            if(a == 1)
                h->saveBinaryCode();
            else
                h->saveDecCode();
        }
        else if(command.compare("decompress") == 0)
        {

        }
        else if(command.compare( "i") == 0)
        {
            string inputFile;
            getline(cin,inputFile);
            h->setInputFile(inputFile);
        }
        else if(command.compare("o") == 0)
        {
            string outputFile;
            getline(cin,outputFile);
            h->setOutputFile(outputFile);
        }
        else
        {
            cout<<"exiting program to follow ";
            exit(0);
        }
    }
