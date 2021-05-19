#ifndef DTOP_RPC_WORKERCMDTYPE_H
#define DTOP_RPC_WORKERCMDTYPE_H

#include <string>

namespace dtop {
namespace worker {

enum WorkerCmdType { START, PAUSE, STOP, NOP };

std::string get_cmd_type_str(WorkerCmdType cmd_type);
WorkerCmdType get_cmd_type(const std::string& cmd_type_str);

}
}  // namespace dtop

#endif //DTOP_RPC_WORKERCMDTYPE_H
