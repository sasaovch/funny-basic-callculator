#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <math.h>

double math(int argc, char* argv[]) {
    int c;
    while (1) {
        static struct option long_opt[] = {
            {"help", no_argument, 0, 'h'},
            // {"unary", no_argument, 0, 'u'},
            // {"binary", no_argument, 0, 'b'},
            {"sub", no_argument, 0, 's'},
            {"subract", no_argument, 0, 's'},
            {"add", no_argument, 0, 'a'},
            {"multiply", no_argument, 0, 'm'},
            {"mul", no_argument, 0, 'm'},
            {"divide", no_argument, 0, 'd'},
            {"div", no_argument, 0, 'd'},
            {"mod", no_argument, 0, 'o'},
            {"modulus", no_argument, 0, 'o'},
            {"power", no_argument, 0, 'p'},
            {"pow", no_argument, 0, 'p'},
            {"factorial", no_argument, 0, 'f'},
            {"exp", no_argument, 0, 'e'},
            {"ln", no_argument, 0, 'l'},
            {"abs", no_argument, 0, 'A'},
            {0, 0, 0, 0}
                    };
        int optIdx;
        double a, b;
        if((c = getopt_long(argc, argv, "samdopfelA", long_opt, &optIdx)) == -1)
        break;
        switch( c ){
            // Надеюсь, ты выведешь в отдельную функцию вывод запроса на ввод чисел 
            case 'a':
                printf("Enter first number: ");
                scanf("%lf", &a);
                printf("Enter second number: ");
                scanf("%lf", &b);
                return(a + b);
            case 's':
                printf("Enter first number: ");
                
                scanf("%lf", &a);
                printf("Enter second number: ");
                scanf("%lf", &b);
                return(a - b);
            case 'm':
                printf("Enter first number: ");
                
                scanf("%lf", &a);
                printf("Enter second number: ");
                scanf("%lf", &b);
                return(a * b);
            case 'd':
                printf("Enter first number: ");
                
                scanf("%lf", &a);
                printf("Enter second number: ");
                scanf("%lf", &b);
                return(a / b);
            case 'o':
                printf("Enter first number: ");
                
                scanf("%lf", &a);
                printf("Enter second number: ");
                scanf("%lf", &b);
                double c = a / b;
                return(((c) - floor(c)) * b);
            case 'p':
                printf("Enter first number: ");
                
                scanf("%lf", &a);
                printf("Enter second number: ");
                scanf("%lf", &b);
                return(pow(a, b));
            case 'f':
                printf("Enter number: ");
                scanf("%lf", &a);
                int fact = 1;
                int x;
                for(x = 1; x <= a; x++)
                fact = fact * x; 
                return(fact);
            case 'e':
                printf("Enter number: ");
                scanf("%lf", &a);
                return(exp(a));
            case 'l':
                printf("Enter number: ");
                scanf("%lf", &a);
                return(log(a));
            case 'A':
                printf("Enter number: ");
                scanf("%lf", &a);
                return(abs(a));
            case 'h':
                printf("Usage: math [OPTION]... [NUMBER]...");
                // С тебя документация по всем опциям
            default:
                return(-1);
        }
    }
}
        
    //     return(0);
    //     int firstNum;
    //     int secondNum;
    //     char* typeOperation;
    //     int mode = -1;
    //     char* l;
    //     char* k;
    //     char* u;
    //     int opt;
    //     while ((opt = getopt(argc, argv, "a:b:X")) != -1) 
    //     {
    //         // printf("opt = %3d (%c); optind = %lf\n", opt, opt, optind);
    //         switch (opt) 
    //         {
    //             case 'a':
    //                 if (atoi(optarg) == 0) {
    //                     printf("Error: a must be positive");
    //                     break;
    //                 }
    //                 printf("Option a has arg: %s\n", optarg);
    //                 break;
    //             case 'b':
    //                 if (atoi(optarg) == 0) {
    //                     printf("Error: a must be positive");
    //                     break;
    //                 }
    //                 printf("Option b has arg: %s\n", optarg);
    //                 k = optarg;
    //                 break;
    //             case 'X':
    //                 printf("Option X was provided\n");
    //                             fprintf(stdout, "Missing argument!\n"
    //                                     "Usage: %s [-i arg] [-s arg] [-v arg]\n", argv[0]); 
    //                 exit(EXIT_FAILURE);
    //                 break;
    //             default:
    //                 fprintf(stdout, "Unexpected case in command"); 
    //                 exit(EXIT_FAILURE);
    //         }
    // }