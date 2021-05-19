#include "WorkerCmdType.h"

std::string dtop::worker::get_cmd_type_str(WorkerCmdType cmd_type) {
	switch (cmd_type) {
		case START: return "START";
		case PAUSE: return "PAUSE";
		case STOP: return "STOP";
		case NOP: return "NOP";
	}
}

dtop::worker::WorkerCmdType dtop::worker::get_cmd_type(const std::string& cmd_type_str) {
	if (cmd_type_str == "START") {
		return START;
	} else if (cmd_type_str == "PAUSE") {
		return PAUSE;
	} else if (cmd_type_str == "STOP") {
		return STOP;
	} else {
		return NOP;
	}
}