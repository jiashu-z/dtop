#ifndef DTOP_RPC_FUTURE_H
#define DTOP_RPC_FUTURE_H

#include <string>

namespace dtop {
namespace worker {

enum FutureType {
		MEM_USAGE, MEM_PER_PROC
};

class Future {
 public:
	explicit Future(FutureType id, std::string label, std::string description);

	/**
	 * @brief The future id, used for query process.
	 *        Duplication is NOT allowed.
	 */
	const FutureType id;

	/**
	 * @brief The label that declare this future
	 */
	const std::string label;

	/**
	 * @brief The description of this future.
	 */
	const std::string desc;

  std::string to_string() const;
};

}  // namespace worker
}  // namespace dtop

#endif //DTOP_RPC_FUTURE_H
