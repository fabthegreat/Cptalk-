#ifndef COMMON_H
#define COMMON_H

// Includes list
//
#include <string>
#include <vector>

using namespace std;


// amené a être le même

enum Type_content {all,command,message,announce};
enum Route {route_output,route_XMPP};
/*enum command_value {connect,disconnect,list_r};*/


class Line {
	public:
		Line(string s, Type_content tp=all);
		~Line();
	
		string content;
		Type_content type_content;
};

typedef vector<Line> Buffer;

class Command {
	public:
		Command();
		~Command();

		//parser command?
		
	private:
		Route route;
		string content;
};


#endif /* COMMON_H */
