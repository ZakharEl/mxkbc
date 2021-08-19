#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <linux/input.h>


/* https://www.kernel.org/doc/html/latest/input/event-codes.html */
#define INPUT_VAL_PRESS 1
#define INPUT_VAL_RELEASE 0
#define INPUT_VAL_REPEAT 2


int read_event(struct input_event *event) {
	return fread(event, sizeof(struct input_event), 1, stdin) == 1;
}


void write_event(const struct input_event *event) {
	if (fwrite(event, sizeof(struct input_event), 1, stdout) != 1)
		exit(EXIT_FAILURE);
}


int main(int argc, char *argv[]) {
	struct input_event input;
	setbuf(stdin, NULL), setbuf(stdout, NULL);
	while (read_event(&input)) {
		/* make mouse and touchpad events consume pressed taps */
		if (input.type == EV_MSC && input.code == MSC_SCAN) continue;

		/* forward anything that is not a key event, including SYNs */
		if (input.type != EV_KEY) {
			write_event(&input);
			continue;
		}

		switch (input.value) {
			case INPUT_VAL_PRESS:
				break;
			case INPUT_VAL_RELEASE:
				break;
			case INPUT_VAL_REPEAT:
				/* linux console, X, wayland handles repeat */
				break;
			default:
				fprintf(stderr, "unexpected .value=%d .code=%d, doing nothing",
				        input.value,
				        input.code);
				break;
		}
	}
}