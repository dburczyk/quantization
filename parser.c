#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"
#include "find_and_union.h"
#include "commands.h"

#define COMMAND_SIZE 8

int scan_character(char *c){
    int a = getchar();
    if(a == -1)return 0;
    else{
        *c = (char)a;
        return 1;
    }
}

node *get_history(){
    char next_char = ' ';
    node *current_node = root;
    while(scan_character(&next_char) == 1){
        int digit = next_char - '0';
        if(digit >= 0 && digit < ALPHABET_SIZE){
            current_node = move_down(current_node, digit);
        }
        else{
            ungetc(next_char, stdin);
            if(current_node == root)return NULL;
            return current_node;
        }
    }
    return NULL;
}
//returns 0 if energy is invalid
unsigned long long get_energy(){
    unsigned long long answer = 0;
    char next_char = ' ';
    while(scan_character(&next_char) == 1){
        if(next_char - '0' >= 0 && next_char - '0' < 10){
            unsigned long long digit = next_char - '0';
            //when number is bigger than 2^64-1
            if(((answer << 3) >> 3) != answer)return 0; 
            if((answer << 3) + (answer << 1) < (answer << 1))return 0;
            answer = (answer << 3) + (answer << 1); //multiply by 10
            if(answer + digit < digit)return 0;
            //number isn't bigger than 2^64 - 1
            answer += digit;
        }
        else{
            ungetc(next_char, stdin);
            return answer;
        }
    }
    return answer;
}
//returns 1 if met EOF, else 0
int delete_line(){
    char c;
    while(scan_character(&c) == 1){
        if(c == '\n')return 0;
    }
    return 1;
}

//returns 1 if met EOF, else 0
int parse_line(){
    char command[COMMAND_SIZE];
    if(scan_character(command) <= 0)return 1;
    else if(command[0] == '#')return delete_line();
    else if(command[0] == '\n')return 0;

    for(int i = 1; i < COMMAND_SIZE; i++){
        if(scan_character(command + i) <= 0){
            fprintf(stderr, "ERROR\n");
            return 1;
        }
        if(command[i] == '\n'){
            fprintf(stderr, "ERROR\n");
            return 0;
        }
        if(command[i] == ' ')break;
    }
    //printf("tu\n");
    if(memcmp(command, "DECLARE ", 8 * sizeof(char)) == 0){
        node *history = get_history();
        if(history == NULL){
                fprintf(stderr, "ERROR\n");
                return delete_line();
        }
        char next_char;
        if(scan_character(&next_char) <= 0){
            fprintf(stderr, "ERROR\n");
            return 1;
        }
        if(next_char != '\n'){
            fprintf(stderr, "ERROR\n");
            return delete_line();
        }
        else
        {
            
            declare(history);
            printf("OK\n");
            return 0;
        }
    }

    else if(memcmp(command, "REMOVE ", 7 * sizeof(char)) == 0){
        node *history = get_history();
        if(history == NULL){
                fprintf(stderr, "ERROR\n");
                return delete_line();
        }
        char next_char;
        if(scan_character(&next_char) <= 0){
            fprintf(stderr, "ERROR\n");
            return 1;
        }
        if(next_char != '\n'){
            fprintf(stderr, "ERROR\n");
            return delete_line();
        }
        else
        {
            remove_history(history);
            printf("OK\n");
            return 0;
        }
    }

    else if(memcmp(command, "VALID ", 6 * sizeof(char)) == 0){
        node *history = get_history();
        if(history == NULL){
                fprintf(stderr, "ERROR\n");
                return delete_line();
        }
        char next_char;
        if(scan_character(&next_char) <= 0){
            fprintf(stderr, "ERROR\n");
            return 1;
        }
        if(next_char != '\n'){
            fprintf(stderr, "ERROR\n");
            return delete_line();
        }
        else
        {
            if(valid(history) == -1){
                fprintf(stderr, "ERROR\n");
                return 0;
            }
            else if(valid(history) == 0){
                printf("NO\n");
            }
            else{
                printf("YES\n");
            }
            return 0;
        }
    }

    else if(memcmp(command, "ENERGY ", 7 * sizeof(char)) == 0){
        node *history = get_history();
        if(history == NULL){
                fprintf(stderr, "ERROR\n");
                return delete_line();
        }
        char next_char;
        if(scan_character(&next_char) <= 0){
            fprintf(stderr, "ERROR\n");
            return 1;
        }
        if(next_char == '\n'){
            if(valid(history) != 1){
                fprintf(stderr, "ERROR\n");
                return 0;
            }
            if(energy_check(history) != 0){
                printf("%llu\n",energy_check(history));
                return 0;
            }
            else{
                fprintf(stderr, "ERROR\n");
                return 0;
            }
        }
        else if(next_char == ' '){
            if(valid(history) != 1){
                fprintf(stderr, "ERROR\n");
                return delete_line();
            }
            unsigned long long new_energy = get_energy();
            if(new_energy == 0){
                fprintf(stderr, "ERROR\n");
                return delete_line();
            }
            if(scan_character(&next_char) <= 0){
                fprintf(stderr, "ERROR\n");
                return 1;
            }
            if(next_char == '\n'){
                if(new_energy == 0)fprintf(stderr, "ERROR\n");
                else{
                    energy_assign(history, new_energy);
                    printf("OK\n");
                }
                return 0;
            }
            else{
                fprintf(stderr, "ERROR\n");
                return delete_line();
            }
        }
        else{
            fprintf(stderr, "ERROR\n");
            return delete_line();
        }
    }

    if(memcmp(command, "EQUAL ", 6 * sizeof(char)) == 0){
        node *history_a = get_history();
        if(history_a == NULL){
                fprintf(stderr, "ERROR\n");
                return delete_line();
        }
        char next_char;
        if(scan_character(&next_char) <= 0){
            fprintf(stderr, "ERROR\n");
            return 1;
        }
        if(next_char == ' '){
            if(valid(history_a) != 1){
                fprintf(stderr, "ERROR\n");
                return delete_line();
            }
            node *history_b = get_history();
            if(history_b == NULL){
                fprintf(stderr, "ERROR\n");
                return delete_line();
            }
            if(scan_character(&next_char) <= 0){
                fprintf(stderr, "ERROR\n");
                return 1;
            }
            if(next_char == '\n'){
                if(valid(history_b) != 1){
                    fprintf(stderr, "ERROR\n");
                    return 0;
                }
                if(equal(history_a, history_b) == 1)fprintf(stderr, "ERROR\n");
                else printf("OK\n");
                return 0;
            }
            else{
                fprintf(stderr, "ERROR\n");
                return delete_line();
            }
        }
        else{
            fprintf(stderr, "ERROR\n");
            return delete_line();
        }
    }

    else{
        fprintf(stderr, "ERROR\n");
        return delete_line();
    }
}