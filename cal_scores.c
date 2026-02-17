#define MAX_ELEMENTS 100
int scores[MAX_ELEMENTS]; // 자료구조

int get_max_score(int n) 
{
  int i, largest;
  largest = scores[0]; 
  for (i = 1; i<n; 1++) {
    if (scores[i] > largest) { 
      largest = scores[i];
    }
  }
return largest;
}
