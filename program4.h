#ifndef PROGRAM4_H
#define PROGRAM4_H

#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>

typedef struct char_freq{
  char c;
  double freq;
  char_freq* left;
  char_freq* right;

  char_freq(char c, double freq)
    :c(c),
     freq(freq), 
     left(nullptr), 
     right(nullptr)
  {}
} CFreq;

typedef struct char_code{
  char c;
  std::string code;
  char_code(char c, std::string code)
    :c(c),
     code(code)
  {}
} CCode;

/*
 * In order to make a min-heap using std::priority_queue,
 * must define a comparison to use instead of std::greater
*/
struct compare{
  bool operator() (char_freq* l, char_freq* r)
  {
    return l->freq > r->freq;
  }
};

//Method to code Huff Tree
std::vector<CCode> codes;
void makeCode(char_freq* ch, std::string s)
{
  //If pointer is null, no code, return
  if(ch == nullptr)
  {
    std::cout << "NULL POINTER" << std::endl;
    return;
  } 
 
  //If pointer is to '#', add 0 or 1 and continue
  if(ch->c == '#')
  {
    std::cout << "#" << std::endl;
    makeCode(ch->left, (s + "0"));
    makeCode(ch->right, (s + "1"));
  }

  //If pointer is not to '#', push string onto codes vector 
  if(ch->c != '#')
  {
    std::cout << "NOT # : " << ch->c << std::endl;
    char_code cc(ch->c, s);
    codes.push_back(cc);
    makeCode(ch->left, (s + "0"));
    makeCode(ch->right, (s + "1"));
  }
}

//input: vector of CFreqs 
//returns: vector of CCodes
std::vector<CCode> getHuffCodes(std::vector<CFreq > cfs){

  //Codes is global variable, clear 
  codes.clear();

  //Create min heap using std::priority_queue
  char_freq *top;
  char_freq *left;
  char_freq *right;
  std::priority_queue <char_freq*, std::vector<char_freq*>, compare> heap;

  //Push all values into min heap 
  for(int i = 0; i < cfs.size(); i++)
  {
    heap.push(new char_freq(cfs[i].c, cfs[i].freq));
  }  

  //Create Huff Tree
  while(heap.size() > 1)
  {
    left = heap.top();
    heap.pop();

    right = heap.top();
    heap.pop();

    top = new char_freq('#', (left->freq + right->freq));
    top->left = left;
    top->right = right;
    heap.push(top);
  }

  //Create Huff Code
  makeCode(heap.top(), "");

  return codes;
}

#endif //PROGRAM4_H
