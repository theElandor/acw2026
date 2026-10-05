#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;
int solve(string word, string input, vector<int> &ends){
  int index = input.find(word);
  if(index == -1){return -1;}
  int current_end_index = 0;
  while(current_end_index < ends.size() && index > ends[current_end_index]){current_end_index++;}
  return current_end_index;
}
int main(int argc, char **argv)
{
  string input;
  getline(cin,input);
  vector<string> words;
  string word;
  vector<int> ends;
  int current = -1;
  while(cin>>word){words.push_back(word);}
  vector<string> input_words;
  stringstream ss(input);
  string temp;
  while(ss >> temp){input_words.push_back(temp);}
  for(int i = 0; i<input_words.size(); i++){
    current = current + input_words[i].size();
    ends.push_back(current);
  }
  input.erase(remove_if(input.begin(), input.end(), [](unsigned char c) {return std::isspace(c);}), input.end());
  int total = 0;
  for(int i = 0; i < words.size(); i++){
    int current = solve(words[i], input, ends);
    total += current;
  }
  cout<<total<<endl;
  return 0;
}
