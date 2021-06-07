#include <time.h>
#include <signal.h>
#include <stdio.h>
#include <memory.h>
#include <errno.h>
#include <unistd.h>

typedef struct point_ {
  int x;
  int y;
} Point;

Point global_point = {10, 20};

static void
print_current_sys_time() {
  time_t t;
  time(&t);

  printf("%s ", ctime(&t));
}

void
timer_callback(union sigval arg) {
  print_current_sys_time();

  Point* p = (Point *)arg.sigval_ptr;

  printf("Coorinates: [%d %d]\n", p->x, p->y);
}

int main(int argc, char **argv) {
  //print_current_sys_time();

  //pause();

  return 0;
}
