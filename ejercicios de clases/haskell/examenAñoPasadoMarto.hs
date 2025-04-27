data OpEd = Añadir Char | Borrar | Reemplazar Char

aplicar :: OpEd -> String -> String
aplicar (Añadir x) xs = xs ++ [x]
aplicar Borrar xs = init xs
aplicar (Reemplazar x) xs = init xs ++ [x]

data List a = Nil | Cons a (List a) deriving (Show)

foldList :: (a -> r -> r) -> r -> List a -> r
foldList f b Nil = b
foldList f b (Cons a xs) = f a (foldList f b xs)

reverseList :: List a -> List a
reverseList xs = foldList (\x xs' -> xs' `snoc` x) Nil xs

snoc :: List a -> a -> List a
snoc xs x = foldList Cons (Cons x Nil) xs

aplicarTodas :: List OpEd -> String -> String
aplicarTodas oper xs = foldList aplicar xs (reverseList oper)

data Raro a = Nada | Algo a | Par (Raro a) (Raro a)

foldRaro :: (r -> r -> r) -> (a -> r) -> r -> Raro a -> r
foldRaro par algo b Nada = b
foldRaro par algo b (Algo a) = algo a
foldRaro par algo b (Par p1 p2) = par (foldRaro par algo b p1) (foldRaro par algo b p2)

sumarRaro :: Raro Int -> Int
sumarRaro xs = foldRaro (+) id 0 xs

class Bolsa b where
  agregar :: a -> b a -> b a
  buscar :: (Eq a) => a -> b a -> Bool
  quitar :: (Eq a) => a -> b a -> b a
  cantidad :: b a -> Int

instance Bolsa List where
  agregar :: a -> List a -> List a
  agregar = Cons

  quitar :: (Eq a) => a -> List a -> List a
  quitar x xs = foldList (\a b -> if x == a then b else (Cons a b)) Nil xs

  buscar :: (Eq a) => a -> List a -> Bool
  buscar x xs = foldList (\a b -> if x == a then (True || b) else (False || b)) False xs

  cantidad :: List a -> Int
  cantidad xs = foldList (\_ n -> 1 + n) 0 xs

fun :: (Ord b) => (a -> b) -> a -> b -> b -> b
fun g a s d
  | g a == s = s
  | g a < s = g a
  | otherwise = d
