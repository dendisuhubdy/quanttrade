#pragma once

#include <blpapi/blpapi_defs.h>
#include <blpapi/blpapi_element.h>
#include <blpapi/blpapi_event.h>
#include <blpapi/blpapi_eventdispatcher.h>
#include <blpapi/blpapi_exception.h>
#include <blpapi/blpapi_logging.h>
#include <blpapi/blpapi_message.h>
#include <blpapi/blpapi_name.h>
#include <blpapi/blpapi_request.h>
#include <blpapi/blpapi_session.h>
#include <blpapi/blpapi_subscriptionlist.h>

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <stdlib.h>
#include <string.h>

using namespace BloombergLP;
using namespace blpapi;

typedef struct {
	double price;
	double perc_shares_out;
	double eq_shares_out;
} t_securitydata;

class input
{
private:
	// private needed variables
	std::string              d_host;
	int                      d_port;
	std::vector<std::string> d_securities;
	std::vector<std::string> d_fields;
	std::vector<std::string> indexlist;

	// private needed function
	bool parseCommandLine(int argc, char **argv);
	void printErrorInfo(const char *leadingStr, const Element &errorInfo);
	void printUsage();
	void registerCallback(int verbosityCount);
	void sendRefDataRequest(Session &session);
	void processResponseEvent(Event event);
	void eventLoop(Session &session);
public:
	input();
	~input();
	void run(int argc, char **argv);
	size_t numSecurities;
	std::vector<t_securitydata> data;
};

