#include "specific.h"

int i, j, k, r, c, box_r, box_c, index, num;
int col_idx, row_idx, box_idx, peer_idx, peer_val;

bool is_valid_ch(char alpha){
    return alpha == '0' || alpha == '1' || alpha == '2' || alpha == '3' || \
            alpha == '4' || alpha == '5' || alpha == '6' || alpha == '7' || \
            alpha == '8' || alpha == '9';
}

sudoku* sudoku_init(void){
    sudoku* s = (sudoku*) malloc(sizeof(sudoku));
    s->isvalid = true;
    int i, j;
    for(i = 0; i < GRIDSIZE ; i++) {
        for(j = 0; j < GRIDSIZE; j++) {
            col_idx = 0;
            row_idx = 0;
            box_idx = 0;
            peer_idx = 0;
            
            /* initialize value */
            for (k = 0 ; k < GRIDSIZE; k++){
                s->value[i*GRIDSIZE+j][k] = false;
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

bool sudoku_setsquare(sudoku* s, int x, int y, squaretype v){
    v += 48;
    if (v == '0'){
        /* revert the setsquare operation */
        s->cur[y*GRIDSIZE+x] = '.';
        s->isvalid = true;
        return true;
    }
    if (x<0 || x>=GRIDSIZE || y<0 || y>=GRIDSIZE || v < '0' || v > '9') {
        return false;
    }
    if (s==NULL) {
        return false;
    }
    /* TODO */
    /* peers */
    /* transfer ASCII */
    s->cur[y*GRIDSIZE+x] = v; 
    for (i = 0 ; i < PEERSIZE; i++) {
        peer_idx = s->peers[y*GRIDSIZE+x][i];
        if (s->cur[peer_idx] == v){
            s->isvalid = false;
            break;
        }
    }
    return true;
    /* return s->value[y*GRIDSIZE+x][v]; */
}



void test_peers_units(sudoku* s, int x, int y) {
    printf("row:");
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


bool is_empty_alpha(char alpha) {
    return alpha == '?' || alpha == '.' || alpha == '0';
}

bool isvalid_value(char c) {
    return is_valid_ch(c) || is_empty_alpha(c);
}

bool sudoku_fromfile(sudoku* s, char* fname){
    FILE *fp = fopen(fname, "r");
    if (fp == NULL) {
        return false;
    }
    int num = 0;
    while(num < GRIDSIZE * GRIDSIZE){
        char tmp = fgetc(fp);
        if(isvalid_value(tmp)){
            s->cur[num] = tmp;
            if(is_empty_alpha(tmp)) {
                s->cur[num] = '.';
            }
            num ++;
        }
        if( feof(fp) ){
            break;
        }
    }

    if (num != GRIDSIZE*GRIDSIZE) {
        return false;
    }

    /* TODO: set value */
    for (i = 0; i < GRIDSIZE; i++){
        for(j = 0; j < GRIDSIZE; j++){
            for(k = 0 ; k < PEERSIZE; k++){
                peer_idx = s->peers[i*GRIDSIZE+j][k];
                if (is129(s->cur[peer_idx])){
                    peer_val = s->cur[peer_idx] - '0' - 1;
                    s->value[i*GRIDSIZE+j][peer_val] = true; 
                }
            }
        }
    }

    if (fclose(fp)) {
        
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
    return is129(s->cur[y*GRIDSIZE+x]);
}

bool sudoku_isvalid(sudoku* s) {
    if(s==NULL){
        return false;
    }
    return s->isvalid;
}

bool* sudoku_taken(sudoku* s, int x, int y) {
    bool* taken = (bool*) malloc(sizeof(bool)*GRIDSIZE);
    memcpy(taken, s->value[y*GRIDSIZE+x], sizeof(bool)*GRIDSIZE);
    return taken;
}

bool sudoku_consprop(sudoku* s){
    sudoku_free(s);
    return true;
}


bool sudoku_free(sudoku* q) {
    free(q);
    return true;
}

