import Text.XHtml (rev)
--1

--a

data OpEd = Escribir Char | Reemplazar Char | Borrar 

--b

aplicar :: OpEd -> String -> String 
aplicar (Borrar) s = init s
aplicar (Escribir c) s = s ++ [c]
aplicar (Reemplazar c) s = init s ++ [c]

--c

data List a = Nil | Cons a (List a) deriving (Show)

foldList :: (a -> r -> r) -> r -> List a -> r
foldList f b Nil = b
foldList f b (Cons x xs) = f x (foldList f b xs)


snoc :: List a -> a -> List a
snoc l x = foldList Cons (Cons x Nil) l 

reverseList :: List a -> List a
reverseList xs = foldList (\ x y -> y `snoc`x) Nil xs

aplicarTodas :: List OpEd -> String -> String 
aplicarTodas l s = foldList (\ l' s' -> aplicar l' s') s (reverseList l) 

--2 
--a

data Raro a = Nada | Algo a | Par (Raro a) (Raro a) 

foldRaro :: (r -> r -> r) -> (a -> r) -> r -> Raro a -> r 
foldRaro par algo nd (Nada) = nd
foldRaro par algo nd (Algo a) = algo a
foldRaro par algo nd (Par x y) = par (foldRaro par algo nd x) (foldRaro par algo nd y)

--b 

sumarRaro :: Raro Int -> Int 
sumarRaro raro = foldRaro (\ x y -> x + y) id 0 raro

--3

class Bolsa b where
    agregar :: a -> b a -> b a
    buscar :: Eq a => a -> b a -> Bool
    quitar :: Eq a => a -> b a -> b a
    cantidad :: b a -> Int

instance Bolsa List where
    agregar :: a -> List a -> List a
    agregar x l = (Cons x) l
    buscar :: Eq a => a -> List a -> Bool
    buscar x l = foldList (\y z -> if (x == y) then (True || z) else (False || z)) False l
    quitar :: Eq a => a -> List a -> List a
    quitar x l = foldList (\ y z -> if (x == y) then z else (Cons y z)) Nil l
    cantidad :: List a -> Int
    cantidad l = foldList (\ _ x -> 1 + x) 0 l

--4

fun :: Ord r => (a -> r) a -> r -> r -> r