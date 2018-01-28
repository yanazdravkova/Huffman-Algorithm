#include<huffman.h>
#include<decompressor.h>
#include<command.h>
#include<iostream>

using namespace std;
void compression()
{
    Huff h;
    h.run();
}
void decompress()
{
    Decompressor de;
    de.run();
}
int main()
{
    compression();
   // decompress();
    /*Command* c = new Command;
    while(!c->getStopFlag())
    {
        cout<<"\nenter command: ";
        string name;
        getline(cin, name);
        cout<<"command given: "<<name<<endl;
        c->setCommand(name);
        c->run();
    }
    delete c;
    */
    return 0;
}
