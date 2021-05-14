#ifndef DEMO_GRPC_WORKERCONFIG_H
#define DEMO_GRPC_WORKERCONFIG_H

#define DEFAULT_CACHE_TIME 100  // ms

namespace dtop {
namespace worker {

class WorkerConfig {
 public:
  long long cache_time = DEFAULT_CACHE_TIME;
};

}  // namespace worker
}  // namespace dtop

#endif  // DEMO_GRPC_WORKERCONFIG_H
