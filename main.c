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

void
timer_demo() {
  int ret;

  struct sigevent evp;
  memset(&evp, 0, sizeof(struct sigevent));

  timer_t timer;
  memset(&timer, 0, sizeof(timer_t));

  evp.sigev_value.sigval_ptr = (void *)&global_point;
  evp.sigev_notify = SIGEV_THREAD;
  evp.sigev_notify_function = timer_callback;

  ret = timer_create(CLOCK_REALTIME, &evp, &timer);

  if(ret < 0) {
    printf("Timer creation failed, errno: %d\n", errno);
    exit(0);
  }

  struct timerspec ts;

  ts.it_value.tv_sec = 5;
  ts.it_value.tv_usec = 0;

  ts.it_interval.tv_sec = 0;
  ts.it_interval.tv_usec = 0;

  ret = timer_settime(timer, 0, &ts, NULL);

  if(ret < 0) {
    printf("Timer start failed, errno: %d\n", errno);
    exit(0);
  } else {
    print_current_sys_time();
    printf("Timer alarmed succesfully\n");
  }
}

int main(int argc, char **argv) {
  timer_demo();

  //pause();

  return 0;
}
