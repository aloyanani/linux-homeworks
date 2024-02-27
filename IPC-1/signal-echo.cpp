#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <sys/ucontext.h>
#include <sys/types.h>
#include <pwd.h>

// Signal handler for SIGUSR1
void sigusr1_handler(int sig, siginfo_t *info, void *ucontext) {
    
    // Extract sender's PID
    pid_t sender_pid = info->si_pid;

    // Extract sender's UID and username
    uid_t sender_uid = info->si_uid;
    struct passwd *pwd = getpwuid(sender_uid);
    const char *sender_username =  pwd->pw_name;

    // Extract register values
    ucontext_t *context = (ucontext_t *)ucontext;
    unsigned long eip = context->uc_mcontext.gregs[REG_RIP];
    unsigned long eax = context->uc_mcontext.gregs[REG_RAX];
    unsigned long ebx = context->uc_mcontext.gregs[REG_RBX];

    // Print the information
    std::cout << "Received a SIGUSR1 signal from process " << sender_pid << " executed by " << sender_uid << " (" << sender_username << ")." << std::endl;
    std::cout << "State of the context: EIP = " << eip << ", EAX = " << eax << ", EBX = " << ebx << "." << std::endl;
}

int main() {
    // Set up signal handling for SIGUSR1
    struct sigaction action;
    memset(&action, 0, sizeof(action));
    action.sa_flags = SA_SIGINFO;
    action.sa_sigaction = sigusr1_handler;

    // Register the signal handler
    int sig_result = sigaction(SIGUSR1, &action, NULL);

    // Check if the signal registration was successful
    if (sig_result < 0) {
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }
 
    // Print the PID of the process
    std::cout << "PID: " << getpid() << std::endl;

    // Enter an infinite loop with a sleep delay
    while (true) {
        sleep(1);
    }

    return 0;
}
