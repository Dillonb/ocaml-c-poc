#include <stdio.h>
#include <caml/mlvalues.h>
#include <caml/callback.h>

const value* hello_closure = NULL;

void init_ocaml(char** argv) {
    caml_startup(argv);
    hello_closure = caml_named_value("print_hello");
}

void print_hello() {
    caml_callback(*hello_closure, Val_unit);
}

int main(int argc, char** argv) {
    init_ocaml(argv);
    printf("hello from c\n");
    print_hello();
}
