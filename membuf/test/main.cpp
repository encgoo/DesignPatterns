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

using namespace std;

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
    return 0;
}
