#include "modem_listener.hpp"
#include "../formatters/helpers.hpp"

using namespace std;

Modems::Modems() {}

Modems Modems::getAll() {
	string list_of_modem_indexes = sys_calls::terminal_stdout("../../scripts/modem_information_extraction.sh list");
	vector<string> modem_indexes = helpers::split(list_of_modem_indexes, '\n', true);
	
	for(auto index : modem_indexes) {
		string modem_information = sys_calls::terminal_stdout("../../scripts/modem_information_extraction.sh extract " + index );
		vector<string> ln_modem_information = helpers::split(modem_information, '\n', true);

		Modem modem;
		modem.setIndex( index );
		for(auto ln : ln_modem_information) {
			vector<string> component = helpers::split(ln, ':', true);
			if( component[0] == "equipment_id") 
				modem.setIMEI( component[1].empty() ? "" : component[1] );
			else 
			if( component[0] == "operator_name")
				modem.setISP( component[1].empty() ? "" : component[1]);
			else
			if( component[0] == "signal_quality") {}

		}
		modems.push_back( modem );
	}
}
vector<string> Modems::getAllIndexes() {

}

vector<string> Modems::getAllISP() {}

vector<string> Modems::getAllIMEI() {}
