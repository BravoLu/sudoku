#include "specific.h"
int *tmp_ptr;

bool is_valid_ch(char alpha){
    return  alpha == '1' || alpha == '2' || alpha == '3' || \
            alpha == '4' || alpha == '5' || alpha == '6' || alpha == '7' || \
            alpha == '8' || alpha == '9';
}

sudoku* sudoku_init(void){
    int i, j, k;
    int col_idx, row_idx, box_idx, peer_idx;
    int index, box_r, box_c;
    int r, c;
    sudoku* s = (sudoku*) malloc(sizeof(sudoku));
    for(i = 0; i < GRIDSIZE ; i++) {
        for(j = 0; j < GRIDSIZE; j++) {
            col_idx = 0;
            row_idx = 0;
            box_idx = 0;
            peer_idx = 0;
            
            /* initialize value */
            for (k = 0 ; k < GRIDSIZE+1; k++){
                s->value[i*GRIDSIZE+j][k] = true;
            }
            index = i*GRIDSIZE + j;
            /* initialize */ 
            s->cur[index] = '.';
            /* construct cols */
            for (k = 0 ; k < GRIDSIZE; k++){
                if (k != i) {
                    s->cols[index][col_idx++] = k*GRIDSIZE + j;
                    s->peers[index][peer_idx++] = k*GRIDSIZE + j;
                }
            } 
            /* construct rows */
            for (k = 0; k < GRIDSIZE; k++) {
                if (k != j) {
                    s->rows[index][row_idx++] = i*GRIDSIZE + k;
                    s->peers[index][peer_idx++] = i*GRIDSIZE + k;
                }
            }
            /* construct box 
             box pos: (box_r, box_c) */
            box_r = i / 3 * UNITS;
            box_c = j / 3 * UNITS;
            for (r = 0; r < UNITS; r++) {
                for (c = 0; c < UNITS; c++) {
                    int tmp = (box_r + r) * GRIDSIZE + ( box_c + c);
                    if (tmp != (i*GRIDSIZE + j)){
                        s->boxes[index][box_idx++] = tmp;
                    }
                    if ((box_r + r) != i && (box_c + c) != j) {
                        s->peers[index][peer_idx++] = tmp; 
                    }
                }
            }
        }
    }
    return s;
}

void print_values(sudoku* s, int x, int y) {
    int i;
    for(i = 0; i < GRIDSIZE; i++ ) {
        if(s->value[y*GRIDSIZE+x][i]){
            printf("true ");
        }
        else{
            printf("false ");
        }
    }
    printf("\n");

}

/* 当num==1时，可以通过assign_value来获取唯一的额一个value为true的idx */
int sudoku_value_num(sudoku* s, int idx, int* assign_value) {
    int num = 0;
    int i;
    for (i = 1; i < GRIDSIZE+1; i++){
        if(s->value[idx][i]){
            num ++;
            *assign_value = i;
        } 
    }
    return num;
}

/* 
   将value[idx][v]设置为false 
   若当前value[idx][v]已经为false, 直接返回true；
   计算当前idx下，value为true的个数，表示这个idx下，有多少种选择；
   若没有选择，则返回false；
   若只有一种选择，则返回只能将cur[idx]设置为当前value[idx][v]=true的v值；然后消除对应peers
   下标的value的值为false
 */
bool sudoku_eliminate(sudoku* s, int idx, squaretype v) {
    int v2;
    int assign_value;
    int val_num = 0;
    int i, num, index, tmp_val, col_idx, box_idx, peer_idx, row_idx;
    tmp_ptr = (int*) malloc(sizeof(int));
    /* 已经被消除，即value已经设置为false */
    if (!s->value[idx][v]) {
        free(tmp_ptr);
        return true;
    } 
    s->value[idx][v] = false;
    val_num = sudoku_value_num(s, idx, tmp_ptr);
    assign_value = *tmp_ptr;
    free(tmp_ptr);
    if ( 0 == val_num) {
        return false;
    } else if ( 1 == val_num ) {
        s->cur[idx] = assign_value + '0';
        v2 = s->cur[idx] - '0';
        for (i = 0; i < PEERSIZE; i++){
            peer_idx = s->peers[idx][i];
            if (!sudoku_eliminate(s, peer_idx, v2)) {
                return false;
            }
        }
    }
    /* row */
    /* 如果被消除的值v在 row/col/box (c1, c2, c3, c4, ...) 中的可选值内（value=true）则， */
    /* 因为消除了idx位置的v，所以要在unit的三个位置找一个可以放v的地方，如果这个地方是确定的，就方v */
    num = 0;
    for(i = 0 ; i < GRIDSIZE - 1; i++){
        row_idx = s->rows[idx][i];
        if (s->value[row_idx][v]) {
            num ++;
            index = row_idx;
            tmp_val = v;
        } 
    }
    /* printf("num:%d\n", num); */
    /* print_values(s, idx%GRIDSIZE, idx/GRIDSIZE); */
    if (num == 0) {
        return false;
    }
    if (num == 1) {
        if (!sudoku_setsquare(s, index%GRIDSIZE, index/GRIDSIZE, tmp_val)){
            return false;
        }
    }
    /* col */
    num = 0;
    for(i = 0 ; i < GRIDSIZE -1; i++){
        col_idx = s->cols[idx][i];
        if (s->value[col_idx][v]) {
            num ++;
            index = col_idx;
            tmp_val = v;
        }
    }
    if (num == 0) {
        return false;
    }
    if (num == 1) {
        if(!sudoku_setsquare(s, index%GRIDSIZE, index/GRIDSIZE, tmp_val)){
            return false;
        }
    }
    /* box */
    num = 0;
    for(i = 0; i < GRIDSIZE - 1; i++) {
        box_idx = s->boxes[idx][i];
        if(s->value[box_idx][v]) {
            num ++;
            index = box_idx;
            tmp_val = v;
        }
    }
    if (num == 0) {
        return false;
    }
    if (num == 1) {
        if(!sudoku_setsquare(s, index%GRIDSIZE, index/GRIDSIZE, tmp_val)) {
            return false;
        }
    }
    return true;
}

/* 将y*GRIDSIZE+x的value值（除了v）外，都设置为false */
/* 将cur[y*GRIDSIZE+x]设置为v */
bool sudoku_setsquare(sudoku* s, int x, int y, squaretype v) {
    int i;
    if (v==0) {
        s->cur[y*GRIDSIZE+x] = '.';
        return true;
    }
    s->cur[y*GRIDSIZE+x] = v + '0';
    for (i = 1; i < GRIDSIZE+1 ; i ++){
        if (v != i  && !sudoku_eliminate(s, y*GRIDSIZE+x, i)){
        }
    }
    return sudoku_isvalid(s);   
}


void test_peers_units(sudoku* s, int x, int y) {
    int i;
    for (i = 0; i < GRIDSIZE - 1; i++){
        printf("%d ", s->rows[y*GRIDSIZE+x][i]);
    }
    printf("\n");
    printf("col:");
    for (i = 0; i <GRIDSIZE - 1; i++){
        printf("%d ", s->cols[y*GRIDSIZE+x][i]);
    }
    printf("\n");
    printf("box:");
    for (i =0; i <GRIDSIZE -1 ; i++){
        printf("%d ", s->boxes[y*GRIDSIZE+x][i]);
    }
    printf("\n");
    
    printf("peers:");
    for (i = 0; i<PEERSIZE; i++){
        printf("%d ", s->peers[y*GRIDSIZE+x][i]);
    }
    printf("\n");
}


bool is_empty_ch(char c) {
    return c == '?' || c == '.' || c == '0';
}

bool isvalid_value(char c) {
    return is_valid_ch(c) || is_empty_ch(c);
}

bool sudoku_fromfile(sudoku* s, char* fname) {
    int i, j, k;
    char buf;
    int grid_coord;
    int peer_idx, peer_val;
    FILE *fp;
    
    grid_coord = 0;
    fp = fopen(fname, "r");
    if (fp == NULL) {
        printf("File open ERROR! Can not open file %s\n", fname);
        return false;
    }

    while (!feof(fp)) {
        buf = fgetc(fp);
        if (is_valid_ch(buf)) {
            s->cur[grid_coord] = buf;
            grid_coord++;
        }
        else if (is_empty_ch(buf)) {
            s->cur[grid_coord] = '.';
            grid_coord++;
        }
    }

    if (grid_coord != GRIDSIZE * GRIDSIZE) {
        printf("grid_coord: %d\n", grid_coord);
        return false;
    }

    /* TODO: set value */
    for (i = 0; i < GRIDSIZE; i++){
        for(j = 0; j < GRIDSIZE; j++){
            for(k = 0 ; k < PEERSIZE; k++){
                peer_idx = s->peers[i * GRIDSIZE + j][k];
                if (is_valid_ch(s->cur[peer_idx])){
                    peer_val = s->cur[peer_idx] - '0' - 1;
                    s->value[i * GRIDSIZE + j][peer_val] = true; 
                }
            }
        }
    }
    if (fclose(fp)) {
        return false;
    }

    return true;
}

void sudoku_tostring(sudoku* q, char* str){
    if(q==NULL){
        str[0] = '\0';
        return;
    }
    memcpy(str, q->cur, GRIDSIZE*GRIDSIZE);
    str[GRIDSIZE*GRIDSIZE] = '\0';
}

void sudoku_print(sudoku* s){
    int i,j;
    if (s==NULL) {
        return;
    }
    for(i = 0; i < GRIDSIZE ; i++){
        for(j = 0; j < GRIDSIZE; j++){
            if (j%3==2) {
                printf("%c |", s->cur[i*GRIDSIZE+j]);
            }else{
                printf("%c ", s->cur[i*GRIDSIZE+j]);
            }
        }
        printf("\n");
        if(i%3==2){
            printf("------+------+------+\n");
        }
    }
    printf("\n");
}

/* 
    notice x,y direction
 */
bool sudoku_isknown(sudoku* s, int x, int y) {
    if(s==NULL){
        return false;
    }
    return is_valid_ch(s->cur[y*GRIDSIZE+x]);
}

bool sudoku_isvalid(sudoku* s) {
    int i, j, k, peers_idx;
    if(s == NULL) {
        return false;
    }
    for(i=0; i < GRIDSIZE; i++){
        for(j=0; j < GRIDSIZE; j++){
            if (is_valid_ch(s->cur[j*GRIDSIZE+i])) {
                for(k=0; k<PEERSIZE; k++){
                    peers_idx = s->peers[j*GRIDSIZE+i][k];
                    if(s->cur[j*GRIDSIZE+i] == s->cur[peers_idx]){
                        return false;
                    }
                }
            }
        }
    }
    
    return true;
}

bool* sudoku_taken(sudoku* s, int x, int y) {
    int i, peer_idx;
    char peer_val;
    bool* taken = (bool*) malloc(sizeof(bool)*GRIDSIZE);
    for (i = 0; i < GRIDSIZE; i++){
        taken[i] = false;
    }
    /* update values */
    for(i = 0; i < PEERSIZE; i++){
        peer_idx = s->peers[y*GRIDSIZE+x][i];
        peer_val = s->cur[peer_idx];
        if (is_valid_ch(peer_val)) {
            taken[peer_val - '0' - 1] = true;
        }
    }
    return taken;
}


bool sudoku_cp_solve(sudoku* s){
    int i, j;
    for (i = 0 ; i < GRIDSIZE ; i++) {
        for (j = 0; j < GRIDSIZE; j++) {
            if(!is_valid_ch(s->cur[j*GRIDSIZE+i])){
                return false;
            }
        }
    }
    return true;
}

bool sudoku_consprop(sudoku* s){
    int i, j ;
    for(i = 0; i < GRIDSIZE ; i++){
        for(j=0; j < GRIDSIZE; j++) {
            if ( is_valid_ch(s->cur[j*GRIDSIZE+i]) && ! sudoku_setsquare(s, i, j, s->cur[j*GRIDSIZE+i]-'0')) {
            }
        }
    }
    return sudoku_cp_solve(s);
}


bool sudoku_free(sudoku* q) {
    free(q);
    return true;
}

