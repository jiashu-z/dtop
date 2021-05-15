#include "Future.h"
#include <sstream>

dtop::worker::Future::Future(FutureType id, std::string label, std::string description) :
				id(id), label(std::move(label)), desc(std::move(description)) {}

std::string dtop::worker::Future::to_string() const {
	std::ostringstream oss;
	oss << "Future" << id << "[" << label << "]: " << desc;
	return oss.str();
}
