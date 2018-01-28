#include<command.h>
#include<huffman.h>
#include<iostream>
#include<string>
#include <stdlib.h>
using namespace std;


void Command::setCommand(string c)
{
    command = c;
}
string Command::getCommand() const
{
    return command;
}
bool Command::getStopFlag() const
{
    return stopFlag;
}
void Command::setInputFile(string ifile)
{
    com.setInputFile(ifile);
    dec.setInputFile(ifile);
}
void Command::setOutputFile(string ofile)
{
    dec.setOutputFile(ofile);
    com.setOutputFile(ofile);
}
void Command::run()
{
    if(command.compare("compress") == 0)
    {
        if(com.getInputFileName() == "")
        {
            cerr<<"NO INPUT FILE NAME DECLARED";
            return;
        }
        if(com.getOutputFileName() == "")
        {
            cerr<<"NO OUTPUT FILE NAME DECLARED";
            return;
        }
        com.createFrequencyTable();
        com.printFrequencyTable();
        com.buildTree();
        com.printTree();
        com.saveTree();
        com.createCodeTable();
        com.printCodeTable();
        com.createBinaryCode();
        com.saveBinaryCode();
    }
    else if(command.compare("decompress") == 0)
    {
        if(dec.getInputFile() == "")
        {
            cerr<<"NO INPUT FILE NAME DECLARED";
            return;
        }
        if(dec.getOutputFile() == "")
        {
            cerr<<"NO OUTPUT FILE NAME DECLARED";
            return;
        }
        dec.run();
    }
    else if(command.compare( "i") == 0)
    {
        string inputFile;
        getline(cin,inputFile);
        setInputFile(inputFile);
    }
    else if(command.compare("o") == 0)
    {
        string outputFile;
        getline(cin,outputFile);
        setOutputFile(outputFile);
    }
    else
    {
        cout<<"exiting program to follow ";
        stopFlag = true;
        exit(0);
    }
}
