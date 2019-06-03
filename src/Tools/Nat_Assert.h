#ifndef NATALIDE_NAT_ASSERT_H_	
#define NATALIDE_NAT_ASSERT_H_

#ifdef linux
	#define RESET 	"\033[0m"
	#define BLACK 	"\033[30m"
	#define RED 	"\033[31m"
	#define GREEN 	"\033[32m"
	#define YELLOW 	"\033[33m"
	#define BLUE 	"\033[34m"
	#define MAGENTA "\033[35m"
	#define CYAN 	"\033[36m"
	#define WHITE 	"\033[37m"
#elif _WIN32
	#define BLACK 	 0x0000
	#define BLUE 	 0x0001
	#define GREEN 	 0x0002
	#define CYAN 	 0x0003
	#define RED 	 0x0004
	#define MAGENTA  0x0005
	#define YELLOW 	 0x0006
	#define WHITE 	 0x0007
#endif


void fAssert (bool logic, const char *file, int line, const char *func)
{
	if (!logic)
	{
		#ifdef _WIN32
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
			std::cout << "FATAL:\n\tFILE : " << file << " \n\tLINE : " << line << " \n\tFUNC : " << func << std::endl;
		#else
			std::cout << RED << file << ":" << line << RESET << std::endl;
		#endif

		std::cout << "Press 'Enter' to continue..." << std::endl;
		std::cin.get();
		exit(0);
	}
}

void wAssert (bool logic, const char *file, int line, const char *func)
{
	if (!logic)
	{
		#ifdef _WIN32
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
			std::cout << "WARN:\n\tFILE : " << file << " \n\tLINE : " << line << " \n\tFUNC : " << func << std::endl;
		#else
			std::cout << YELLOW << "WARN:\n\tFILE : " << file << " \n\tLINE : " << line << " \n\tFUNC : " << func  << RESET << std::endl;
		#endif
	}
}

void lAssert (bool logic, const char *file, int line, const char *func)
{
	if (!logic)
	{
		#ifdef _WIN32
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), CYAN);
			std::cout << "LOG:\n\tFILE : " << file << " \n\tLINE : " << line << " \n\tFUNC : " << func << std::endl;
		#else
			std::cout << CYAN << "LOG:\n\tFILE : " << file << " \n\tLINE : " << line << " \n\tFUNC : " << func << RESET << std::endl;
		#endif
	}
}


#define FATAL_ASSERT(logic) fAssert(logic, __FILE__, __LINE__, __PRETTY_FUNCTION__)
#define WARN_ASSERT(logic) wAssert(logic, __FILE__, __LINE__, __PRETTY_FUNCTION__)
#define LOG_ASSERT(logic) lAssert(logic, __FILE__, __LINE__, __PRETTY_FUNCTION__)

#endif // NATALIDE_NAT_ASSERT_H_