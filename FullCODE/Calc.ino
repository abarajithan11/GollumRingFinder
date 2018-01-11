int alignErrorCalc(int targetAngle)
{
  readCompassAvg();
  return targetAngle-heading;
}

float getMedian(float * arr, int n, int k)                     //Returns the k-average of n-median values
{
  if (n < 5) return -1;
  
  sortArray(arr, n);
  float x = 0;
  int k1 = (n-k)/2;
  int k2 =  (n+k)/2;
  for (int i = k1 ; i < k2 ; i++)      //Total of k values
    x += arr[i];
  return x/k;
}
