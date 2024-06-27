#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char string_output_data[256];
    char function_name[32];
} output_data;

typedef struct {
    char return_data[16];
} return_data;

typedef struct {
    char function_name[256];
    char argv1[64];
    char data_value[64];
    char function_return_data[16];
} function_token;

typedef struct {
    char var_name[16];
    char char_var_data[16];
    int int_var_data;
    float float_var_data;
    char bool_var_data[16];
} var_data;

typedef struct {
    char for_var_1[16];
    char for_var_2[16];
    char for_var_3[16];
    char for_var_4[16];
} for_loop;

typedef struct {
    char if_var_1[16];
    char if_var_2[16];
    char if_var_3[16];
} if_statement;

int process(char *buffer, FILE *file) {
    output_data output;
    function_token token_f;
    var_data data;
    return_data return_data1;
    for_loop for_var;
    if_statement if_var;
    int return_flag = 0;

    if (sscanf(buffer, "print %255s .", output.string_output_data)) {
        fprintf(file, "printf(%s);\n", output.string_output_data);
    } else if (sscanf(buffer, "function %s ( %s : %s ): %s {", token_f.function_name, token_f.data_value, token_f.argv1, token_f.function_return_data)) {
        fprintf(file, "%s %s(%s %s) {\n", token_f.function_return_data, token_f.function_name, token_f.data_value, token_f.argv1);
    } else if (sscanf(buffer, "let int %15s be %d .", data.var_name, &data.int_var_data)) {
        fprintf(file, "int %s = %d;\n", data.var_name, data.int_var_data);
    } else if (sscanf(buffer, "let char %15s be %15s", data.var_name, data.char_var_data)) {
        fprintf(file, "char %s = %s;\n", data.var_name, data.char_var_data);
    } else if (sscanf(buffer, "let float %15s be %f", data.var_name, &data.float_var_data)) {
        fprintf(file, "float %s = %f;\n", data.var_name, data.float_var_data);
    } else if (sscanf(buffer, "let bool %15s be %15s", data.var_name, data.bool_var_data)) {
        fprintf(file, "bool %s = %s;\n", data.var_name, data.bool_var_data);
    } else if (sscanf(buffer, "}")) {
        fprintf(file, "}\n");
    } else if (sscanf(buffer, "return %15s .", return_data1.return_data)) {
        fprintf(file, "return %s;\n", return_data1.return_data);
        return_flag = 1;
    } else if (sscanf(buffer, "for %15s in range %15s {", for_var.for_var_1, for_var.for_var_2)) {
        fprintf(file, "for (int %s = 0; %s == %s; %s++) {\n", for_var.for_var_1, for_var.for_var_1, for_var.for_var_2, for_var.for_var_1);
    } else if (sscanf(buffer, "if %15s %15s %15s {", if_var.if_var_1, if_var.if_var_2, if_var.if_var_3)) {
        fprintf(file, "if (%s %s %s) {\n", if_var.if_var_1, if_var.if_var_2, if_var.if_var_3);
    } else {
        fprintf(file, "}\n");
    }

    return 0; // 正常終了を示すために0を返す
}

int main(int argc, char *argv[]) {
    FILE *file;
    FILE *file_2;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[2], "tomato.c") == 0) {
        perror("error code: (3)");
        return 1;
    }

    file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("error code: (1)");
        return 1;
    }

    file_2 = fopen(argv[2], "w");
    if (file_2 == NULL) {
        perror("error code: (2)");
        fclose(file);
        return 1;
    }

    fprintf(file_2, "#include <stdio.h>\n#include <stdlib.h>\n#include <string.h>\n\n");

    char buffer[256];

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s\n", buffer);
        process(buffer, file_2);
    }

    fclose(file);
    fclose(file_2);
    return 0;
}