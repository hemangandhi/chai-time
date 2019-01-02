
typedef struct {
    char ** table;
    int rows, cols;
    TrieNode * words;
} WordSearch;

typedef struct _Solution{
    int start_row, start_col;
    int end_row, end_col;
    struct _Solution * next;
} Solution;

Solution * concat_solutions(Solution * left, Solution * right){
    if(left == NULL) return right;
    if(right == NULL) return left;

    Solution * t = left->next;
    left->next = right->next;
    right->next = t;
    return left;
}

Solution * singleton_solution(int sr, int sc, int er, int ec){
    Solution * s = malloc(sizeof(Solution));
    if(s){
        s->end_row = er;
        s->end_col = ec;
        s->start_row = sr;
        s->start_col = sc;
        s->next = NULL;
    }
    return s;
}

void free_solution(Solution * s){
    Solution * t = s->next;
    s->next = NULL;
    while(t != NULL){
        Solution * tt = t->next;
        free(t);
        t = tt;
    }
}

int in_bounds(WordSearch * ws, int row, int col){
    return 0 <= row && row < ws->rows && 0 <= cols && cols < ws->cols;
}

Solution * go_in_direction(WordSearch * ws, int row, int col, int dr, int dc){
    Solution * acc = NULL;
    TrieNode * tp = ws->words;
    for(int i = 0; in_bounds(ws, row + i * dr, col + i * dc) && (tp = childAt(ws->table[row + i * dr][col + i * dc], tp)) != NULL; i++){
        if(tp->words_ending_here > 0){
            acc = concat_solutions(acc, singleton_solution(row, col, row + i * dr, col + i * dc));
        }
    }
    return acc;
}

static int directions[8][2] = {
    {-1, -1},
    {0, -1},
    {1, -1},
    {-1, 0},
    {1, 0},
    {1, 1},
    {0, 1},
    {-1, 1}
};

Solution * solve(WordSearch * ws){
    Solution * acc = NULL;
    for(int r = 0; r < ws->rows; r++){
        for(int c = 0; c < ws->cols; c++){
            for(int d = 0; d < 8; d++){
                acc = concat_solutions(acc, go_in_direction(ws, r, c, directions[d][0], directions[d][1]));
            }
        }
    }
}
