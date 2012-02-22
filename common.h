/**Copyright 2012 Fabien LUCE
This file is part of Cptalk!.

Cptalk! is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Cptalk! is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Cptalk!.  If not, see <http://www.gnu.org/licenses/>.**/

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
