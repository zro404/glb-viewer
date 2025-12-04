#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
  // va.vertices = (float *)malloc((va.size * 12) * sizeof(float));
  va.vertices = (float *)malloc((va.size * 18) * sizeof(float));

  float normal[3];

  for (int i = 0; i < va.size; i++) {
    // fseek(fptr, 12, SEEK_CUR); // Skip Normal data
    // fread(va.vertices + (i * 9), 4, 9, fptr);
    // fread(va.vertices + (i * 12), 4, 12, fptr);

    fread(&normal, 4, 3, fptr);
    fread(va.vertices + (i * 18), 4, 3, fptr);
    memcpy(va.vertices + (i * 18) + 3, normal, 3 * sizeof(float));
    fread(va.vertices + (i * 18) + 6, 4, 3, fptr);
    memcpy(va.vertices + (i * 18) + 9, normal, 3 * sizeof(float));
    fread(va.vertices + (i * 18) + 12, 4, 3, fptr);
    memcpy(va.vertices + (i * 18) + 15, normal, 3 * sizeof(float));
    fseek(fptr, 2, SEEK_CUR);
  }

  // for (int i = 0; i < va.size*18; i++) {
  //   float n = *(va.vertices+i);
  //   if(n>=0) printf(" ");
  //   printf("%.2f, ", n);
  //   if((i+1)%6 == 0) {
  //     printf("\n");
  //   }
  // }

  return va;
}
