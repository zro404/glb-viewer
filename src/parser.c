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
  va.vertices = (float *)malloc(va.size * 18 * sizeof(float));
  va.indices = (unsigned int *)malloc(va.size * 3 * sizeof(unsigned int));
  va.vertCount = 0;

  float normal[3];
  float vert[3];

  for (int i = 0; i < va.size; i++) {
    fread(&normal, 4, 3, fptr);
    for (int j = 0; j < 3; j++) {
      fread(&vert, 4, 3, fptr);

      int idx = -1;
      for (int k = 0; k < va.vertCount * 6; k += 6) {
        if (va.vertices[k] == vert[0] && va.vertices[k + 1] == vert[1] &&
            va.vertices[k + 2] == vert[2]) {
          idx = k;
          break;
        }
      }

      if (idx > -1) {
        va.vertices[idx + 3] += normal[0];
        va.vertices[idx + 4] += normal[1];
        va.vertices[idx + 5] += normal[2];
      } else {
        idx = (va.vertCount++) * 6;
        memcpy(va.vertices + idx, vert, 3 * sizeof(float));
        memcpy(va.vertices + idx + 3, normal, 3 * sizeof(float));
      }

      va.indices[i * 3 + j] = idx/6;
    }
    fseek(fptr, 2, SEEK_CUR);
  }

  return va;
}
