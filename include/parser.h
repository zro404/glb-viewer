#ifndef Parser
typedef struct {
  float *vertices;
  unsigned int *indices;
  int size;
  int vertCount;
} VertexArray;

VertexArray parseSTL(char *path);
#endif // !Parser
