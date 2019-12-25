#include "helpers.hpp"
#include "logger.hpp"
#include "declarations.hpp"
#include "gl_request_queue_listener.cxx"
#include "gl_modem_listener.cxx"
#include <typeinfo>

using namespace std;

template <class Generic_Type>
class Test {
	private:
		string class_name = "Test";
	public:
		bool equal_values( Generic_Type value1, Generic_Type value2 ) const {
			string func_name = this->class_name + ":equal_values";
			if( typeid( value1).name() != typeid( value2).name() ) return false;
			return value1 == value2;
		}
};


string test_request_file = string( getenv("HOME")) + "/deku/test_request.txt";

int main() {

	SYSTEM_STATE = "DEVELOPMENT";
	Test<size_t> size_t_tester;

	auto list_of_modems = gl_modem_listener();
	size_t s_list_of_modems = list_of_modems.size();
	int expected_value = 2;
	bool test = size_t_tester.equal_values( s_list_of_modems, expected_value );
	logger::logger_tester("Tester", test);
	if( !test) {
		logger::logger("Tester", "\nvalue1: " + to_string( s_list_of_modems ) + "\nvalue2: " + to_string( expected_value ) + "\n");
	}
	else {
		if( list_of_modems[0]["index"] == "0") {
			logger::logger("Tester", "\nMMCLI Index matches");
			
			if( list_of_modems[1]["index"] == "192.168.8.1" ) {
				logger::logger("Tester", "\nSSH index matches" );

				if( list_of_modems[0]["type"] == "mmcli" ) {
					logger::logger("Tester", "\nMMCLI type matches" );

					if( list_of_modems[1]["type"] == "ssh" ) {
						logger::logger("Tester", "\nSSH type matches" );
					}
					else {
						logger::logger("Tester", "\nSSH type doesn't match", "stderr");
					}
				}
				else {
					logger::logger("Tester", "\nMMCLI type doesn't match", "stderr");
				}
			}
			else {
				logger::logger("Tester", "\nSSH index doesn't match", "stderr");
			}
		}
		else {
			logger::logger("Tester", "\nMMCLI index doesn't match", "stderr");
		}
	}


	return 0;
}
