#ifndef Parser
typedef struct {
  float *vertices;
  int size;
} VertexArray;

VertexArray parseSTL(char *path);
#endif // !Parser
