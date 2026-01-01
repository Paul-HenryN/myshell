#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void) {
  char input[256];

  while (1) {
    printf("myshell> ");
    char *res = fgets(input, sizeof(input), stdin);

    if (res == NULL) {
      break;
    }

    int len = strlen(input);

    if (input[len - 1] == '\n') {
      input[len - 1] = '\0';
      len--;
    }

    if (len == 4 && strcmp(input, "exit") == 0) {
      break;
    }

    char *tokens[20];
    int ntokens = 0;

    char *token = strtok(input, " ");

    if (token == NULL) {
      continue;
    }
    while (token != NULL) {
      tokens[ntokens] = token;
      token = strtok(NULL, " ");
      ntokens++;
    }
    tokens[ntokens] = NULL;

    pid_t pid, w;
    int wstatus;

    pid = fork();

    switch (pid) {
    case -1:
      perror("fork failed");
      exit(EXIT_FAILURE);
    case 0:
      execvp(tokens[0], tokens);
      perror("");
      _exit(EXIT_FAILURE);
    default:
      do {
        w = waitpid(pid, &wstatus, WUNTRACED);

        if (w == -1) {
          perror("waitpid");
          exit(EXIT_FAILURE);
        }
      } while (!WIFEXITED(wstatus));
    }
  };

  return 0;
}
