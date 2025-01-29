int *sorted(int n) {
    int *array = (int*)malloc(n*sizeof(int));
    // this ensures we reset the random seed
    // to get truly random ints
    srand(time(NULL)); 
    int nxt = 0;
    for (int i = 0; i < n ; i++) {
        nxt += (rand() % (n*10))+1;
        array[i] = nxt;
    }
    return array;
}