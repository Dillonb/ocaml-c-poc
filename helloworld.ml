let print_hello () = print_endline "hello from ocaml" ;;

let process_byte_array(buf) = 
  for i = 0 to Bigarray.Array1.dim buf - 1 do
    let b = Bigarray.Array1.get buf i in
      Bigarray.Array1.set buf i (b + 1)
  done

let () = Callback.register "print_hello" print_hello

let () = Callback.register "process_byte_array" process_byte_array