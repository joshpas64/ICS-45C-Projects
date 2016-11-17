// expmain.cpp
//
// Do whatever you'd like here.  This is intended to allow you to experiment
// with the code in the "app" directory or with any additional libraries
// that are part of the project, outside of the context of the main
// application or Google Test.
#include "linkedlist.hpp"
#include "Hashfunction.hpp"
#include "HashMap.hpp"
#include "interface.hpp"

int main()
{
	//Commented code below were just tests when constructing the HashMap class
	/*
	HashMap hm = HashMap(simpleHash);
	hm.add("pascascio.joshua@yahoo.com","83290");
	hm.add("pascascio.joshua@yahoo.com","1234");
	hm.add("joshua.pascascio@gmail.com","1994");
	hm.add("Miley Cyrus", "DISNEY");
	hm.add("Some dude","THE DUDE");
	hm.add("Crypto","Encryption");
	hm.add("Hungry","Hippo");
	hm.add("Momo","Hinamori");
	hm.add("Ichigo Kurosaki","StrawBerry");
	hm.add("Doctor","WHO");
	std::cout << hm.bucketCount() << std::endl;
	std::cout << hm.size() << std::endl;
	std::cout << hm.loadFactor() << std::endl;
	std::cout << hm.maxBucketSize() << std::endl;
	hm.output();
	hm = HashMap();
	std::cout << hm.bucketCount() << std::endl;
	*/
	//Make an interface object, which will include a HashMap object and references to some HashFunctions
	Interface i = Interface();
	i.run(); //Run the interface for the user until the user wishes to terminate
	//termination in this case is when the run() returns which is when cont == -1 which is when user enters QUIT
	return 0;
}

