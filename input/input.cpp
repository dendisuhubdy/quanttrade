#include "input.h"

// defining namespaces
using namespace BloombergLP;
using namespace blpapi;

// definitiong of finance specific data
namespace {
	const Name SECURITY_DATA("securityData");
	const Name SECURITY("security");
	const Name FIELD_DATA("fieldData");
	const Name RESPONSE_ERROR("responseError");
	const Name SECURITY_ERROR("securityError");
	const Name FIELD_EXCEPTIONS("fieldExceptions");
	const Name FIELD_ID("fieldId");
	const Name ERROR_INFO("errorInfo");
	const Name CATEGORY("category");
	const Name MESSAGE("message");
	const Name REASON("reason");
	const Name SESSION_TERMINATED("SessionTerminated");
	const Name SESSION_STARTUP_FAILURE("SessionStartupFailure");
};

// fetching function from a DLL/external library
extern "C" {
	// this is a specific type of data 
	// unsigned integers from Bloomberg
	void loggingCallback(blpapi_UInt64_t    threadId,
		int                severity,
		blpapi_Datetime_t  timestamp,
		const char        *category,
		const char        *message);
}

void loggingCallback(blpapi_UInt64_t    threadId,
	int                severity,
	blpapi_Datetime_t  timestamp,
	const char        *category,
	const char        *message)
{
	std::string severityString;
	switch (severity) {
		// The following cases will not happen if callback registered at OFF
	case blpapi_Logging_SEVERITY_FATAL:
	{
		severityString = "FATAL";
	} break;
	// The following cases will not happen if callback registered at FATAL
	case blpapi_Logging_SEVERITY_ERROR:
	{
		severityString = "ERROR";
	} break;
	// The following cases will not happen if callback registered at ERROR
	case blpapi_Logging_SEVERITY_WARN:
	{
		severityString = "WARN";
	} break;
	// The following cases will not happen if callback registered at WARN
	case blpapi_Logging_SEVERITY_INFO:
	{
		severityString = "INFO";
	} break;
	// The following cases will not happen if callback registered at INFO
	case blpapi_Logging_SEVERITY_DEBUG:
	{
		severityString = "DEBUG";
	} break;
	// The following case will not happen if callback registered at DEBUG
	case blpapi_Logging_SEVERITY_TRACE:
	{
		severityString = "TRACE";
	} break;

	};
	std::stringstream sstream;
	sstream << category << " [" << severityString << "] Thread ID = "
		<< threadId << ": " << message << std::endl;
	std::cout << sstream.str() << std::endl;;
}

// class initialization 
input::input()
{
	d_host = "localhost";
	d_port = 8194;
}

input::~input()
{
}

bool input::parseCommandLine(int argc, char **argv)
{
	int verbosityCount = 0;
	for (int i = 1; i < argc; ++i) {
		if (!std::strcmp(argv[i], "-s") && i + 1 < argc) {
			d_securities.push_back(argv[++i]);
		}
		else if (!std::strcmp(argv[i], "-f") && i + 1 < argc) {
			d_fields.push_back(argv[++i]);
		}
		else if (!std::strcmp(argv[i], "-ip") && i + 1 < argc) {
			d_host = argv[++i];
		}
		else if (!std::strcmp(argv[i], "-p") && i + 1 < argc) {
			d_port = std::atoi(argv[++i]);
		}
		else if (!std::strcmp(argv[i], "-v")) {
			++verbosityCount;

		}
		else {
			printUsage();
			return false;
		}
	}
	if (verbosityCount) {
		registerCallback(verbosityCount);
	}
	// handle default arguments
	if (d_securities.size() == 0) {
		// 
		d_securities.push_back("RHT US Equity");
		d_securities.push_back("MLM US Equity");
		d_securities.push_back("Q US Equity");
		d_securities.push_back("HIW US Equity");
		d_securities.push_back("CREE US Equity");
		d_securities.push_back("FCNCA US Equity");
		d_securities.push_back("PRAH US Equity");
		d_securities.push_back("INCR US Equity");
		d_securities.push_back("PGEM US Equity");
		d_securities.push_back("TCAP US Equity");
		d_securities.push_back("TRXC US Equity");
		d_securities.push_back("SQI US Equity");
		d_securities.push_back("ECOM US Equity");
		d_securities.push_back("POWR US Equity");
		d_securities.push_back("BDSI US Equity");
		d_securities.push_back("CMRX US Equity");
		d_securities.push_back("BCRX US Equity");
		d_securities.push_back("UNB US Equity");
		d_securities.push_back("XRM US Equity");
	}

	if (d_fields.size() == 0) {
		d_fields.push_back("PX_LAST");
		d_fields.push_back("EQY_FREE_FLOAT_PCT");
		d_fields.push_back("EQY_SH_OUT");
	}

	return true;
}

// [romtomge errpr 
void input::printErrorInfo(const char *leadingStr, const Element &errorInfo)
{
	std::cout << leadingStr
		<< errorInfo.getElementAsString(CATEGORY)
		<< " ("
		<< errorInfo.getElementAsString(MESSAGE)
		<< ")" << std::endl;
}

void input::printUsage()
{
	std::cout << "Usage:" << std::endl
		<< "    Retrieve reference data " << std::endl
		<< "        [-s         <security   = IBM US Equity>" << std::endl
		<< "        [-f         <field      = PX_LAST>" << std::endl
		<< "        [-ip        <ipAddress  = localhost>" << std::endl
		<< "        [-p         <tcpPort    = 8194>" << std::endl
		<< "        [-v         increase verbosity"
		<< " (can be specified more than once)"
		<< std::endl;
}


void input::registerCallback(int verbosityCount)
{
	blpapi_Logging_Severity_t severity = blpapi_Logging_SEVERITY_OFF;
	switch (verbosityCount) {
	case 1: {
		severity = blpapi_Logging_SEVERITY_INFO;
	}break;
	case 2: {
		severity = blpapi_Logging_SEVERITY_DEBUG;
	}break;
	default: {
		severity = blpapi_Logging_SEVERITY_TRACE;
	}
	};
	blpapi_Logging_registerCallback(loggingCallback,
		severity);
}

void input::sendRefDataRequest(Session &session)
{
	Service refDataService = session.getService("//blp/refdata");
	Request request = refDataService.createRequest("ReferenceDataRequest");

	// Add securities to request
	Element securities = request.getElement("securities");
	for (size_t i = 0; i < d_securities.size(); ++i) {
		securities.appendValue(d_securities[i].c_str());
	}

	// Add fields to request
	Element fields = request.getElement("fields");
	for (size_t i = 0; i < d_fields.size(); ++i) {
		fields.appendValue(d_fields[i].c_str());
	}

	//std::cout << "Sending Request: " << request << std::endl;
	session.sendRequest(request);
}


// return true if processing is completed, false otherwise
void input::processResponseEvent(Event event)
{
	MessageIterator msgIter(event);
	while (msgIter.next()) {
		Message msg = msgIter.message();
		if (msg.asElement().hasElement(RESPONSE_ERROR)) {
			printErrorInfo("REQUEST FAILED: ",
				msg.getElement(RESPONSE_ERROR));
			continue;
		}

		Element securities = msg.getElement(SECURITY_DATA);
		numSecurities = securities.numValues();
		/*
		std::cout	<< "Processing " 
					<< (unsigned int)numSecurities
					<< " securities:" 
					<< std::endl;*/

		for (size_t i = 0; i < numSecurities; ++i) {
			Element security = securities.getValueAsElement(i);
			std::string ticker = security.getElementAsString(SECURITY);
			//std::cout << "\nTicker: " + ticker << std::endl;
			if (security.hasElement(SECURITY_ERROR)) {
				printErrorInfo("\tSECURITY FAILED: ",
					security.getElement(SECURITY_ERROR));
				continue;
			}

			// outputing data here

			if (security.hasElement(FIELD_DATA)) {
				const Element fields = security.getElement(FIELD_DATA);
				if (fields.numElements() > 0) {

					//std::cout << "FIELD\t\tVALUE" << std::endl;
					//std::cout << "-----\t\t-----" << std::endl;

					size_t numElements = fields.numElements();
					
					t_securitydata temp;

					for (size_t j = 0; j < numElements; ++j) {
						Element field = fields.getElement(j);
						if (j == 0) {
							//std::cout << field.name() << std::endl;
							temp.price = field.getValueAsFloat64();
							//std::cout << temp.price << std::endl;
						}
						else if (j == 1) {
							//std::cout << field.name() << std::endl;
							temp.perc_shares_out = field.getValueAsFloat64();
							//std::cout << temp.perc_shares_out << std::endl;

						}
						else if (j == 2) {
							//std::cout << field.name() << std::endl;
							temp.eq_shares_out = field.getValueAsFloat64();
							//std::cout << temp.eq_shares_out << std::endl;
						}

						//std::cout	<< field.name()
						//			<< "\t\t" 
						//			<< field.getValueAsString() 
						//			<< std::endl;
						// output values to another variable
						//values.push_back(field.getValueAsFloat64());
					}

					data.push_back(temp);
				}
			}

			//std::cout << std::endl;


			Element fieldExceptions = security.getElement(
				FIELD_EXCEPTIONS);
			if (fieldExceptions.numValues() > 0) {
				std::cout << "FIELD\t\tEXCEPTION" << std::endl;
				std::cout << "-----\t\t---------" << std::endl;
				for (size_t k = 0; k < fieldExceptions.numValues(); ++k) {
					Element fieldException =
						fieldExceptions.getValueAsElement(k);
					Element errInfo = fieldException.getElement(
						ERROR_INFO);
					std::cout
						<< fieldException.getElementAsString(FIELD_ID)
						<< "\t\t"
						<< errInfo.getElementAsString(CATEGORY)
						<< " ( "
						<< errInfo.getElementAsString(MESSAGE)
						<< ")"
						<< std::endl;
				}
			}
		}
	}
}

void input::eventLoop(Session &session)
{
	bool done = false;
	while (!done) {
		Event event = session.nextEvent();
		if (event.eventType() == Event::PARTIAL_RESPONSE) {
			//std::cout << "Processing Partial Response" << std::endl;
			processResponseEvent(event);
		}
		else if (event.eventType() == Event::RESPONSE) {
			//std::cout << "Processing Response" << std::endl;
			processResponseEvent(event);
			done = true;
		}
		else {
			MessageIterator msgIter(event);
			while (msgIter.next()) {
				Message msg = msgIter.message();
				if (event.eventType() == Event::REQUEST_STATUS) {
					std::cout << "REQUEST FAILED: " << msg.getElement(REASON) << std::endl;
					done = true;
				}
				else if (event.eventType() == Event::SESSION_STATUS) {
					if (msg.messageType() == SESSION_TERMINATED ||
						msg.messageType() == SESSION_STARTUP_FAILURE) {
						done = true;
					}
				}
			}
		}
	}
}

void input::run(int argc, char **argv)
{
	if (!parseCommandLine(argc, argv)) return;

	SessionOptions sessionOptions;
	sessionOptions.setServerHost(d_host.c_str());
	sessionOptions.setServerPort(d_port);

	//std::cout << "Connecting to " + d_host + ":" << d_port << std::endl;
	Session session(sessionOptions);
	if (!session.start()) {
		std::cout << "Failed to start session." << std::endl;
		return;
	}
	if (!session.openService("//blp/refdata")) {
		std::cout << "Failed to open //blp/refdata" << std::endl;
		return;
	}
	sendRefDataRequest(session);

	// wait for events from session.
	try {
		eventLoop(session);
	}
	catch (Exception &e) {
		std::cerr << "Library Exception !!!"
			<< e.description()
			<< std::endl;
	}
	catch (...) {
		std::cerr << "Unknown Exception !!!" << std::endl;
	}

	session.stop();
}
