#ifndef _display_h_
#define _display_h_

/* Public kernel API */
void print_string(char* string);
void print_nl();
void clear_screen();
int scroll_ln(int offset);
char *int_to_string(int v, char *buff, int radix_base);

#endif