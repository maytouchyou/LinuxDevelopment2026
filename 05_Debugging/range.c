#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct range {
    int start;
    int stop;
    int step;
    int current;
};

void range_init(struct range *r)
{
    if (r) r->current = r->start;
}

bool range_run(const struct range *r){
    if (r) return r->current < r->stop;
    return false;
}

void range_next(struct range *r){
    if (r) r->current += r->step;
}

int range_get(const struct range *r){
    if (r) return r->current;
    return 0;
}

void help(){
    printf("Простейшая программа-генератор арифметической прогрессии\n"
           "  <program>             => help \n"
           "  <program> <N>         => вывод последовательности [0, 1, … N-1] \n"
           "  <program> <M> <N>     => вывод последовательности [M, M+1, … N-1] \n"
           "  <program> <M> <N> <S> => вывод последовательности [M, M+S, M+2S, … N-1] \n"
    );
    return;
}

bool parseint(const char *str, int *ret){
    long val;
    char *endptr;

    errno = 0;
    val = strtol(str, &endptr, 10);

    if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN))
        || (errno != 0 && val == 0))
    {
        perror("strtol");
        return false;
    }

    if (ret) *ret = val;
    return true;
}

bool argparse(int argc, char **argv, int *start, int *stop, int *step)
{
    if (argc == 1){
        help();
        return false;
    }

    if (argc >= 2) {
        if (!start || !parseint(argv[1], start))
            return false;

        if (stop) *stop = *start;
        if (step) *step = 1;
        if (argc == 2) *start = 0;
    }

    if (argc >= 3) {
        if (!stop || !parseint(argv[2], stop))
            return false;
    }

    if (argc == 4) {
        if (!step || !parseint(argv[3], step))
            return false;
    }

    return true;
}

int main(int argc, char **argv)
{
    struct range I;
    if (argparse(argc, argv, &I.start, &I.stop, &I.step)){
        for(range_init(&I); range_run(&I); range_next(&I))
            printf("%d\n", range_get(&I));
    }
    return 0;
}
