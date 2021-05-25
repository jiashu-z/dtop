#include <asm-generic/errno-base.h>
#include <cerrno>
#include <fcntl.h>
#include <malloc.h>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

struct malloc_free_msg_t {
		int64_t mode;
		int64_t pid;
		int64_t size;
		int64_t addr;
		int64_t caller;
};

int main() {
//	mkfifo("/tmp/myfifo", 0666);
	int fd = open("/tmp/myfifo", O_RDONLY | O_NONBLOCK);
	printf("fd: %d\n", fd);
	int i = 0;
	struct malloc_free_msg_t malloc_msg;
	void *buf = (void *)&malloc_msg;
	while (true) {
		int ret = read(fd, buf, 40);
		if (ret == -1 || ret == 0) {
			break;
		}
		++i;
		printf("pid: %lld, size: %lld, addr: %p, caller: %p\n", malloc_msg.pid, malloc_msg.size, malloc_msg.addr, malloc_msg.caller);
	}
	close(fd);
	printf("i: %d\n", i);
	return 0;
}