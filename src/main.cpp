#include <iostream>
#include "Logger.h"


int main(int argc, char *argv[]) {

	mercury::Logger &mercury = mercury::Logger::get();
	mercury.setLevel(mercury::Level::trace);

	mercury::Theme *t = mercury.getTheme();
	t -> setIsTimestampEnabled(false);
	t -> setLevelNameLen(1);
	// std::string s = t.apply(mercury::Level::debug, "This is a test");

	// std::cout << s << std::endl;
	mercury.trace("Turning the fan on");
	mercury.info("Fan on");
	mercury.debug("Is there somthing wrong with the fan?");
	mercury.warn("Yo $#%& may be hitting the fan");
	mercury.critical("$#%& JUST HIT THE FAN");
	mercury.error("THE FAN JUST BROKE");

}