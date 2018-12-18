#include <stdlib.h>
#include "uf.h"

struct uf_ {
  int size;
  int* parents;
  unsigned char* ranks;
};

UF *uf_create(int n) {
  UF *s = (UF*)malloc(sizeof(UF));
  s->size = n;
  s->parents = (int*)malloc(n*sizeof(int));
  s->ranks = (unsigned char*)malloc(n*sizeof(unsigned char));

  for (int i = 0; i < n; i += 1) {
    s->parents[i] = i;
    s->ranks[i] = 0;
  }

  return s;
}

int uf_find(UF* s, int x) {
  int p  = s->parents[x];  
  int gp = s->parents[p];

  while (p != gp) {
    s->parents[x] = gp;
    x = gp;
    p = s->parents[x];
    gp = s->parents[p];
  }

  return p;
}

void uf_union(UF* s, int x, int y) {  
  x = uf_find(s, x);
  y = uf_find(s, y);
  
  unsigned char rank_x, rank_y;
  
  rank_x = s->ranks[x];
  rank_y = s->ranks[y];
  if (rank_x < rank_y) {
    s->parents[x] = y;
  }
  else {
    s->parents[y] = x;
    if (rank_x == rank_y) {
      s->ranks[x] += 1;
    }
  }
}

void uf_free(UF* s) {
  free(s->parents);
  free(s->ranks);
  free(s);
}
