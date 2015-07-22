#include <iostream>
#include <sstream>
#include <string>
#include "hconfig.hpp"

using namespace std;

struct TestConfig : public Config
{
	//[SECTION1]
	std::string _name;
	std::string _logfile;

	//[SECTION2]
	int _max;
	double _min;
	
	// get config, use default value if get failed
	#define GET_CONFIG_DEFAULT(type, section, name, value, default_value) \
        if (get_##type##_param(section, name, (type&)value) < 0) {\
            value = default_value;\
            std::cout << "[" << section << "]" << name << "=" << value << std::endl;\
        } else {\
            std::cout << "[" << section << "]" << name << "=" << value << std::endl;\
        }

	// get config, return error(-1) if get failed
	#define GET_CONFIG(type, section, name, value) \
        if (get_##type##_param(section, name, (type&)value) < 0) {\
            std::cerr << "get [" << section << "]" << name << " failed" << std::endl;\
            return -1;\
        } else {\
            std::cout << "[" << section << "]" << name << "=" << value << std::endl;\
        }

	int load(const std::string & filename)
	{
		int rv = 0;
        rv = Config::load(filename);
        if(rv<0)
        {   
            std:cerr << "config init failed " << endl;
            return -1; 
        }   

		GET_CONFIG(string, "SECTION1", "name", _name);
        GET_CONFIG_DEFAULT(string, "SECTION1", "file", _logfile, "config.cfg");
		GET_CONFIG(int, "SECTION2", "max", _max);
        GET_CONFIG_DEFAULT(double, "SECTION2", "min", _min, 0.2);

		return rv;
	}

	std::string to_string() const
	{
		std::stringstream ss;
		ss << "{name:" << _name
		<< ", loggfile:" << _logfile
		<< ", max:" << _max
		<< ", min:" << _min
		<< "}";
		return ss.str();
	}
};

int main()
{
	TestConfig tc;
	tc.load("config-example.cfg");
	std::cout << tc.to_string() << std::endl;
	return 0;
}
