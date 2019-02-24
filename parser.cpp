#include <iostream>
#include <stack>

#include "parser.h"

void Parser::checkMatch (char left, char right, int lineNumber)
{

    switch(right)
        {
        case ')':
            m_Stack.pop();
            if (left == '{' || left == '[')
                mismatchError(left, right, lineNumber);
            break;

        case '}':
            m_Stack.pop();
            if (left == '(' || left == '[')
                mismatchError(left, right, lineNumber);
            break;

        case ']':
            m_Stack.pop();
            if (left == '(' || left == '{')
                mismatchError(left, right, lineNumber);
            break;
        }
}

void Parser::Check()
{
    // Clear the stack so we make sure we begin our process with an empty stack
    while(!m_Stack.empty())
    {
        m_Stack.pop();
    }

    char c;
    int lineNumber = 1; // We want line numbers to always start at 1

    /* Read the input file 'm_is' character by character and look for opening
        parentheses. When we find one, place it into our stack. Because we must
        first read in an opening parenthesis, if one isn't found and the stack
        is empty, then we know we immediately have a problem with balancing
        our parenthesis.

        This method works by inserting each symbol into a stack with the last
        known opening symbol placed on top. We do this so we can work backwards
        to make sure everything is balanced properly.
    */
    while(m_is.get(c))
    {

        if(c == '('||c == '['||c == '{')
        {
            m_Stack.push(c);
            //continue;
        }
        else if(c == '\n'){
            lineNumber++;
        }
        else if(m_Stack.empty()){
            unmatchedError(c, lineNumber);
        }
        else
        {
            checkMatch(m_Stack.top(), c, lineNumber);
        }

    }

    /* Checks to see if the stack is empty. If the stack is not empty and we
        are no longer iterating through the input file, then we have opening
        parentheses that are not matched.
    */
    while(!m_Stack.empty())
    {
        unmatchedError(m_Stack.top(), lineNumber);
        m_Stack.pop();
    }

    m_os << "Done";
}
