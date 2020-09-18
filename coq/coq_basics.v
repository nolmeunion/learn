Inductive day : Type :=
  | monday
  | tuesday
  | wednesday
  | thursday
  | friday
  | saturday
  | sunday.

Definition next_weekday (d:day) : day :=
  match d with
  | monday => tuesday
  | tuesday => wednesday
  | wednesday => thursday
  | thursday => friday
  | friday => monday
  | saturday => monday
  | sunday => monday
  end.

Compute (next_weekday friday).
Compute (next_weekday tuesday).


Example test_next_weekday: 
  (next_weekday (next_weekday saturday)) = tuesday.


Proof. simpl. reflexivity. Qed.


(*
  - example is a test 
  - proof is unique to Coq 
*)


