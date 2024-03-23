/*
  badSleep
 */
#include <signal.h>
#include <unistd.h>

static void sig_alrm(int signo){}

unsigned int toDream(unsigned int nsecs) {
    signal(SIGALRM, sig_alrm);
    alarm(nsecs); /* start the timer */
    pause();      /* next caught signal wakes us up */ 
    return alarm(0); // turn off timer, return unslept time 
}
