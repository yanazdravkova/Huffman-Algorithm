#include<huffman.h>
#include <algorithm>
#include <iomanip>
#include<string>
using namespace std;
bool sortBySecond(const Node* a,const Node* b)
{
    return (a->data.second < b->data.second);
}
//направи го шаблонно
void printMap(unordered_map<char, int> m)
{
     for ( const pair<char,int> p : m )
    {
        cout << " " << p.first << ":"<< p.second;
    }
    cout <<endl;
}
void printMap(unordered_map<char, string> m)
{
    for ( const pair<char,string> p : m )
    {
        cout<<" " << p.first << ":"<< p.second;
    }
    cout <<endl;
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
bool Huff::isMemberHelp(Node* const& r, char c) const
{
    if(r == nullptr)
        return false;
    if(c == r->data.first)
        return true;
    return isMemberHelp(r->left, c) || isMemberHelp(r->right, c);
}
bool Huff::isMember(char c) const
{
    return isMemberHelp(root, c);
}
string Huff::binaryCodeHelp(const char c, const Node* start) const
{
    if(c == start->data.first)
        return "";
    if(start == nullptr)
        return "";
    if(isMemberHelp(start->left,c))
        return "0" + binaryCodeHelp(c, start->left);
    if(isMemberHelp(start->right,c))
        return "1" + binaryCodeHelp(c, start->right);
    return "";//ако символът не се съдържа изобщо в дървото с корен start
}
string Huff::binaryCode(const char c) const
{
    return binaryCodeHelp(c,root);
}

void Huff::createCodeTable()
{
    if(root == nullptr)
        return;

    for( pair<char,int> p : frequencyTable)
    {
        codeTable.emplace(p.first,binaryCode(p.first));
    }
}
void Huff::saveBinaryCode() const
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
            }
        }
    }
    fin.close();
    fout.close();
}
//връща като резултат възела с най-малка числена стойност като същевременно го премахва от списъка с възели, подаден като параметър
Node*& Huff::findMinNode(list<Node*>& nodes)
{
    nodes.sort(sortBySecond);
    return nodes.front();
}

void Huff::buildTree()
{
    //стъпка 2 от построяване на дърво на Хъфман от описанието
    //създаваме n дървета от по един възел, който съдържа наредена двойка и ги записваме в списък, като той е сортиран във низходяш
    list<Node*> nodes;
    for(const pair<char,int> p : frequencyTable)
    {
        nodes.push_front(new Node(p));
    }
   /* nodes.sort(sortBySecond);
    cout<<nodes.front()->data.first<<" "<<nodes.front()->data.second<<endl;*/
    while(nodes.size() > 1)
    {
        Node* fst = findMinNode(nodes);
        nodes.pop_front();//премахваме fst от списъка
        Node* snd = findMinNode(nodes);
        nodes.pop_front();//премахваме snd от списъка
        Node* res = new Node(make_pair(' ',fst->data.second + snd->data.second), fst, snd);//строим ново дърво с поддървета 2те най-малки досега
        nodes.push_front(res);
    }
    //има само 1 възел в списъка и това е нашият корен
  //  root = nodes.pop_front();

  root = nodes.front();
}
void Huff::saveDecCode()const
{
    ofstream fout;
    fout.open(outputFile, ios::out|ios::app);
    list<string> subs;
    for(int i=0; i<code.size(); i + 8)
    {
        subs.push_back( code.substr(i,8));
        cout<<code.substr(i,8);
    }
    for(const string s : subs)
    {
        int tmp = binToDec(s);
        cout<<tmp<<endl;
        fout<<tmp;
    }
    fout.close();

}
void prettyPrint(ostream& out = cout,int currentHeight = 0, Node* start = nullptr)
{
    if(start ==nullptr)
        return;
    prettyPrint(out, currentHeight + 1, start->right);
    if(start->data.first == ' ')
        out<<setw(5*currentHeight)<<" "<<start->data.second<<endl;
    else
        out<<setw(5*currentHeight)<<" "<<start->data.first<<" "<<start->data.second<<endl;
    prettyPrint(out, currentHeight + 1,start->left);

}
void Huff::printTree() const
{
    prettyPrint(cout,0,root);

}
void Huff::printFrequencyTable() const
{
    printMap(frequencyTable);
}
void Huff::printCodeTable() const
{
    printMap(codeTable);
}
int main()
{
    Huff h;
    h.setInputFile("input.txt");
    h.setOutputFile("output.txt");
    h.createFrequencyTable();
    h.buildTree();
    h.createCodeTable();
    h.saveBinaryCode();
    h.saveDecCode();
    return 0;
}
