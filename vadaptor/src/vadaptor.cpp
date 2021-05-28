#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cassert>

static int wait_time;

int main(int argc, char **argv) {
  std::cout << "Please specify your maximum wait time." << std::endl;
  std::cin >> wait_time;
  assert(wait_time > 0);
  if (argc == 0) {
    std::cout << "You did not provide any executable!" << std::endl;
  }
  char *name = argv[1];
  int pid = fork();
  if (pid == 0) {
    argv[0] = new char[9];
    char *valgrind = argv[0];
    valgrind[0] = 'v';
    valgrind[1] = 'a';
    valgrind[2] = 'l';
    valgrind[3] = 'g';
    valgrind[4] = 'r';
    valgrind[5] = 'i';
    valgrind[6] = 'n';
    valgrind[7] = 'd';
    valgrind[8] = '\0';
    for (int i = 0; i < 9; ++i) {
      std::cout << argv[i] << std::endl;
    }
    execvp("valgrind", argv);
  }
  else {
    int pid1 = fork();
    if (pid1 == 0) {
      sleep(wait_time);
      kill(pid, SIGINT);
    }
    else {
      wait(0);
    }
  }
  return 0;
}
