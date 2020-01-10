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
class membuf
{
public:
    enum OPERATION
    {
        INSERT = 0,
        APPEND,
        ERASE,
        ERASE_TRAILING,
        REPLACE
    };
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
    
    int count_toString(std::vector<unsigned char>::iterator search_start,
                       std::vector<unsigned char>::iterator search_end,
                       std::string str_to,
                       int cur_index,
                       std::vector<int>& skipList);
    void undo_replace(const std::string& from_str, const std::string& to_str,
                      std::vector<int> skipList);
};
#endif /* membuf_hpp */
