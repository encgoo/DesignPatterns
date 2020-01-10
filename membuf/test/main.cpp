//
//  main.cpp
//  test
//
//  Created by Yongjian Feng on 1/6/20.
//  Copyright © 2020 Yongjian Feng. All rights reserved.
//

#include <iostream>
#include "membuf.hpp"
#include <assert.h>
#include <regex>

using namespace std;

void TestReplaceOfLongBuf()
{
    
    // Test replace with longer text
    string in_str = "This is a program in C++ to test design pattern memento. The idea is to use memento to store states. Memento is a middle man in this approach. The design pattern contains a memento, a caretaker, and a originator.";
    membuf long_buf(in_str);
    
    // Test special case when from_str is a substring of to_str
    long_buf.replace("te", "test");
    string replaced = long_buf.get_content();
    string rep_str = regex_replace(in_str, regex("te"), "test");
    assert(replaced.compare(rep_str) == 0);
    
    long_buf.undo();
    string undo_str = long_buf.get_content();
    assert(in_str.compare(undo_str) == 0);
}


int main(int argc, const char * argv[]) {
    // insert code here...
    string init_str = "Hello world!";
    membuf text_buf(init_str);
    
    // Test read and save
    const string filename = "test.txt";
    text_buf.save_file(filename);
    
    membuf in_buf("");
    size_t sz_read = in_buf.read_file(filename);
    
    // Make sure we can read the file we just wrote
    assert(sz_read == init_str.size());
    
    string read_content = in_buf.get_content();
    
    // Verify the content we read
    assert(read_content.compare(init_str) == 0);
    
    // Test insert
    text_buf.insert(5, " Hello");
    
    // Test replace
    text_buf.replace("Hello", "hello");
    
    read_content = text_buf.get_content();
    
    // Special test
    text_buf.replace("hello", "hello");
    
    assert(read_content.compare("hello hello world!") == 0);
    
    TestReplaceOfLongBuf();
    
    return 0;
}
