#include <stdio.h>
#include <string.h>

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
    while (token != NULL) {
      tokens[ntokens] = token;
      token = strtok(NULL, " ");
      ntokens++;
    }

    for (int i = 0; i < ntokens; i++) {
      printf("->%s", tokens[i]);
    }

    printf("\n");
  };

  return 0;
}
