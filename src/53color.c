#include "../include/helpers2.h"
#include "../include/hw2.h"

int main(int argc, char* argv[]) {
    char* c_file = NULL;
    char* mapping_file = NULL;
    int lines_shown = 24;

    // Use basic getopt to parse flags and respective arguments
    int c;
    while ((c = getopt(argc, argv, "hl:k:")) >= 0) {
        switch (c) {
            case 'h':
                fprintf(stdout,USAGE_MSG);
                return EXIT_SUCCESS;
            case 'l':
                lines_shown = atoi(optarg);
                break;
            case 'k':
                mapping_file = optarg;
                break;
            default:
                fprintf(stderr, USAGE_MSG);
                return EXIT_FAILURE;
        }
    }

    // validate that we only have 1 positional argument
    if (optind + 1 != argc)
    {
        fprintf(stderr, "Exactly one positional argument should be specified.\n\n" USAGE_MSG);
        return EXIT_FAILURE;
    }
    
    c_file = *(argv + optind);

    // INSERT YOUR IMPLEMENTATION HERE
    FILE * fp = NULL;
    fp = fopen(c_file, "r");

    FILE * mappingFile = NULL;

    list_t* linkedList = NULL;

    if (mapping_file != NULL) {
        mappingFile = fopen(mapping_file, "r");

        //Generate mappings
        linkedList = CreateList(&mapping_tComparator, &mapping_tPrinter, &mapping_tDeleter);
        node_t** head = &(linkedList->head);
        node_t* newNode = NULL;
        node_t* prev = NULL;

        char * line = NULL;
        size_t len = 0;
        ssize_t lineSize = 0;
        int totalCount = 0;

        mapping_t * map = NULL;

    
        while (1) {
            lineSize = getline(&line, &len, mappingFile);
            if (lineSize == -1) {
                if (totalCount == 0) {
                    //Error
                    return 2;
                } else {
                    break;
                }
            }
            map = CreateMapping(line);

            /*
            newNode = malloc(sizeof(node_t));
            newNode->data = map;

            if (totalCount == 0) {
                *head = newNode;
            } else {
                prev->next = newNode;
            }
            prev = newNode;
            */
           InsertInOrder(linkedList, map, 1);




            totalCount++;

        }
        if (line)
            free(line);
    } else {
        linkedList = GenerateDefaultFormatMappings();
    }


    /*
    mapping_t *mapping = malloc(sizeof(mapping_t));
    char *key = malloc(4 * sizeof(char));
    key = "aoz";
    mapping->keyword = key;
    mapping->format.fg_color = 91;
    mapping->format.bg_color = 100;
    mapping->format.is_bold = 1;

    InsertInOrder(linkedList, mapping, 0); */
    //PrintLinkedList(linkedList);




    int val = 0;
    int isCommented = 0;
    char * input = malloc(sizeof(char)*10);
    while (1) {
        isCommented = processLine(fp, lines_shown, linkedList, isCommented);

        if (isCommented == -1)
            break;

        fgets(input,10,stdin);
        if ( ((*input) == 'q') || ((*input) == 'Q')  ) {
            break;
        }
    }


   //printf("\nCLEANUP\n");

    //fclose(fp);
    free(input);

    //DestroyDefaultFormatMappings(linkedList);
    DestroyList(linkedList);

    return 0;
}
