//
//  membuf.hpp
//  membuf
//
//  Created by Yongjian Feng on 1/6/20.
//  Copyright © 2020 Yongjian Feng. All rights reserved.
//

#ifndef membuf_hpp
#define membuf_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include "StateController.hpp"
class Command;
class membuf
{
public:
    typedef std::vector<unsigned char> CharBuf;

private:
    std::vector<unsigned char>  m_buf;
    StateController             m_stateController;
    
public:
    membuf(std::string inbuf);
    virtual ~membuf(){};
    
    // Insert a substring at a position
    membuf& insert(size_t pos, const std::string& in_str);
    
    // Append a substring
    membuf& append(const std::string& in_str);
    
    // Erase n characters at a given position
    membuf& erase(size_t pos, size_t len);
    
    // Erase n trailing characters
    membuf& erase_trailing(size_t len);
    
    // Replace all occurences of a substring to another
    membuf& replace(const std::string& from_str, const std::string& to_str);
    
    // Undo
    membuf& undo();
    
    // Redo
    membuf& redo();
    
    // Load from TXT file
    size_t read_file(const std::string& filename);
    
    // Save to TXT file
    size_t save_file(const std::string& filename) const;
    
    // Utility functions
    // Get content
    std::string get_content() const;
private:
    // Execute a command
    membuf& execute(Command *pCommand);
};
#endif /* membuf_hpp */
