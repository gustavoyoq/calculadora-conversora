/*

  Criação: 25/08/2024
  Autor: Gustavo Mourato

  1º Questão - 6:09 PM 26/08
  2º Questão - 8:12 PM 27/08
  3º Questão - 11:24 PM 27/08

  Link do GitHub: https://github.com/gustavoyoq/calculadora-conversora


*/


#include <stdio.h>
#include <string.h>

void binario(int num);
void octal(int num);
void hexa(int num);
void bcd(int num);
void complemento2(int num);
void floatdouble(double num);

int main(void) {
  int opc;
  printf("\n\nEscolha qual conversor usar:\n");
  printf("[1] Decimal para Base 2\n");
  printf("[2] Decimal para Base 8\n");
  printf("[3] Decimal para Base 16\n");
  printf("[4] Decimal para Código BCD\n");
  printf("[5] Decimal para Base com sinal com 16 bits\n");
  printf("[6] Decimal real para binário com ponto flutuante e double\n\n");
  scanf("%d", &opc);

  if (opc == 1){
    int result; 
    int num;
    printf("\nInsira um número para converter: ");
    scanf("%d", &num);
    printf("\n");
    binario(num);
    main();
  } else if (opc == 2){
    int num;
    printf("\nInsira um número para converter: ");
    scanf("%d", &num);
    octal(num);
    main();
  } else if (opc == 3){
    int num;
    printf("\nInsira um número para converter: ");
    scanf("%d", &num);
    hexa(num);
    main();
  } else if (opc == 4){
    int num;
    printf("\nInsira um número para converter: ");
    scanf("%d", &num);
    bcd(num);
    main();
  } else if (opc == 5){
    int num;
    printf("\nInsira um número para converter: ");
    scanf("%d", &num);
    complemento2(num);
    main();
  } else if (opc == 6){ 
    double num;
    printf("\nInsira um número para converter: ");
    scanf("%lf", &num);
    floatdouble(num);
    main();
  }
  
  return 0;
}

void binario (int num){
  int result[32], i = 0;
  while (num > 0){
    result[i] = num % 2;
    printf("%d / 2 = %d\nResto: %d\n\n", num, (num/2), result[i]);
    num = num/2;
    i++;
  }
  printf("Resultado da conversão(Base2): ");
  for (int j = i - 1; j >= 0; j--) {
      printf("%d", result[j]);
  }
}

void octal (int num){
  int result[32], i = 0;
  while (num > 0){
    result[i] = num % 8;
    printf("%d / 8 = %d\nResto: %d\n\n", num, (num/8), result[i]);
    num = num/8;
    i++;
  }
  printf("Resultado da conversão(Base8): ");
  for (int j = i - 1; j >= 0; j--) {
      printf("%d", result[j]);
  }
}

void hexa(int num) {
  char result[100];
  int i = 0;
  while (num != 0) {
      int resto = num % 16;
      if (resto < 10) {
          result[i] = resto + '0';
          printf("%d / 16 = %d\nResto: %d\n\n", num, (num/16), resto);
      } else {
          result[i] = resto - 10 + 'A';
      }

      num = num / 16;
      i++;
  }

  printf("Resultado da conversão(Base16): ");  
  for (int j = i - 1; j >= 0; j--) {
        printf("%c", result[j]);
  }
  printf("\n");
  }

void bcd(int num) {
    int algarismos[10];
    int size = 0;

    if (num == 0) {
        printf("0000\n");
        return;
    }
    while (num > 0) {
        algarismos[size] = num % 10;
        size++;
        printf("Pegando algarismo para converter: %d\n", num % 10);
        num /= 10;
    }

    printf("\n");
    printf("Resultado da conversão: ");
    for (int i = size - 1; i >= 0; i--) {
        int algarismo = algarismos[i];
        for (int j = 3; j >= 0; j--) {
            printf("%d", (algarismo >> j) & 1);
        }
        printf(" ");
    }

    printf("\n");
}

void complemento2(int num) {
    int result[16];
    int bin = num;
    int i = 0, j = 0;
    if (num < 0) {
        bin = num*(-1);
    }

    while (bin > 0) {
        result[i] = bin % 2;
        bin /= 2;
        i++;
        j++;
    }
    while (i < 16) {
        result[i] = 0;
        i++;
    }

    printf("Número em binário: ");
    for (int k = 15; k >= 0; k--) {
        printf("%d", result[k]);
    }
    printf("\n");

    printf("Número com binaridade invertida: ");
    for (int k = 15; k >= 0; k--) {
        printf("%d", result[k] == 0 ? 1 : 0);
    }
    printf("\n");

    if (num < 0) {
        int carry = 1;
        for (int k = 0; k < 16; k++) {
            int sum = (result[k] == 0 ? 1 : 0) + carry;
            result[k] = sum % 2;
            carry = sum / 2;
        }
    }

    printf("Número em complemento a 2: ");
    for (int k = 15; k >= 0; k--) {
        printf("%d", result[k]);
    }
    printf("\n");
}

void floatdouble(double numero) {
    unsigned long long bits = 0;
    unsigned char *byteptr = (unsigned char*)&numero;
    
    for (int i = 0; i < sizeof(double); i++) {
        bits |= (unsigned long long)byteptr[i] << (8 * i);
    }

    unsigned long long integerpart = (unsigned long long)numero;
    int algorismo = 0;
    int flag = 0;

    printf("Parte inteira em binário: ");
    if (integerpart == 0) {
        printf("0");
        algorismo++;
    } else {
        for (int i = 63; i >= 0; i--) {
            if (integerpart & (1ULL << i)) {
                printf("1");
                algorismo++;
                flag = 1;
            } else if (flag) {
                printf("0");
                algorismo++;
            }
        }
    }
    int bitsinal = (bits >> 63) & 1;
    printf("Bit de sinal: %d\n", bitsinal);
    printf("Exponente: %d\n", algorismo);

    printf("Resultado da conversão (64 bits): ");
    for (int i = 63; i >= 0; i--) {
        printf("%c", (bits & (1ULL << i)) ? '1' : '0');
    }
    printf("\n");
    printf("Conversão do fracionário: ");
    for (int i = 51; i >= 0; i--) {
        printf("%c", (bits & (1ULL << i)) ? '1' : '0');
    }
    printf("\n");
}