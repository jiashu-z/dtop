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
	mkfifo("/tmp/myfifo", 0666);
	int fd = open("/tmp/myfifo", O_RDWR | O_NONBLOCK);
	malloc_free_msg_t malloc_msg;
	void *buf = (void *)&malloc_msg;
	int i = 0;
	while (true) {
		malloc_msg.pid = i;
		malloc_msg.size = i;
		malloc_msg.addr = i;
		malloc_msg.caller = i;
		write(fd, buf, 40);
		printf("counter: %d\n", ++i);
		sleep(5);
	}
}