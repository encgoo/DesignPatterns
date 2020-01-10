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

string long_str =
    "This is a program in C++ to test design pattern memento and command. "
    "The idea is to use memento to store states. Each memento contains "
    "a (pointer to) command. The design pattern contains "
    "a memento, a caretaker, and a originator.";


void TestInsert();
void TestAppend();
void TestErase();
void TestEraseTrailing();
void TestReplace();
void TestSaveRead();
void TestUndoRedo();


int main(int argc, const char * argv[]) {
    TestInsert();
    TestAppend();
    TestErase();
    TestEraseTrailing();
    TestReplace();
    TestSaveRead();
    TestUndoRedo();
    return 0;
}

void TestUndoRedo()
{
    printf("Testing undo & redo command history...\n");
    string str1("Hello ");
    string str2("World! ");
    string str3("This ");
    string str4("is a ");
    string str5("C++ ");
    string str6("program.");
    
    printf("\tTesting constructor (history 0/0)...\n");
    membuf mbuf(str1);
    string ret = mbuf.get_content();
    assert(ret.compare(str1) == 0);
    
    printf("\tappend (history 1/1) ...\n");
    mbuf.append(str2 + str3 + str4 + str6);
    ret = mbuf.get_content();
    assert(ret.compare(str1 + str2 + str3 + str4 + str6) == 0);
    
    printf("\tinsert (history 2/2)...\n");
    mbuf.insert((str1 + str2 + str3 + str4).size(), str5);
    ret = mbuf.get_content();
    assert(ret.compare(str1 + str2 + str3 + str4 + str5 + str6) == 0);
           
    printf("\tundo twice (history 0/2)...\n");
    mbuf.undo();
    mbuf.undo();
    ret = mbuf.get_content();
    assert(ret.compare(str1) == 0);
    
    printf("\tredo only ONCE (history 1/2)...\n");
    mbuf.redo();
    ret = mbuf.get_content();
    assert(ret.compare(str1 + str2 + str3 + str4 + str6) == 0);
    
    printf("\terase trailing (history 2/2) ...\n");
    mbuf.erase_trailing(str6.size());
    ret = mbuf.get_content();
    assert(ret.compare(str1 + str2 + str3 + str4) == 0);
    
    printf("\tredo again (history 2/2) ...\n");
    // The above edit shall remove the remaining redo. This
    // redo shall do nothing
    mbuf.redo();
    ret = mbuf.get_content();
    assert(ret.compare(str1 + str2 + str3 + str4) == 0);
    
    printf("\tappend (history 3/3) ...\n");
    mbuf.append(str6);
    ret = mbuf.get_content();
    assert(ret.compare(str1 + str2 + str3 + str4 + str6) == 0);
    
    printf("\tundo wrong append (history 2/3)...\n");
    mbuf.undo();
    ret = mbuf.get_content();
    assert(ret.compare(str1 + str2 + str3 + str4) == 0);
    
    printf("\tappend again (history 3/3)...\n");
    mbuf.append(str5 + str6);
    ret = mbuf.get_content();
    assert(ret.compare(str1 + str2 + str3 + str4 + str5 + str6) == 0);
    
    printf("\tundo 3 times (history 0/3) ...\n");
    mbuf.undo().undo().undo();
    ret = mbuf.get_content();
    assert(ret.compare(str1) == 0);
    
    
    printf("Tested undo & redo.\n");
}

void TestSaveRead()
{
    printf("Testing save and read ...\n");
    string init_str = "Hello world!";
    membuf text_buf(init_str);
    
    // Test read and save
    printf("\tSaving ...\n");
    const string filename = "test.txt";
    text_buf.save_file(filename);
    
    printf("\tReading back ...\n");
    membuf in_buf("");
    size_t sz_read = in_buf.read_file(filename);
    
    // Make sure we can read the file we just wrote
    assert(sz_read == init_str.size());
    
    string read_content = in_buf.get_content();
    
    // Verify the content we read
    assert(read_content.compare(init_str) == 0);
    
    printf("Tested save and read.\n");
}

void TestEraseTrailing()
{
    printf("Testing erase_trailing ...\n");
    string str1("Hello World!");
    string str2("This is a C++ program.");
    membuf mbuf(str1 + str2);
    
    printf("\tErase trailing ...\n");
    mbuf.erase_trailing(str2.size());
    string ret = mbuf.get_content();
    assert(ret.compare(str1) == 0);
    
    printf("\tUndo erase trailing...\n");
    mbuf.undo();
    ret = mbuf.get_content();
    assert(ret.compare(str1 + str2) == 0);
    
    printf("Tested erase_trailing.\n");
}

void TestErase()
{
    printf("Testing erase ...\n");
    string init_str("Hello World!");
    string new_str("Hello ");
    
    membuf mbuf(init_str);
    
    printf("\tInsert a string...\n");
    mbuf.insert(6, new_str);
    string ret = mbuf.get_content();
    assert(ret.compare("Hello Hello World!") == 0);
    
    printf("\tErase the string ...\n");
    mbuf.erase(6, new_str.size());
    ret = mbuf.get_content();
    assert(ret.compare(init_str) == 0);

    printf("\tUndo erase ...\n");
    mbuf.undo();
    ret = mbuf.get_content();
    assert(ret.compare("Hello Hello World!") == 0);
    
    printf("\tUndo insert ...\n");
    mbuf.undo();
    ret = mbuf.get_content();
    assert(ret.compare(init_str) == 0);
    
    printf("Tested erase.\n");
}
void TestAppend()
{
    printf("Testing append ....\n");
    printf("\tAppend string ....\n");
    membuf mbuf(long_str);
    string new_str(" Added tests to get complete code coverage.");
    mbuf.append(new_str);
    
    string result = mbuf.get_content();
    assert(result.compare(long_str + new_str) == 0);
    
    printf("\tUndo append ...\n");
    mbuf.undo();
    result = mbuf.get_content();
    assert(result.compare(long_str) == 0);
    printf("Tested append.\n");
}

void TestInsert()
{
    printf("Testing insert ...\n");
    
    string init_str = "Hello world!";
    membuf text_buf(init_str);
    
    printf("\tinsert a string ...\n");
    text_buf.insert(5, " Hello");
    string inserted = text_buf.get_content();
    assert(inserted.compare("Hello Hello world!") == 0);
    
    printf("\tUndo insert ...\n");
    text_buf.undo();
    string undo_str = text_buf.get_content();
    assert(undo_str.compare(init_str) == 0);
    
    text_buf.redo();
    string redo_str = text_buf.get_content();
    assert(redo_str.compare(inserted) == 0);
    
    printf("Tested insert.\n");
}

void TestReplace()
{
    // Test replace with longer text
    printf("Testing replace.\n");

    string in_str = long_str;
    membuf long_buf(in_str);
    
    // Test special case when from_str is a substring of to_str
    printf("\tSpecial case: replacing 'te' with 'test'...\n");
    long_buf.replace("te", "test");
    string replaced = long_buf.get_content();
    string rep_str = regex_replace(in_str, regex("te"), "test");
    assert(replaced.compare(rep_str) == 0);
    
    long_buf.undo();
    string undo_str = long_buf.get_content();
    assert(in_str.compare(undo_str) == 0);
    
    long_buf.redo();
    string redo_str = long_buf.get_content();
    assert(rep_str.compare(redo_str) == 0);
    
    // Test normal case
    printf("\tNormal case: replacing ' a ' with ' the '...\n");
    membuf nor_buf(long_str);
    nor_buf.replace(" a ", " the ");
    replaced = nor_buf.get_content();
    rep_str = regex_replace(long_str, regex(" a "), " the ");
    assert(replaced.compare(rep_str) == 0);
    
    // Test other case
    printf("\tNormal case: replacing ' to ' with ' not_such_word '...\n");
    nor_buf.replace(" to ", " not_such_word ");
    replaced = nor_buf.get_content();
    rep_str = regex_replace(rep_str, regex(" to "), " not_such_word ");
    assert(replaced.compare(rep_str) == 0);
    
    printf("Tested replace.\n");
}
