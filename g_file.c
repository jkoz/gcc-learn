#include <stdio.h>
#include <stdlib.h>

int main() {
	char line[100];    /* Line from the keyboard */
	int count, total;  /* Number of entries & total value */
	int scan_count;    /* Number of parameters scanned */

	fgets(line, sizeof(line), stdin);

	scan_count = sscanf(line,"%d %d", &count, &total);
	if (scan_count != 0) {
		printf("sscanf failed");
		return 1;
	}

	switch (scan_count) {
		case EOF:
		case 0:
			printf("Didn't find any number\n");
			break;
		case 1:
			printf("Found 'count'(%d), but not 'total'\n", count);
			break;
		case 2:
			printf("Found both 'count'(%d) and 'total'(%d)\n", count, total);
			break;
		default:
			printf("This should not be possible\n");
			break;
	}
}
