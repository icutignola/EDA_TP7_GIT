#include "Error.h"

Error::Error()
{
	errorDescription = "No Error";
}

void Error::setError(string error)
{
	errorDescription = error;
}

string Error::getError(void)
{
	return errorDescription;
}
