// Elay Ben Yehoshua 214795668
#include <stdio.h>
#include <malloc.h>

typedef unsigned char uchar;

typedef struct cache_line_s {

    uchar valid;
    uchar frequency;
    long int tag;
    uchar *block;
} cache_line_t;

typedef struct cache_s {
    uchar s;
    uchar t;
    uchar b;
    uchar E;
    cache_line_t **cache;
} cache_t;

void print_cache(cache_t cache) {

    int S = 1 << cache.s;
    int B = 1 << cache.b;

    for (int i = 0; i < S; i++) {
        printf("Set %d\n", i);
        for (int j = 0; j < cache.E; j++) {

            printf("%1d %d 0x%0*lx ", cache.cache[i][j].valid,
                   cache.cache[i][j].frequency, cache.t,
                   cache.cache[i][j].tag);

            for (int k = 0; k < B; k++) {
                printf("%02x ", cache.cache[i][j].block[k]);
            }
            puts("");
        }
    }
}

cache_t initialize_cache(uchar s, uchar t, uchar b, uchar E) {
    cache_t c1;

    c1.t = t;
    c1.s = s;
    c1.b = b;
    c1.cache = NULL;
    c1.E = E;

    //S = number pf sets
    int S = 1 << s;
    //B = number of blocks
    int B = 1 << b;

    c1.cache = (cache_line_t**) malloc(E * sizeof(cache_line_t*));
    int i = 0;
    while(i < S){
        //ini the sets
        c1.cache[i] = (cache_line_t*) malloc(sizeof(cache_line_t) * c1.E);
        int j = 0;
        //init the lines per set
        while(j < E) {
            c1.cache[i][j].valid = 0;
            c1.cache[i][j].frequency = 0;
            c1.cache[i][j].tag = 0;
            c1.cache[i][j].block = malloc(B * sizeof(uchar));
            for (int k = 0; k < B; ++k) {
                c1.cache[i][j].block[k] = 0;
            }
            j++;
        }
        i++;
    }
    return c1;
}

uchar read_byte(cache_t cache, uchar *start, long int off) {

    //B = number of blocks
    int B = 1 << cache.b;
    //S = number of blocks
    int S= 1 << cache.s;
    int nig = off;
    int tag1 = nig >> (cache.s + cache.b);
    int block1 = off & (B - 1);
    nig = (nig >> cache.b);
    int set1 = nig & (S - 1);

    for (int i = 0; i < cache.E; i++) {
        if (cache.cache[set1][i].valid &&
         cache.cache[set1][i].tag == tag1)
        {
            // tag was found
            if(cache.cache[set1][i].block[block1] == start[off])
            {
                //block was found
                cache.cache[set1][i].frequency++;
            }
            else{
                cache.cache[set1][i].frequency = 1;
                //run over the line
                for (int j = 0; j < B; ++j) {
                    cache.cache[set1][i].block[j] = start[off - block1 + j];
                }
            }
            return cache.cache[set1][i].block[block1];
        }
    }
    //tag wasn't found, so we look for empty line
    for (int i = 0; i < cache.E; i++) {
        if (cache.cache[set1][i].valid == 0){
            cache.cache[set1][i].frequency = 1;
            cache.cache[set1][i].valid = 1;
            cache.cache[set1][i].tag = tag1;
            //run over the line
            for (int j = 0; j < B; ++j) {
                cache.cache[set1][i].block[j] = start[off - block1 + j];
            }
            return cache.cache[set1][i].block[block1];
        }
    }

    //no line was empty, so we run over the minFreq line
    // find the min frequency
    int minFreq = 10000000;
    for (int i = 0; i < cache.E; i++) {
        if (cache.cache[set1][i].frequency < minFreq) {
            minFreq = cache.cache[set1][i].frequency;
        }
    }

    for (int i = 0; i < cache.E; i++) {
        if (cache.cache[set1][i].frequency == minFreq) {
            cache.cache[set1][i].valid = 1;
            cache.cache[set1][i].frequency = 1;
            cache.cache[set1][i].tag = tag1;
            //run over the line
            for (int j = 0; j < B; ++j) {
                cache.cache[set1][i].block[j] = start[off - block1 + j];            }
            return cache.cache[set1][i].block[block1];
        }
    }

    return 0;
}

uchar write_byte(cache_t cache, uchar *start, long int off, uchar new) {
    start[off] = new;
    return read_byte(cache,start,off);
}


int main() {
    int n;

    printf("Size of data: ");
    scanf("%d", &n);

    uchar *mem = malloc(n);

    printf("Input data >>");

    for (int i = 0; i < n; i++)
        scanf("%hhd", mem + i);

    int s, t, b, E;

    printf("s t b E:");
    scanf("%d %d %d %d", &s, &t, &b, &E);

    cache_t cache = initialize_cache(s, t, b, E);

    while (1) {

        scanf("%d", &n);
        if (n < 0)
            break;
        read_byte(cache, mem, n);

    }

    puts("");
    print_cache(cache);
    free(mem);

}