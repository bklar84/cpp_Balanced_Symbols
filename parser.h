#ifndef __PARSER_H__
#define __PARSER_H__

#include <list>
#include <stack>
#include <string>

/*
* This class will read from the provided input stream, checking for balancing of
* () [], and {} pairs.
*
* If an error is detected, then the program prints an error message to 
* the provided output stream. The messages are one of the following:
*  "Unmatched { in line N"
*  "Unmatched } in line N"
*  "Mismatched { and } in line N"
* where the character { could be replaced by any of {, (, or [
* and the charcter } could be replaced by any of }, ], or ) and
* N is the line number in which the error was detected.
*/

class Parser
{
private:
	// the stack to keep the current state of the parser
	std::stack<char, std::list<char> > m_Stack;
	// the input stream
	std::istream& m_is;
	// the output stream
	std::ostream& m_os;

private:
	/*
	 * Use this routine to signal errors when you have encountered a )]}
	 * that does not match the most recent ([{
	 * 
	 * @param left character that we were trying to match (one
	 *     of '(', '[', or '{')
	 * @param right character that saw instead (one
	 *     of ')', ']', or '}')
	 * @param lineNumber  line of input in which the right character
	 *     was encountered.
	 * 
	 */
	void mismatchError(char left, char right, int lineNumber)
	{
		// Use this routine to signal errors when you have encountered a )]}
		// that does not match the most recent ([{
		m_os << "*Mismatched " << left << " and " << right << " in line " << lineNumber << std::endl;
	}

	/*
	 * Use this routine to signal errors when you have encountered a {[(
	 * and there are no )]} (even non-matching ones) left in the input, or 
	 * if you have encountered a )]} with no preceding ({[ (even non-matching 
	 * ones) in the input.
	 *
	 * @param c Character that was not properly matched.
	 * @param lineNumber  line of input in which that character was encountered.
	 */
	void unmatchedError(char c, int lineNumber)
	{
		m_os << "*Unmatched " << c << " in line " << lineNumber << std::endl;
	}

	// utility function to check the current state of the stack and call output functions when necessary
	void checkMatch (char left, char right, int lineNumber);

public:
	Parser(std::istream& is, std::ostream& os) : m_is(is), m_os(os)
	{}

	// The function that will loop through the input and update the stack
	void Check();
};

#endif // __PARSER_H__
