#include <iostream>
#include "Logger.h"

int main(int argc, char *argv[]) {

	mercury::Logger &instance = mercury::Logger::get();
	instance.log();
}