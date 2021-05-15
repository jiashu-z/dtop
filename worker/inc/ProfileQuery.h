#ifndef DTOP_RPC_PROFILEQUERY_H
#define DTOP_RPC_PROFILEQUERY_H

#include <message.grpc.pb.h>

namespace dtop {
namespace worker {

	class ProfileQuery {
	public:
		std::unordered_map<std::string, std::string> req_map;

		/**
		 * @brief Decode request from protobuf
		 *
		 * @param request
		 * @return
		 */
		bool decode(const FetchRequestMessage* request);

		std::string to_string();
	};

}  // namespace worker
}  // namespace dtop

#endif  // DTOP_RPC_PROFILEQUERY_H
