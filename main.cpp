#include<huffman.h>
#include<command.h>
#include<iostream>
using namespace std;
int main()
{
    Command c;
    while(true)
    {
        cout<<"Enter command: ";
        c.setCommand("compress");
        c.run();
    }
    return 0;
}
