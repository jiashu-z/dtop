#include <asm-generic/errno-base.h>
#include <cerrno>
#include <fcntl.h>
#include <malloc.h>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

/* Prototypes for our hooks */
static void my_init_hook(void);
static void *my_malloc_hook(size_t, const void *);
static void my_free_hook(void *ptr, const void *);

/* Variables to save original hooks */
static void *(*old_malloc_hook)(size_t, const void *);
static void (*old_free_hook)(void *ptr, const void *);

/* Override initializing hook from the C library */
void (*__malloc_initialize_hook)(void) = my_init_hook;

static void
my_init_hook(void)
{
  old_malloc_hook = __malloc_hook;
  __malloc_hook = my_malloc_hook;
  old_free_hook = __free_hook;
  __free_hook = my_free_hook;
}

struct malloc_free_msg_t {
  char mode;
  int pid;
  int64_t size;
  int64_t addr;
  int64_t caller;
};

#define malloc_msg_size sizeof(malloc_free_msg_t)
#define mode_malloc 0
#define mode_free 1

static void *
my_malloc_hook(size_t size, const void *caller)
{
  /* Restore all old hooks */
  __malloc_hook = old_malloc_hook;
  __free_hook = old_free_hook;
  void *result;
  
  struct malloc_free_msg_t malloc_msg{};


  printf("Hello world!");
  /* Call recursively */
  result = malloc(size);
	int pid = getpid();

  std::string myfifo = "/tmp/fifo" + std::to_string(pid);
  int fd = open(myfifo.c_str(), O_RDWR | O_NONBLOCK);
  printf("fd: %d\n", fd);
  bool fifo_opened = true;
  while (fd == -1) {
    if (!fifo_opened) {
      break;
    }
    int err = errno;
    printf("err: %d\n", err);
    fifo_opened = false;
    if (err == ENOENT) {
      printf("handling\n");
      // The fifo does not exist.
      mkfifo(myfifo.c_str(), 0666);
      fd = open(myfifo.c_str(), O_RDWR | O_NONBLOCK);
    }
    else {
      break;
    }
  }

  if (fifo_opened) {
    printf("opened");
    malloc_msg.mode = mode_malloc;
    malloc_msg.pid = pid;
    malloc_msg.size = (int64_t)size;
    malloc_msg.addr = (int64_t)result;
    malloc_msg.caller = (int64_t)caller;
    void *buf = &malloc_msg;
    write(fd, buf, malloc_msg_size);
    close(fd);
  }

  printf("goodbye!");

  /* Save underlying hooks */
  old_malloc_hook = __malloc_hook;
  old_free_hook = __free_hook;

  /* Restore our own hooks */
  __malloc_hook = my_malloc_hook;
  __free_hook = my_free_hook;

  return result;
}

static void 
my_free_hook(void *ptr, const void *caller)
{
  /* Restore all old hooks */
  __malloc_hook = old_malloc_hook;
  __free_hook = old_free_hook;
  struct malloc_free_msg_t malloc_msg{};



  /* Call recursively */
  free(ptr);
  int pid = getpid();

  std::string myfifo = "/tmp/fifo" + std::to_string(pid);
  int fd = open(myfifo.c_str(), O_RDWR | O_NONBLOCK);
  bool fifo_opened = true;
  while (fd == -1) {
    if (!fifo_opened) {
      break;
    }
    int err = errno;
    fifo_opened = false;
    if (err == ENOENT) {
      // The fifo does not exist.
      mkfifo(myfifo.c_str(), 0666);
      fd = open(myfifo.c_str(), O_RDWR | O_NONBLOCK);
    }
    else {
      break;
    }
  }

  if (fifo_opened) {
    malloc_msg.mode = mode_free;
    malloc_msg.pid = pid;
    malloc_msg.size = 0;
    malloc_msg.addr = (int64_t)ptr;
    malloc_msg.caller = (int64_t)caller;
    void *buf = &malloc_msg;
    write(fd, buf, malloc_msg_size);
    close(fd);
  }

  /* Save underlying hooks */
  old_malloc_hook = __malloc_hook;
  old_free_hook = __free_hook;

  /* Restore our own hooks */
  __malloc_hook = my_malloc_hook;
  __free_hook = my_free_hook;
}
