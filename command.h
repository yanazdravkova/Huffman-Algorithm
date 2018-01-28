
#ifndef _COMMAND_H_
#define _COMMAND_H_
#include<iostream>
#include<huffman.h>
#include<unordered_set>
#include<string>
#include<decompressor.h>
class Command
{
    Huff com;
    Decompressor dec;
    string command;
    bool stopFlag = 0;
public:
    Command(string _command = "compress"):com(),dec(), command(_command), stopFlag(false){}

    void setCommand(string c);
    string getCommand() const;
    bool getStopFlag() const;
    void run();

    void setInputFile(string ifile);
    void setOutputFile(string ofile);
};

#endif // _COMMAND_H_
