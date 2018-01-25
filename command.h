
#ifndef _COMMAND_H_
#define _COMMAND_H_
#include<iostream>
#include<huffman.h>
#include<unordered_set>
#include<string>
class Command
{
    Huff* h;
    string command;

    void copy(Command const& other);
    void erase();
public:
    Command(Huff* _h = new Huff(), string _command = "compress"):h(_h), command(_command){}
    Command(Command const& other);
    Command& operator=(Command const& other);

    void setCommand(string c);
    string getCommand();
    void run();
};

#endif // _COMMAND_H_
