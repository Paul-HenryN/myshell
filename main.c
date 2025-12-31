#include <stdio.h>
#include <string.h>

int main(void) {
  char input[256];

  do {
    printf("myshell> ");
    char *res = fgets(input, sizeof(input), stdin);

    if (res == NULL) {
      break;
    }

    int len = strlen(input);

    if (input[len - 1] == '\n') {
      input[len - 1] = '\0';
    }

    printf("%s\n", input);
  } while (!(strlen(input) == 4 && strncmp(input, "exit", 4) == 0));

  return 0;
}
