//
//  main.cpp
//  test_undo
//
//  Created by yongjian feng on 1/9/20.
//  Copyright © 2020 yongjian feng. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <regex>


using namespace std;

vector<unsigned char> buf;
vector<int> replace_lst;

void set_buf(string str_in)
{
    copy(str_in.begin(), str_in.end(), back_inserter(buf));
}

int count_to_string(vector<unsigned char>::iterator search_start,
                     vector<unsigned char>::iterator search_end,
                     string str_to,
                     int cur_index)
{
    int count = 0;
    vector<unsigned char>::iterator itr =
    search(search_start, search_end, str_to.begin(), str_to.end());
    while (itr != search_end)
    {
        replace_lst.push_back(cur_index + count);
        count ++;
        itr = search(itr + str_to.size(), search_end, str_to.begin(), str_to.end());
    }
    return count;
}

void replace(string str_from, string str_to)
{
    // if str_from is a substring of str_to, then
    // no need to store replace_lst
    bool is_substring = search(str_to.begin(), str_to.end(),
                               str_from.begin(), str_from.end()) != str_to.end();
    
    vector<unsigned char>::iterator search_start = buf.begin();
    vector<unsigned char>::iterator search_end = buf.end();
    
    vector<unsigned char>::iterator next_from = search(search_start, search_end, str_from.begin(), str_from.end());
    int cur_index = 0;
    while (next_from != buf.end())
    {
        int count = 0;
        if (!is_substring)
        {
            count = count_to_string(search_start, next_from, str_to, cur_index);
        }
        cur_index += count;
        // first erase and then insert?
        buf.erase(next_from, next_from + str_from.size());
        buf.insert(next_from, str_to.begin(), str_to.end());
        cur_index ++;
        search_start = next_from + str_to.size();
        next_from = search(search_start, buf.end(), str_from.begin(), str_from.end());
    }
}

void undo(string from_str, string to_str)
{
    // Look for all the to_str occurrances, it
    // it is not in the replace_lst
    int cur_index = 0;
    vector<unsigned char>::iterator search_start = buf.begin();
    vector<unsigned char>::iterator search_end = buf.end();
    
    vector<unsigned char>::iterator itr = search(search_start, search_end,
                                                 to_str.begin(), to_str.end());
    while (itr != buf.end())
    {
        // is cur_index in replace_lst?
        bool b_inlist = find(replace_lst.begin(), replace_lst.end(),
                             cur_index) != replace_lst.end();
        if (!b_inlist)
        {
            //https://stackoverflow.com/questions/4643512/replace-substring-with-another-substring-c
            // The above find/replace won't work if from_str.size() != to_str.size()
            buf.erase(itr, itr + to_str.size());
            buf.insert(itr, from_str.begin(), from_str.end());
            search_start = itr + from_str.size();
        }
        else
        {
            search_start = itr + to_str.size();
        }
        cur_index ++;
        itr = search(search_start, buf.end(),
                     to_str.begin(), to_str.end());
    }
}

int main(int argc, const char * argv[]) {
    
    string in_str = "This is a program in C++ to test design pattern memento. The idea is to use memento to store states. Memento is a middle man in this approach. The design pattern contains a memento, a caretaker, and a originator.";

    //in_str = "hello, he says hello";
    set_buf(in_str);
    
    replace(" a ", " to ");
    
    string rep_str = regex_replace(in_str, regex(" a "), " to ");
    
    string replaced;
    copy(buf.begin(), buf.end(), back_inserter(replaced));
    assert(rep_str.compare(replaced) == 0);
    
    undo(" a ", " to ");
    
    string content;
    copy(buf.begin(), buf.end(), back_inserter(content));
    
    assert(in_str.compare(content) == 0);
    
    return 0;
}
