#include <stdio.h>
#include <math.h>



int main(int argc, char const *argv[]) {
	research("arh02/input.file", "arh02/output.file");


	return 0;
}

void research(char *filename_research, char *filename_report) {
	FILE *file_research = open_file(filename_research);
	FILE *file_report = create_file(filename_report);
	int const total_bytes = get_total_bytes(file_research);
	float entropy = 0.0f;
	float array_frequency[256] = {[0 ... 255] = 0};

	write_filename(file_report, filename_report);
	write_total_bytes(file_report, total_bytes);

	save_array_frequency(array_frequency, total_bytes);

	write_frequency(file_report, array_frequency);

	entropy = get_entropy(array_frequency, array_bytes, total_bytes);
	write_entropy(file_report, entropy);

	fclose(file_research);
	fclose(file_report);
}

FILE* open_file(char *filename) {
	FILE *file = NULL;

	file = fopen(filename, "rb");
	if(file == NULL) {
		printf("Error! Couldn't open the file: %s\n", filename);
		exit(-1);
	}
	return file;
}

FILE* create_file(char *filename) {
	FILE *file = NULL;

	file = fopen(filename, "wb+");
	if(file == NULL) {
		printf("Error! Couldn't open the file: %s\n", filename);
	}
	return file;
}

int get_total_bytes(FILE *file) {
	const long int current_position = ftell(file);
	fseek(file, 0L, SEEK_END);
	int size = ftell(file);
	fseek(file, current_position, SEEK_SET);
	return size;
}

void write_filename(FILE *file, char *filename) {
	fprintf(file, "%s\n", filename);
}

void write_total_bytes(FILE *file, const int total_bytes) {
	fprintf(file, "%d\n", total_bytes);
}

void save_array_frequency(FILE *file, float *array_frequency, int *array_bytes, const int total_bytes) {
	int symbol = 0;
	while((symbol = getc(file)) != EOF) {
		array_bytes[symbol]++;
	}

	for(int i=0; i<256; ++i) {
		array_frequency[i] = (float)array_bytes / (float)total_bytes;
	}
}

void write_frequency(FILE *file, float *array) {
	for(int i=0; i<256; ++i) {
		fprintf(file, "%d\t%f\n", i, array[i]);
	}
}