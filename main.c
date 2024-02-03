#include <stdio.h>
#include <caml/bigarray.h>
#include <caml/mlvalues.h>
#include <caml/callback.h>

const value* hello_closure = NULL;
const value* process_byte_array_closure = NULL;

void init_ocaml(char** argv) {
    caml_startup(argv);
    hello_closure = caml_named_value("print_hello");
    process_byte_array_closure = caml_named_value("process_byte_array");
}

void print_hello() {
    caml_callback(*hello_closure, Val_unit);
}

void process_byte_array(uint8_t* buf, size_t length) {
    value buf_arr = caml_ba_alloc_dims(CAML_BA_UINT8, 1, buf, length);
    caml_callback(*process_byte_array_closure, buf_arr);
}

int main(int argc, char** argv) {
    init_ocaml(argv);
    printf("hello from c\n");
    print_hello();

    uint8_t buf[] = {0x00, 0x01, 0x02, 0x03};
    printf("Original buffer:\n");
    for (int i = 0; i < 4; i++) {
        printf("%02X ", buf[i]);
    }
    printf("\n");

    // mutate it
    process_byte_array((uint8_t*)&buf, sizeof(buf) / sizeof(buf[0]));

    printf("After running ocaml code:\n");
    for (int i = 0; i < 4; i++) {
        printf("%02X ", buf[i]);
    }
    printf("\n");
}
