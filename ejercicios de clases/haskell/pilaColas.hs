-- instance Stack Pila where
--   empty::Pila a
--   empty = PEmpty
--
--   push::a->Pila a -> Pila a
--   push x xs = PTop x xs
--
--   top:: Pila a -> a
--   top (PTop x xs) = x
--
--   pop :: Pila a -> Pila a
--
class Stack s where
  empty :: s a
  push :: a -> s a -> s a
  top :: s a -> a
  pop :: s a -> s a
  isEmpty :: s a -> Bool

instance Stack [] where
  empty = []
  push = (:)
  top = head
  pop = tail
  isEmpty = null

class Queue q where
  empty' :: q a
  enqueue :: a -> q a -> q a
  qfront :: q a -> a
  dequeue :: q a -> q a
  isEmpty' :: q a -> Bool

data FastQueue a = FQ ([a], [a]) deriving (Show)

dump :: FastQueue a -> FastQueue a
dump (FQ (outs, ins)) = FQ (outs ++ reverse ins, [])

instance Queue FastQueue where
  empty' = FQ ([], [])
  enqueue x (FQ (xs, ys)) = FQ (xs, x : ys)

  qfront (FQ (x : outs, ins)) = x
  qfront (FQ ([], ins)) = qfront (dump (FQ ([], ins)))

  dequeue (FQ ([], [])) = (FQ ([], []))
  dequeue (FQ (x : xs, ys)) = FQ (xs, ys)
  dequeue (FQ ([], ys)) = dequeue (dump (FQ ([], ys)))
  isEmpty' = undefined
