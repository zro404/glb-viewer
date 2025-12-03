#include "parser.h"

#include <stdio.h>
#include <stdlib.h>

VertexArray parseSTL(char *path) {
  FILE *fptr = fopen(path, "r");
  if (fptr == NULL) {
    printf("Could not open file: %s !", path);
    exit(-1);
  }

  // Skip header - 80 bytes
  fseek(fptr, 80, SEEK_CUR);

  VertexArray va;
  fread(&va.size, 4, 1, fptr); // No. of Triangular Faces
  va.vertices = (float *)malloc((va.size * 12) * sizeof(float));

  for (int i = 0; i < va.size; i++) {
    fseek(fptr, 12, SEEK_CUR); // Skip Normal data
    fread(va.vertices + (i * 9), 4, 9, fptr);
    fseek(fptr, 2, SEEK_CUR);
  }

  return va;
}
