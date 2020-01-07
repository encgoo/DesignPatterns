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

class membuf
{
private:
    std::vector<unsigned char> m_buf;
public:
    membuf(std::string inbuf);
    virtual ~membuf(){};
    
    // Insert a substring at a position
    membuf& insert(size_t pos, const std::string& in_str);
    
    // Append a substring
    membuf& append(const std::string& in_str);
    
    // Erase n characters at a given position
    membuf& erase(size_t pos = 0, size_t len = std::string::npos);
    
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
    
    // Get content
    std::string get_content() const;
};
#endif /* membuf_hpp */
