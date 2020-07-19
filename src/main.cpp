#include <iostream>
#include "Logger.h"

int main(int argc, char *argv[]) {

	mercury::Logger &instance = mercury::Logger::get();
	instance.setLevel(mercury::Level::info);

	instance.debug("tap tap...is this thing on?");
	instance.warn("Yes it's on...Now dont say anything stupid everyone can hear you!");
	instance.critical("HELLO! WE GOT BIG ISSUES!...WE HAVE NOTHING TO LOG!");
	instance.debug("tap tap...is this thing on?");
    instance.info("Nevermind those guys, onto the main event...");
    instance.info("Hello! Welcome to Mercury, a quick and simple C++ logger.");

}