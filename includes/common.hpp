#ifndef __BETACORE_COMMON_HPP__
#define __BETACORE_COMMON_HPP__

#define BUFFER_LENGTH 1024

#include <string>
namespace betacore
{

enum SHAPE
{
	NONE,
	TRIANGLE,
	CIRCLE,
	SQUARE,
	PENTAGON,
	UNKOWN
};
enum MODE
{
	ALICE,
	BOB,
	EVE,
	END
};
class Parser
{
	public:
	static std::string mode(MODE &mode)
	{
		switch (mode)
		{
		case ALICE:
			return "ALICE";
		case BOB:
			return "BOB";
		default:
			return "END";
		}
	}
	static MODE mode(const std::string &mode)
	{
		if (mode == "ALICE")
			return ALICE;
		if (mode == "BOB")
			return BOB;
		return END;
	}

	static SHAPE shape(const std::string &shape)
	{

		if (shape == "TRIANGLE")
			return TRIANGLE;
		if (shape == "CIRCLE")
			return CIRCLE;
		if (shape == "SQUARE")
			return SQUARE;
		if (shape == "PENTAGON")
			return PENTAGON;
		return UNKOWN;
	}

	static std::string shape(const SHAPE &shape)
	{
		std::string message;
		switch (shape)
		{
		case TRIANGLE:
			message = "TRIANGLE";
			break;
		case CIRCLE:
			message = "CIRCLE";
			break;
		case SQUARE:
			message = "SQUARE";
			break;
		case PENTAGON:
			message = "PENTAGON";
			break;
		default:
			message = "UNKOWN";
			break;
		}
		return message;
	}
};
} // namespace betacore
#endif