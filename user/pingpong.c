#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"

int main(int argc, char *argv[]) {
  // 创建管道
  int fd1[2];
  int fd2[2];
  if (pipe(fd1) < 0 || pipe(fd2) < 0) {
    printf("Create pipe fail!\n");
    exit(1);
  }

  // 创建子进程
  int pid;
  if ((pid = fork()) < 0) {
    printf("Fork fail!\n");
    exit(1);
  } else if (pid > 0) {
    // 父进程
    close(fd1[0]);
    close(fd2[1]);
    char temp = 't';
    write(fd1[1], &temp, 1);

    int n;
    while ((n = read(fd2[0], &temp, 1)) > 0) {
      printf("%d: received pong\n", getpid());
      break;
    }
  } else {
    // 子进程
    close(fd1[1]);
    close(fd2[0]);
    char temp;
    int n;
    while ((n = read(fd1[0], &temp, 1)) > 0) {
      printf("%d: received ping\n", getpid());
      write(fd2[1], &temp, 1);
    }
  }

  exit(0);
}
