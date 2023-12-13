#include "./hex.h"
void convertAndSaveToFile(FILE *inputFile, const char *outputFileName, int encode) {
    FILE *outputFile = fopen(outputFileName, encode ? "w" : "wb");
    if (outputFile == NULL) {
        perror("Error opening file");
        return;
    }
    
    if (encode == 1) {
        int ch;
        while ((ch = fgetc(inputFile)) != EOF) {
            fprintf(outputFile, "%02X", (unsigned char)ch);
        }
    } else {
        int ch1;
        while (fscanf(inputFile, "%02X|", (unsigned int *)&ch1) == 1) {
            fputc(ch1, outputFile);
        }
    }
    fclose(outputFile);
}

int main(int argc, char *argv[]) {
  // Check if the correct number of command line arguments is provided
  if (argc != 3) {
    fprintf(stderr, "Usage: %s <input_file_name> <output_file_name.hxt>\n",
            argv[0]);
    return 1;
  }

  // Get input file name from command line arguments
  const char *inputFileName = argv[1];

  // Open the input file
  FILE *inputFile = fopen(inputFileName, "rb");
  if (inputFile == NULL) {
    perror("Error opening input file");
    return 1;
  }

  // Get output file name from command line arguments
  const char *outputFileName = argv[2];

  // Check if the output file has a ".hxt" extension
  const char *extension = strrchr(outputFileName, '.');
  int encode = (extension != NULL && strcmp(extension, ".hxt") == 0);

  // Encode or decode based on the file extension
  convertAndSaveToFile(inputFile, outputFileName, encode);

  // Print a message based on the operation performed
  printf("Conversion %s complete. Check the file '%s' for the result.\n",
         encode ? "to hexadecimal" : "from hexadecimal", outputFileName);

  fclose(inputFile);

  return 0;
}
