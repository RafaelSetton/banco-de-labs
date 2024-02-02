#pragma once

struct path
{
    int v[21];
    int n;
};

typedef struct path *p_path;

p_path novo_caminho();

void adiciona(p_path p, int x);

int pop(p_path p);

void reseta(p_path p);

int contem(p_path p, int x);