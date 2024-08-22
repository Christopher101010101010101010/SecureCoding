//	Christopher Anderson 2-3 Activity: Buffer Overflow Coding
// BufferOverflow.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iomanip>
#include <iostream>
#include <conio.h>		//_getchar(), _putch() - library header file

int main()
{
  std::cout << "Buffer Overflow Example" << std::endl;

  // TODO: The user can type more than 20 characters and overflow the buffer, resulting in account_number being replaced -
  //  even though it is a constant and the compiler buffer overflow checks are on.
  //  You need to modify this method to prevent buffer overflow without changing the account_order
  //  varaible, and its position in the declaration. It must always be directly before the variable used for input.

  const std::string account_number = "CharlieBrown42";

  const int inputLen = 21;									// allows for user to enter 20 chars to array while allowing array a terminating null index
  char user_input[inputLen] = {};							// user_input character array initialized to inputLen number of indexes and empty

  const char endLineChar = '\r';							// un-alterable character variable endLineChar set to carriage return symbol, sent by _getch() at Enter key activation
  const char delKeyChar = '\b';								// un-alterable character variable delKeyChar set to delete symbol, sent by _getch() at Backspace key activation
  const char nullChar = '\0';								// un-alterable character variable nullChar set to null symbol, used to empty character array indexes 
  
  char charBuffer = ' ';									// Initialize charBuffer to empty space
  int i = 0;												// Initialize counter variable i to 0

  std::cout << "Enter a value: ";

  // while counter is less than input length minus 1 and character buffer is not the end line symbol
  while (charBuffer != endLineChar) {
	  
	  charBuffer = (char)_getch();							//	then have character buffer receive keyboard input

	  if (i < inputLen - 1 )
		  _putch(charBuffer);								//	display this keyboard input to console


	  if (charBuffer == endLineChar)						//	if character buffer contains the Enter key symbol exit loop
		  break;

	  else if (charBuffer == delKeyChar && i > 0) {			// if character buffer contain backspace key symbol and counter is greater than 0
		  _putch(charBuffer);
		  _putch(' ');										// remove single character from console display
		  _putch(delKeyChar);

		  if (user_input[i] == nullChar) {					// if user_input i-th index is already empty decrement i
			  user_input[--i] = nullChar;
		  }
		  else {
			  user_input[i--] = nullChar;					// otherwise set user_input i-th index to null, pre-decrementing counter 'i'

		  }
		  
	  }
	  else if (charBuffer == delKeyChar && i == 0) {		// if user presses Backspace key and initial array index is not set to null
															//	then empty inital index otherwise do nothing
		  if (user_input[i] != nullChar) {
			  user_input[i] = nullChar;
		  }
	  }
	  else if (i < inputLen - 1) {
		  user_input[i++] = charBuffer;						//	otherwise set the i-th index of user_input array to the character buffer's contents
															//	and post-increment the counter 'i'
	  }
		  									
	  charBuffer = '\0';
  }


  std::cout << std::endl << std::endl;
  std::cout << "You entered: " << user_input << std::endl;
  std::cout << "Account Number = " << account_number << std::endl;

  return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
