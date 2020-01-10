# Buffer Management

Emulate buffer management found within many text editor

## 1. Requirements
##### 1.1 A text buffer to store text.
##### 1.2 User can initialize the text buffer with some text
##### 1.3 User can insert a substring at a position
##### 1.4 User can append a substring to the existing text
##### 1.5 User can erase n characters at a given position
##### 1.6 User can erase n trailing characters from the existing text
##### 1.7 User can replace all occurrences of a substring with another one
##### 1.8 User can undo the above operation(s)
##### 1.9 User can redo the above operation(s)
##### 1.10 User can save the text buffer content in to a txt file
##### 1.11 User can load the content from a txt file
##### 1.12 User expects high efficiency in memory usage when there are many operations are made, and each involves only small changes.

## 2. Design
Design patterns are used in the implementation. 

### 2.1 Design Patterns
#### 2.1.1 Memento
This design decision comes from Requirement 1.8 and 1.9. Memento can be used to manage states and history of operations.

#### 2.1.2 Command
This design decision can be linked to Requirement 1.12. Instead of storing the whole buffer before modification, we store the
command (operation) together with some necessary information for undo.

### UML Class Diagrams


## 3. Make


## 4. Usage
 
## 5. Test
