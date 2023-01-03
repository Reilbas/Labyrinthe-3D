#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	if(argc != 3 + 1) {
		printf("Correct usage: LevelCreator width length file %d", argc);
	}
    FILE* file_ptr = fopen(argv[3], "a");
	int w = atoi(argv[1]);
	int l = atoi(argv[2]);
	for(int i = 0; i < 10; i++) {
		for(int j = 0; j < 10; j++) {
			if(i == 0 || j == 0 || i == 9 || j == 9)
				fprintf(file_ptr, "X");
			else if(i == 1 && j == 1)
				fprintf(file_ptr, "P");
			else {
				int r = rand() % 10;
				if(r >= 8)
					fprintf(file_ptr, "X");
				else if(r == 7)
					fprintf(file_ptr, "I");
				else 
					fprintf(file_ptr, "O");
			}
		}	
		fprintf(file_ptr, "\n");
	}
    fclose(file_ptr);

    return 0;
}