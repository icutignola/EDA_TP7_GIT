#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Error
{
	public:
		Error();
		void setError(string error);
		string getError(void);
	private:
		string errorDescription;
};