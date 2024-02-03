let print_hello () = print_endline "hello from ocaml" ;;

let () = Callback.register "print_hello" print_hello