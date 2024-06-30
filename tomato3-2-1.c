#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

typedef struct
{
    char include_file[256];
} import_data;

typedef struct
{
    char class_name[64];
} class;

typedef struct
{
    char var1[64];
    char var2[64];
    char var3[64];
    char var4[64];
    char var5[64];
    char var6[64];

    char token1[64];
    char token2[64];
    char token3[64];
    char token4[64];
} for_and_if_def;

typedef struct
{
    char var1[64];
    char var2[64];
} add_pull;

typedef struct
{
    char output_data_1[512];
    char output_data_2[512];
    char output_data_3[512];
    char output_data_4[512];
    char output_data_5[512];
    char output_data_6[128];
    char output_data_7[512];
    char output_data_8[512];
    char output_data_9[512];
    char output_data_10[512];
    char output_data_11[512];
    char output_data_12[512];
    char output_data_13[512];
    char output_data_14[512];
    char output_data_15[512];

    int output_data_int1[128];
    float output_data_float1[128];
} output;
/*
---------------------------japanase------------------------------
*/
//--------------------------execute def ----------------------------
int process_execute_def_jp(char *buffer, FILE *file2)
{
    add_pull add;

    if (sscanf(buffer, "追加 %s %s", add.var1, add.var2))
    {
        fprintf(file2, "%s += %s;\n", add.var1, add.var2);
    }
    else if (sscanf(buffer, "引く %s %s", add.var1, add.var2))
    {
        fprintf(file2, "%s -= %s;\n", add.var1, add.var2);
    }
    return 0;
}

//------------------------------var def -------------------------
int process_var_def_jp(char *buffer, FILE *file2)
{
    setlocale(LC_ALL, "");
    output output;

    if (sscanf(buffer, "とします %s be %s:char", output.output_data_4, output.output_data_5))
    {
        fprintf(file2, "char %s = %s;\n", output.output_data_4, output.output_data_5);
    }
    else if (sscanf(buffer, "とします %s be %s:float", output.output_data_4, output.output_data_5))
    {
        fprintf(file2, "float %s = %s;\n", output.output_data_4, output.output_data_5);
    }
    else if (sscanf(buffer, "とします %s be %s:int", output.output_data_4, output.output_data_5))
    {
        fprintf(file2, "int %s = %s;\n", output.output_data_4, output.output_data_5);
    }
    return 0;
}

//------------------------for and if def-------------------------------
int process_for_and_if_def_jp(char *buffer, FILE *file2)
{
    for_and_if_def def;

    if (sscanf(buffer, "繰り返す %s %s %s", def.var1, def.token1, def.var2))
    {
        fprintf(file2, "for (int %s = 0;%s %s %s; %s ++) {\n", def.var1, def.var1, def.token1, def.var2, def.var1);
    }

    if (sscanf(buffer, "もし %s %s %s {\n", def.var1, def.token1, def.var2))
    {
        fprintf(file2, "if (%s %s %s) {\n", def.var1, def.token1, def.var2);
    }
}

//------------------------- PRINT FUNCTION DEF------------------------
int process_print_function_jp(char *buffer, FILE *file2)
{
    output output;
    if (sscanf(buffer, "印刷 %s", output.output_data_1) == 1)
    {
        fprintf(file2, "printf(%s);\n", output.output_data_1); // 修正点：フォーマット指定子を追加
        return 0;
    }
    return 1; // 修正点：失敗した場合に1を返す
}

//---------------------------------FUNCTION DEF--------------------------
int process_function_def_jp(char *buffer, FILE *file2)
{
    output output;
    if (sscanf(buffer, "関数 %255s ( %255s : %255s ) : %255s {",
               output.output_data_15,
               output.output_data_14,
               output.output_data_13,
               output.output_data_12))
    {
        fprintf(file2, "%s %s(%s %s) {\n",
                output.output_data_12,
                output.output_data_15,
                output.output_data_14,
                output.output_data_13);
        return 0;
    }
    else if (strcmp(buffer, "}終わり\n") == 0 || strcmp(buffer, "}終わり") == 0)
    {
        fprintf(file2, "}\n");
    }
    else if (sscanf(buffer, "実行する %s (%s)", output.output_data_10, output.output_data_9))
    {
        fprintf(file2, "%s(%s);\n", output.output_data_10, output.output_data_9);
    }
    else if (sscanf(buffer, "実行する %s ()", output.output_data_10))
    {
        fprintf(file2, "%s();\n", output.output_data_10);
    }
    return 1; // 修正点：失敗した場合に1を返す
}
//------------------import def-------------------------
int process_include_def_jp(char *buffer, FILE *file2)
{
    import_data import_data;

    if (sscanf(buffer, "パッケージ %s", import_data.include_file))
    {
        fprintf(file2, "#include %s\n", import_data.include_file);
    }
    return 0;
}

/*
--------------------------english--------------------------------
*/

//--------------------------execute def ----------------------------
int process_execute_def(char *buffer, FILE *file2)
{
    add_pull add;
    

    if (sscanf(buffer, "add %s %s", add.var1, add.var2))
    {
        fprintf(file2, "%s += %s;\n", add.var1, add.var2);
    }
    else if (sscanf(buffer, "pull %s %s", add.var1, add.var2))
    {
        fprintf(file2, "%s -= %s;\n", add.var1, add.var2);
    }
    return 0;
}

//------------------------------var def -------------------------
int process_var_def(char *buffer, FILE *file2)
{
    setlocale(LC_ALL, "");
    output output;

    if (sscanf(buffer, "%s %s be %s", output.output_data_4, output.output_data_5, output.output_data_6) == 3)
    {
        fprintf(file2, "%s %s = %s;\n", output.output_data_4, output.output_data_5, output.output_data_6);
    }
    return 0;
}

//------------------------for and if def-------------------------------
int process_for_and_if_def(char *buffer, FILE *file2)
{
    for_and_if_def def;

    if (sscanf(buffer, "for %s %s %s", def.var1, def.token1, def.var2))
    {
        fprintf(file2, "for (int %s = 0;%s %s %s; %s ++) {\n", def.var1, def.var1, def.token1, def.var2, def.var1);
    }

    if (sscanf(buffer, "if %s %s %s {\n", def.var1, def.token1, def.var2))
    {
        fprintf(file2, "if (%s %s %s) {\n", def.var1, def.token1, def.var2);
    }
}

//------------------------- PRINT FUNCTION DEF------------------------
int process_print_function(char *buffer, FILE *file2)
{
    output output;
    if (sscanf(buffer, "print %s", output.output_data_1) == 1)
    {
        fprintf(file2, "printf(%s);\n", output.output_data_1); // 修正点：フォーマット指定子を追加
        return 0;
    }
    return 1; // 修正点：失敗した場合に1を返す
}

//---------------------------------FUNCTION DEF--------------------------
int process_function_def(char *buffer, FILE *file2)
{
    output output;
    if (sscanf(buffer, "func %255s ( %255s : %255s ) : %255s {",
               output.output_data_15,
               output.output_data_14,
               output.output_data_13,
               output.output_data_12))
    {
        fprintf(file2, "%s %s(%s %s) {\n",
                output.output_data_12,
                output.output_data_15,
                output.output_data_14,
                output.output_data_13);
        return 0;
    }
    else if (sscanf(buffer, "func %255s () : %255s {",
               output.output_data_15,
               output.output_data_12))
    {
        fprintf(file2, "%s %s() {\n",
                output.output_data_12,
                output.output_data_15);
        return 0;
    } else if (sscanf(buffer, "func %255s ( %255s : %255s, %255s : %255s ) : %255s {",
               output.output_data_15,
               output.output_data_14,
               output.output_data_13,
               output.output_data_11,
               output.output_data_10,
               output.output_data_12))
    {
        fprintf(file2, "%s %s(%s %s, %s %s) {\n",
                output.output_data_12,
                output.output_data_15,
                output.output_data_14,
                output.output_data_13,
                output.output_data_11,
                output.output_data_10);
        return 0;
    }
    else if (sscanf(buffer, "func %255s ( %255s : %255s ) : %255s",
               output.output_data_15,
               output.output_data_14,
               output.output_data_13,
               output.output_data_12))
    {
        fprintf(file2, "%s %s(%s %s)\n",
                output.output_data_12,
                output.output_data_15,
                output.output_data_14,
                output.output_data_13);
        return 0;
    }
    else if (sscanf(buffer, "func %255s () : %255s",
               output.output_data_15,
               output.output_data_12))
    {
        fprintf(file2, "%s %s()\n",
                output.output_data_12,
                output.output_data_15);
        return 0;
    } else if (sscanf(buffer, "func %255s ( %255s : %255s, %255s : %255s ) : %255s",
               output.output_data_15,
               output.output_data_14,
               output.output_data_13,
               output.output_data_11,
               output.output_data_10,
               output.output_data_12))
    {
        fprintf(file2, "%s %s(%s %s, %s %s)\n",
                output.output_data_12,
                output.output_data_15,
                output.output_data_14,
                output.output_data_13,
                output.output_data_11,
                output.output_data_10);
        return 0;
    }
    else if (strcmp(buffer, "}end\n") == 0 || strcmp(buffer, "}end") == 0)
    {
        fprintf(file2, "}\n");
    }
    else if (sscanf(buffer, "execute %s (%s)", output.output_data_10, output.output_data_9))
    {
        fprintf(file2, "%s(%s);\n", output.output_data_10, output.output_data_9);
    }
    else if (sscanf(buffer, "execute %s ()", output.output_data_10))
    {
        fprintf(file2, "%s();\n", output.output_data_10);
    }
    else if (sscanf(buffer, "return %s", output.output_data_8)) {
        fprintf(file2, "return %s;\n", output.output_data_8);
    }
    else if (strcmp(buffer, "}\n") == 0 || strcmp(buffer, "}") == 0) {
        fprintf(file2, "}\n");
    }
    else if (strcmp(buffer, "{\n") == 0 || strcmp(buffer, "{") == 0) {
        fprintf(file2, "}\n");
    }
    return 1; // 修正点：失敗した場合に1を返す
}

//------------------import def-------------------------
int process_include_def(char *buffer, FILE *file2)
{
    import_data import_data;

    if (sscanf(buffer, "package %s", import_data.include_file))
    {
        fprintf(file2, "#include %s\n", import_data.include_file);
    }
    return 0;
}

//---------------------------math def --------------------------
int process_math_def(char *buffer, FILE * file2) 
{

    return 0;
}

void delete_tab(char *buffer)
{
    char *start = buffer;
    while (*start && (*start == ' ' || *start == '\t'))
    { // 修正点：文字リテラルの間違い
        start++;
    }
    if (start != buffer)
    {
        memmove(buffer, start, strlen(start) + 1); // 修正点：文字列を前に移動
    }
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    FILE *file1 = fopen(argv[1], "r");
    if (file1 == NULL)
    {
        perror("error opening input file");
        return 1;
    }

    FILE *file2 = fopen(argv[2], "w");
    if (file2 == NULL)
    {
        perror("error opening output file");
        fclose(file1); // 修正点：file1を閉じる
        return 1;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file1) != NULL)
    {
        delete_tab(buffer);

        process_include_def(buffer, file2);
        if (process_function_def(buffer, file2) != 0)
        {
            process_print_function(buffer, file2);
            process_for_and_if_def(buffer, file2);
            process_var_def(buffer, file2);
            process_execute_def(buffer, file2);
        }

        process_include_def_jp(buffer, file2);
        process_function_def_jp(buffer, file2);
        process_print_function_jp(buffer, file2);
        process_for_and_if_def_jp(buffer, file2);
        process_var_def_jp(buffer, file2);
        process_execute_def_jp(buffer, file2);
    }

    fclose(file1); // 修正点：file1を閉じる
    fclose(file2); // 修正点：file2を閉じる
    return 0;
}