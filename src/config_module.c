/* ----------------------------------------------------------------------------
 config_module -  This module holds the state and functions related to config files

 date: 8/15/17
 author: Alex C.U. (@au42)
----------------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <config_module.h>
#include <libconfig.h>

config_t cfg;
config_setting_t *setting;
const char *str;

// TODO: create custom error codes for "cant find file"
// TODO: create hardcoded values inside header file and use below, instead of magic strings

/* Does all the required work to load config values from a file. */
int m_config_init(){
      
    config_init(&cfg);

    // Read the file. If there is an error, report it and exit.
    if(! config_read_file(&cfg, CFG_FILENAME))
    {
        fprintf(stderr, "%s:%d - %s\n", config_error_file(&cfg),
        config_error_line(&cfg), config_error_text(&cfg));
        config_destroy(&cfg);
        return(EXIT_FAILURE);
    }

    /* Get the store name. */
    if(config_lookup_string(&cfg, "name", &str))
        printf("Store name: %s\n\n", str);
    else
        fprintf(stderr, "No 'name' setting in configuration file.\n");

    /* Output a list of all books in the inventory. */
    setting = config_lookup(&cfg, "inventory.books");
    if(setting != NULL)
    {
        int count = config_setting_length(setting);
        int i;

        printf("%-30s  %-30s   %-6s  %s\n", "TITLE", "AUTHOR", "PRICE", "QTY");

        for(i = 0; i < count; ++i)
        {
        config_setting_t *book = config_setting_get_elem(setting, i);

        /* Only output the record if all of the expected fields are present. */
        const char *title, *author;
        double price;
        int qty;

        if(!(config_setting_lookup_string(book, "title", &title)
            && config_setting_lookup_string(book, "author", &author)
            && config_setting_lookup_float(book, "price", &price)
            && config_setting_lookup_int(book, "qty", &qty)))
            continue;

        printf("%-30s  %-30s  $%6.2f  %3d\n", title, author, price, qty);
        }
        putchar('\n');
    }

    return(EXIT_SUCCESS);
}




